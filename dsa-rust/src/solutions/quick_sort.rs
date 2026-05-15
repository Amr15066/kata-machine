/// Quick Sort: O(n log n) average, in-place with Lomuto partition.
/// Teaches: recursion with slice indices, partitioning, swap.
///
/// We use index-based recursion rather than sub-slices to avoid
/// borrow-checker complexity — a practical Rust trade-off.
pub fn quick_sort(arr: &mut [i32]) {
    let len = arr.len();
    if len <= 1 {
        return;
    }
    qs(arr, 0, len - 1);
}

fn qs(arr: &mut [i32], lo: usize, hi: usize) {
    if lo >= hi {
        return;
    }

    let pivot_idx = partition(arr, lo, hi);

    if pivot_idx > 0 {
        qs(arr, lo, pivot_idx - 1);
    }
    qs(arr, pivot_idx + 1, hi);
}

fn partition(arr: &mut [i32], lo: usize, hi: usize) -> usize {
    let pivot = arr[hi];
    let mut idx = lo;

    for i in lo..hi {
        if arr[i] <= pivot {
            arr.swap(i, idx);
            idx += 1;
        }
    }
    arr.swap(idx, hi);
    idx
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sorts_array() {
        let mut arr = [9, 3, 7, 4, 69, 420, 42];
        quick_sort(&mut arr);
        assert_eq!(arr, [3, 4, 7, 9, 42, 69, 420]);
    }

    #[test]
    fn empty_and_single() {
        let mut empty: [i32; 0] = [];
        quick_sort(&mut empty);

        let mut single = [42];
        quick_sort(&mut single);
        assert_eq!(single, [42]);
    }
}
