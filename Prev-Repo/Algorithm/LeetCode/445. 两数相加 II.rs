// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

struct Solution;

impl Solution {
    pub fn add_two_numbers(l1: Option<Box<ListNode>>, l2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        fn get_size(mut l: &Option<Box<ListNode>>) -> usize {
            let mut size = 0;
            while let Some(node) = l {
                size += 1;
                l = &node.next;
            }
            size
        }

        let n1 = get_size(&l1);
        let n2 = get_size(&l2);               

        fn make_list(l1: &Option<Box<ListNode>>, n1: usize, l2: &Option<Box<ListNode>>, n2: usize) -> Option<Box<ListNode>> {
            if n1 == 0 && n2 == 0 {
                return None;
            }

            if n1 > n2 {
                return make_list(&l2, n2, &l1, n1);
            }

            if n1 < n2 {
                let mut next = make_list(&l1, n1, &l2.as_ref().unwrap().next, n2 - 1);
                let mut ret = ListNode::new(l2.as_ref().unwrap().val);

                if let Some(node) = &mut next {
                    if node.val >= 10 {
                        ret.val += node.val / 10;
                        node.val %= 10;
                    }
                    ret.next = next;
                }

                Some(Box::new(ret))
            } else {
                let mut next = make_list(&l1.as_ref().unwrap().next, n1 - 1, &l2.as_ref().unwrap().next, n2 - 1);
                let mut ret = ListNode::new(l1.as_ref().unwrap().val + l2.as_ref().unwrap().val);
                
                if let Some(node) = &mut next {
                    if node.val >= 10 {
                        ret.val += node.val / 10;
                        node.val %= 10;
                    }
                }

                ret.next = next;

                Some(Box::new(ret))
            }
        }
        
        let mut ret = make_list(&l1, n1, &l2, n2);

        while let Some(node) = &mut ret {
            if node.val >= 10 {
                let mut new_node = ListNode::new(node.val / 10);
                node.val %= 10;
                new_node.next = ret;
                ret = Some(Box::new(new_node));
            } else {
                break;
            }
        }

        ret
    }
}

fn main() {

}