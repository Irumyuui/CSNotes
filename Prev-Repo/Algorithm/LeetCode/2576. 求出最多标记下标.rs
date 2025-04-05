#![allow(unused)]

struct Solution;

impl Solution {
    // 排序，然后枚举左右 k 个数字对是否可以组合为 k 对
    // 二分这个 k
    pub fn max_num_of_marked_indices(mut nums: Vec<i32>) -> i32 {
        nums.sort();

        let check = |k: usize| -> bool {
            for i in 0..k {
                if nums[i] * 2 > nums[nums.len() - k + i] {
                    return false;
                }
            }
            true
        };

        let mut l = 0;
        let mut r = nums.len() / 2;
        let mut ret = 0;

        while l <= r {
            let mid = l + (r - l) / 2;
            if check(mid) {
                ret = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        (ret * 2) as _
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        assert_eq!(Solution::max_num_of_marked_indices(vec![3, 5, 2, 4]), 2);
    }

    #[test]
    fn test2() {
        assert_eq!(Solution::max_num_of_marked_indices(vec![9, 2, 5, 4]), 4);
    }

    #[test]
    fn test3() {
        assert_eq!(Solution::max_num_of_marked_indices(vec![7, 6, 8]), 0);
    }
}

fn main() {}
