#[allow(dead_code)]
struct Solution;

impl Solution {
    pub fn clear_digits(s: &String) -> String {
        let mut ret = vec![];

        for c in s.chars() {
            if c.is_numeric() {
                ret.pop();
            } else {
                ret.push(c);
            }
        }

        ret.into_iter().collect()
    }
}

fn main() {}
