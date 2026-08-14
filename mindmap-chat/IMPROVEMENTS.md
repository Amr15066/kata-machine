# Changes since the hackathon build

The 24-hour LeedsHack version worked well enough to demo, but a read of the
source afterwards turned up a set of defects that a demo would never surface.
This documents what was wrong, why it mattered, and what changed.

Every claim below is covered by a test in `tests/`, which runs offline with no
API key (`pytest`).

---

## 1. The graph's relation types were decorative

**The bug.** `ConversationGraph.to_d3_graph()` contained:

```python
relation = "child"
confidence = 0.8
```

Hardcoded, for every edge. The palette defined five relation types
(`continue`, `deepen`, `child`, `sibling`, `tangent`) with distinct colours and
stroke widths, but four of them were unreachable — every edge rendered the same
blue. `BlockClassification.action` was computed by the classifier, used to
decide routing, and then discarded.

This mattered more than a cosmetic bug: the entire premise of the project is
that the *shape* of a conversation is meaningful, and the visualisation was
throwing away the thing that made the shape meaningful.

**Verified on the original code:**

```
to_d3_graph() relation variety -> relations={'child'} colours={'#2196F3'}
```

**The fix.** `Block` now persists `relation` and `relation_confidence`, set at
creation time from the classifier's decision. `to_d3_graph()` reads them.
A single `RELATION_ALIASES` map translates classifier vocabulary (`new_child`)
into renderer vocabulary (`child`) so the two cannot drift apart.

---

## 2. Loading a conversation could crash

**The bug.** `JSONStorage.load()` assigned `mindmap` only inside
`if "graphs" in data:`, then used it unconditionally. Any file without that key
raised `UnboundLocalError`. The legacy-format migration that was supposed to
handle exactly that case sat *after* a `return` statement — unreachable dead
code that had never run.

**Verified on the original code:**

```
load() on legacy single-graph file -> UnboundLocalError: cannot access local
variable 'mindmap' where it is not associated with a value
```

**The fix.** Proper `if/else`, the migration path restored and tested, plus a
guard for a non-dict JSON root. `Block.from_dict` and
`ConversationMessage.from_dict` now ignore unknown keys, so adding or removing
a field no longer makes every previously saved conversation unloadable.

---

## 3. Blocks were summarised exactly once, ever

**The bug.**

```python
if message_count >= threshold and not block.summary:
```

Once a block had a summary, `not block.summary` was permanently false. Combined
with a 3-message context window, everything between message 4 and message 27 of
a long block was invisible to the model — not truncated with a warning, just
silently gone. Answer quality decayed the longer you stayed on one topic, which
is the exact opposite of what the product promises.

**The fix.** `Block.summarized_at_message_count` records what the current
summary covers; `maybe_auto_summarize` re-summarises once the block has grown by
`resummarize_every_n_messages` since then.

---

## 4. Deepened blocks lost the thread they came from

**The bug.** `construct_block_context()` built context from the current block
only. A block created by `DEEPEN` or `NEW_CHILD` starts with zero messages, so
the model answered the first question in a new sub-topic with no idea what was
being deepened.

**The fix.** `collect_ancestors()` walks the parent chain (cycle-safe, since
parent links are rebuilt from persisted data rather than validated on write) and
the nearest `ancestor_context_depth` summaries are prepended under a
`WHERE THIS CAME FROM` heading.

---

## 5. Two of the five thresholds did nothing

**The bug.** In `detect_intent_shift`:

```python
elif intent_similarity < thresholds.tangent_threshold:
    return _classify_with_llm(...)   # identical body
else:
    return _classify_with_llm(...)   # identical body
```

`tangent_threshold` was a config knob with no effect. `related_match_threshold`
was never referenced at all. Worse, both paths fell back to `"continue"` when the
LLM errored — so an API blip pinned a completely unrelated message onto the
current block.

**The fix.** The band now selects the *fallback*: below `tangent_threshold` the
fallback is `tangent`, above it `new_child`. Thresholds are validated as ordered
at construction, and documented as the unvalidated magic numbers they are.

---

## 6. The Gemini fallback could never have worked

**The bug.**

```python
try:
    import google.generativeai as genai
except ImportError:
    import google.genai as genai      # new SDK
...
genai.configure(api_key=...)          # does not exist on the new SDK
```

The two SDKs have incompatible surfaces. The fallback would `AttributeError`
immediately. Both packages were pinned in `requirements.txt`, so the failure was
masked in the one environment anyone actually ran.

`response.text` was also used unguarded — it raises when the model returns no
candidates, which is what happens on a safety block or token exhaustion. That
surfaced as an opaque 500 with no indication of the real cause.

**The fix.** A single `_load_sdk()` detects which SDK is present and the client
branches properly for both generation and embeddings. `_extract_text()` checks
`prompt_feedback.block_reason`, falls back to joining `candidates[0].content.parts`,
and raises a message naming the actual `finish_reason`.

`DeepSeekClient` referenced `config.deepseek`, which did not exist in `AppConfig`
— constructing it always raised `AttributeError`. Config added; it now delegates
embeddings to `GeminiClient` instead of configuring a second SDK by hand.

---

## 7. Redundant work on every single turn

| Waste | Before | After |
|---|---|---|
| `construct_block_context` | called twice per answer, plus a hand-built prompt discarded on the next line | once |
| User message embedding | embedded in `detect_intent_shift`, then again in `_find_matching_block_in_other_graphs` | once, passed through |
| Corpus loads per web message | 2 | 1 |
| Corpus saves per web message | 2 | 1 |
| Embedding calls in cross-graph search | one network round-trip *inside* a nested loop, per un-embedded block | collected and backfilled outside the scan |

Embeddings were also being sent without a `task_type`. Queries and documents are
asymmetric; embedding a live user question and a stored block intent the same way
compares the wrong things. `TASK_QUERY` / `TASK_DOCUMENT` are now set correctly.

---

## 8. The codebase could not be tested at all

Importing anything under `core/` pulled in `llm/__init__.py`, which eagerly
imported `GeminiClient`, which required the Google SDK and an API key. There was
no way to run any logic offline, which is why the thresholds were hand-tuned by
demo feel rather than measurement.

**The fix.**

- Provider clients resolve lazily via module `__getattr__`, so `import llm`
  works without any SDK installed.
- `llm/fake.py` adds `FakeLLMClient`: deterministic hash-based embeddings (so
  similar text really is more cosine-similar), scriptable responses, and call
  counters that let tests assert redundant work has actually been removed.
- 49 tests covering storage round-trips and migration, relation rendering,
  threshold bands, summarisation cadence, ancestor context, and the full
  conversation loop.

---

## What is still wrong

These are known and deliberately not addressed here; they are design changes,
not fixes.

1. **JSON file as a database.** Every message rewrites the whole corpus. At
   3072 dimensions stored as JSON text, one block's embedding is roughly 61 KB
   (about 12 KB as a float32 blob). This is the root cause of the write
   amplification and it does not survive real use.
2. **No user model.** There is one global `conversation.json`. Two people using
   a deployed instance share one mindmap. The `RLock` added here makes
   read-modify-write atomic *within a process*; it does nothing across
   processes or machines.
3. **Cross-graph search is O(N)** pure-Python cosine over every block. Fine at
   hackathon scale, not at thousands of blocks. Wants a vector index.
4. **The thresholds are still unvalidated.** 0.90 / 0.70 / 0.75 were chosen by
   feel. There is no labelled set and no confusion matrix, so the core claim —
   that this routes conversation correctly — is unproven. This is the single
   highest-value thing to build next: it converts an opinion into a number.
5. **The LLM can never overrule a confident embedding.** The classifier is only
   consulted when similarity < 0.70, so a confidently-wrong embedding match is
   final.

See `proj_mindmap-chat-technical-roadmap.md` for the full phased plan.
