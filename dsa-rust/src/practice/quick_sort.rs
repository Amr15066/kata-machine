/// Quick Sort: O(n log n) average, in-place with Lomuto partition.
/// Teaches: recursion with slice indices, partitioning, swap.
///
/// TODO: Pick arr[hi] as pivot, partition so smaller elements go left,
/// then recurse on each half.
pub fn quick_sort(arr: &mut [i32]) {
    let len = arr.len();
    if len <= 1 {
        return;
    }
    qs(arr, 0, len - 1);
}

fn qs(arr: &mut [i32], lo: usize, hi: usize) {
    // TODO: implement recursive quick sort
    // Hint: partition, then recurse left and right halves
    todo!()
}

fn partition(arr: &mut [i32], lo: usize, hi: usize) -> usize {
    // TODO: Lomuto partition — use arr[hi] as pivot
    todo!()
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
