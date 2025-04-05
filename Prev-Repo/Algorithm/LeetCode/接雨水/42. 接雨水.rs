impl Solution {
    pub fn trap(height: Vec<i32>) -> i32 {
        let mut ans = 0;

        let mut stk = Vec::with_capacity(height.capacity());
        for r in 0..height.len() {
            while !stk.is_empty() && height[*stk.last().unwrap()] < height[r] {
                let t = stk.pop().unwrap();
                if stk.is_empty() {
                    break;
                }
                let l = *stk.last().unwrap();
                let h = i32::min(height[l], height[r]) - height[t];
                ans += (r - l - 1) as i32 * h;
            }
            stk.push(r);
        }

        ans
    }
}
