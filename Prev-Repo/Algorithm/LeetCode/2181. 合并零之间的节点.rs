use std::{
    collections::LinkedList,
    f32::consts::E,
    ptr::{self, NonNull},
};

struct Solution;

// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

impl Solution {
    #[inline]
    pub fn merge_nodes(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut ans = None;

        let mut cur = &mut ans as *mut Option<Box<ListNode>>;
        let mut tot = 0;

        while let Some(node) = head.take() {
            if node.val == 0 && tot > 0 {
                unsafe {
                    *cur = Some(Box::new(ListNode::new(tot)));
                    cur = &mut (*cur).as_mut().unwrap().next;
                }
                tot = 0;
            } else {
                tot += node.val;
            }

            head = node.next
        }

        ans
    }
}

fn main() {}
