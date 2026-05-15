/// Bubble Sort: O(n²) comparison sort, in-place.
/// Teaches: mutable slices (&mut [T]), .swap(), nested loops.
pub fn bubble_sort(arr: &mut [i32]) {
    let len = arr.len();
    for i in 0..len {
        for j in 0..len.saturating_sub(1 + i) {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1); // Rust's safe swap — no temp variable needed
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sorts_array() {
        let mut arr = [9, 3, 7, 4, 69, 420, 42];
        bubble_sort(&mut arr);
        assert_eq!(arr, [3, 4, 7, 9, 42, 69, 420]);
    }

    #[test]
    fn empty_and_single() {
        let mut empty: [i32; 0] = [];
        bubble_sort(&mut empty);
        assert_eq!(empty, []);

        let mut single = [1];
        bubble_sort(&mut single);
        assert_eq!(single, [1]);
    }
}
