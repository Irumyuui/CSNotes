struct Solution;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> Vec<i32> {
        let xor_sum = nums.iter().fold(0, |acc, num| acc ^ num);
        let lowbit = xor_sum & -xor_sum;

        let mut ret = vec![0; 2];
        for &x in &nums {
            if x & lowbit == 0 {
                ret[0] ^= x;
            } else {
                ret[1] ^= x;
            }
        }

        ret
    }
}

fn main() {}
