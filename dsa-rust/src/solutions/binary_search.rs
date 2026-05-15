/// Binary Search: O(log n) search on a sorted array.
/// Teaches: while loops, usize overflow care, half-open ranges [lo, hi).
pub fn binary_search(haystack: &[i32], needle: i32) -> bool {
    let mut lo: usize = 0;
    let mut hi: usize = haystack.len();

    while lo < hi {
        let mid = lo + (hi - lo) / 2;
        if haystack[mid] == needle {
            return true;
        } else if haystack[mid] < needle {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    false
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
