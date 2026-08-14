# LeedsHack2026 — Mindmap Chat

A chat interface that structures a conversation as a navigable mindmap rather
than a linear transcript. Each shift in intent branches the graph, so a
discussion that wanders can still be followed, revisited and resumed.

Built in 24 hours at LeedsHack 2026. Since hardened: see
[`IMPROVEMENTS.md`](IMPROVEMENTS.md) for the defects found in the original
build, the evidence for each, and what changed.

## Getting Started

### Prerequisites
- Python 3.10+
- pip (Python package manager)
- Google Gemini API key (for the core AI engine) — place this in a `.env` file
  in the `mindmap_chat` directory as `GEMINI_API_KEY=your_api_key_here`

### Setup Virtual Environment

```bash
# Create virtual environment
python -m venv .venv

# Activate virtual environment
# On Windows:
.venv\Scripts\activate
# On macOS/Linux:
source .venv/bin/activate

# Install dependencies
pip install -r requirements.txt
```

## Running the Tests

The suite runs entirely offline against a deterministic fake client, so it
needs no API key and makes no network calls.

```bash
pip install -r requirements-dev.txt
pytest
```

## Running the App

### FastAPI App (Port 8000)

**Option 1: Using launch script (Windows)**
```powershell
.\launch-fastapi.ps1
```

**Option 2: Using launch script (macOS/Linux)**
```bash
chmod +x launch-fastapi.sh
./launch-fastapi.sh
```

**Option 3: Manual**
```bash
cd my-fastapi-app
uvicorn app:app --reload --host 127.0.0.1 --port 8000
```

Access at: **http://127.0.0.1:8000**

API docs: **http://127.0.0.1:8000/docs**

## Project Structure

```text
LeedsHack2026/
├── mindmap_chat/           # Core AI Engine (Gemini)
│   ├── core/               # Intent detection, block lifecycle, context building
│   ├── llm/                # API clients, prompt templates, offline fake client
│   ├── storage/            # Persistence logic
│   ├── utils/              # Helper functions
│   ├── config.py           # App configuration and thresholds
│   ├── conversation.py     # Conversation orchestration
│   ├── main.py             # CLI entry point
│   └── models.py           # Graph & Block data structures
├── my-fastapi-app/         # FastAPI Web Interface
│   ├── app/                # API endpoints & initialization
│   ├── static/             # CSS & D3.js visualization logic
│   └── templates/          # HTML templates
├── tests/                  # Offline test suite (no API key required)
├── requirements.txt        # Runtime dependencies
├── requirements-dev.txt    # Test dependencies
├── pyproject.toml          # Project & pytest configuration
├── IMPROVEMENTS.md         # Post-hackathon fixes and remaining limitations
├── launch-fastapi.ps1      # Launcher (Windows)
├── launch-fastapi.sh       # Launcher (Bash)
└── README.md
```


