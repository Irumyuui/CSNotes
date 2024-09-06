use std::{collections::HashMap, vec};

struct Solution;

impl Solution {
    pub fn maximum_length(nums: Vec<i32>, k: i32) -> i32 {
        let k = k as usize;

        let mut dp = vec![0; k + 1];
        let mut memo = HashMap::with_capacity(nums.len());

        for &x in &nums {
            let memo = memo.entry(x).or_insert(vec![0; k + 1]);
            for i in 0..=k {
                memo[i] += 1;
                if i > 0 {
                    memo[i] = memo[i].max(dp[i - 1] + 1);
                }
            }
            for i in 0..=k {
                dp[i] = dp[i].max(memo[i]);
                if i > 0 {
                    dp[i] = dp[i].max(dp[i - 1]);
                }
            }
        }

        dp[k]
    }
}

fn main() {
    println!("{}", Solution::maximum_length(vec![1, 2, 1, 1, 3], 2));
    println!("{}", Solution::maximum_length(vec![1, 2, 3, 4, 5, 1], 0));
}
