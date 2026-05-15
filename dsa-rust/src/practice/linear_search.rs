/// Linear Search: scan every element until we find the needle.
/// Teaches: slices (&[T]), iterators, early return.
///
/// TODO: Walk through each element. Return true if needle is found.
/// Time complexity: O(n)
pub fn linear_search(haystack: &[i32], needle: i32) -> bool {
    // TODO: implement
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn finds_existing_elements() {
        let arr = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
        assert!(linear_search(&arr, 69));
        assert!(linear_search(&arr, 69420));
        assert!(linear_search(&arr, 1));
    }

    #[test]
    fn returns_false_for_missing() {
        let arr = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
        assert!(!linear_search(&arr, 1336));
        assert!(!linear_search(&arr, 69421));
        assert!(!linear_search(&arr, 0));
    }
}
