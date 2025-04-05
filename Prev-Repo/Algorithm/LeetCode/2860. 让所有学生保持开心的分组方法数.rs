use std::vec;

#[allow(dead_code)]
struct Solution;

impl Solution {
    pub fn count_ways(mut nums: Vec<i32>) -> i32 {
        nums.sort_unstable();

        let mut ans = if nums[0] > 0 { 1 } else { 0 };
        for i in 1..nums.len() {
            let t = i as i32;
            if nums[i - 1] < t && t < nums[i] {
                ans += 1;
            }
        }

        ans + 1
    }
}

fn main() {
    let result = Solution::count_ways(vec![6,0,3,3,6,7,2,7]);
    println!("{}", result);
}
