struct Solution;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        nums.iter().fold(0, |x, y| x ^ y)
    }
}

fn main() {
    println!("{}", Solution::single_number(vec![2, 2, 1]));
    println!("{}", Solution::single_number(vec![4, 1, 2, 1, 2]));
}
