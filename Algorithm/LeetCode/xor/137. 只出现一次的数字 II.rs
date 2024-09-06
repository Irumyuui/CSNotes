use std::collections::HashMap;

struct Solution;

// impl Solution {
//     pub fn single_number(nums: Vec<i32>) -> i32 {
//         let mut cnt = std::collections::HashMap::new();

//         for &x in &nums {
//             *cnt.entry(x).or_insert(0) += 1;
//         }

//         let mut res = 0;
//         for (&k, &v) in &cnt {
//             if v == 1 {
//                 res = k;
//                 break;
//             }
//         }

//         res
//     }
// }

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut cnt = [0; 32];

        for &x in &nums {
            for i in 0..32 {
                if (x >> i) & 1 == 1 {
                    cnt[i] += 1;
                }
            }
        }

        let mut res = 0;
        for i in 0..32 {
            if cnt[i] % 3 != 0 {
                res |= 1 << i;
            }
        }
        res
    }
}

fn main() {
    println!("{}", Solution::single_number(vec![2, 2, 3, 2]));
    println!("{}", Solution::single_number(vec![0, 1, 0, 1, 0, 1, 99]));
}
