/// Two Crystal Balls: find the first `true` in a sorted bool slice
/// using sqrt(n) jumps — O(√n).
/// Teaches: Option<usize>, f64 sqrt, two-phase search.
pub fn two_crystal_balls(breaks: &[bool]) -> Option<usize> {
    let jump = (breaks.len() as f64).sqrt() as usize;

    // Phase 1: jump forward until we find a true
    let mut i = 0;
    while i < breaks.len() {
        if breaks[i] {
            break;
        }
        i += jump;
    }

    // Phase 2: walk back one jump, then linear scan
    let start = if i >= jump { i - jump } else { 0 };
    for j in start..breaks.len().min(start + jump + 1) {
        if breaks[j] {
            return Some(j);
        }
    }
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn finds_break_point() {
        let break_point = 7321;
        let mut arr = vec![false; 10000];
        for i in break_point..10000 {
            arr[i] = true;
        }
        assert_eq!(two_crystal_balls(&arr), Some(break_point));
    }

    #[test]
    fn returns_none_for_all_false() {
        let arr = vec![false; 10000];
        assert_eq!(two_crystal_balls(&arr), None);
    }

    #[test]
    fn first_element_true() {
        let arr = vec![true; 100];
        assert_eq!(two_crystal_balls(&arr), Some(0));
    }
}
