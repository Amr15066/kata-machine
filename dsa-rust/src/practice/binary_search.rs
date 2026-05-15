/// Binary Search: O(log n) search on a sorted array.
/// Teaches: while loops, usize overflow care, half-open ranges [lo, hi).
///
/// TODO: Use two pointers (lo, hi). Compute mid, compare, halve the range.
pub fn binary_search(haystack: &[i32], needle: i32) -> bool {
    // TODO: implement
    // Hint: let mut lo = 0; let mut hi = haystack.len();
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn finds_existing_elements() {
        let arr = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
        assert!(binary_search(&arr, 69));
        assert!(binary_search(&arr, 69420));
        assert!(binary_search(&arr, 1));
    }

    #[test]
    fn returns_false_for_missing() {
        let arr = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
        assert!(!binary_search(&arr, 1336));
        assert!(!binary_search(&arr, 69421));
        assert!(!binary_search(&arr, 0));
    }
}
