use std::collections::HashMap;
use std::mem::MaybeUninit;
use std::ptr::NonNull;

type Ptr<T> = Option<NonNull<T>>;

struct Node<T> {
    data: MaybeUninit<T>,
    prev: Ptr<Node<T>>,
    next: Ptr<Node<T>>,
}

impl<T> Node<T> {
    fn new(data: T) -> Self {
        Self {
            data: MaybeUninit::new(data),
            prev: None,
            next: None,
        }
    }
}

impl<T> Default for Node<T> {
    fn default() -> Self {
        Self {
            data: MaybeUninit::uninit(),
            prev: None,
            next: None,
        }
    }
}

struct LRUCache {
    capcity: usize,
    dummy: Ptr<Node<(i32, i32)>>,
    key_to_node: HashMap<i32, NonNull<Node<(i32, i32)>>>,
}

impl LRUCache {
    pub fn new(capcity: i32) -> Self {
        let dummpy = unsafe {
            let node =
                NonNull::new_unchecked(Box::into_raw(Box::new(Node::<(i32, i32)>::default())));
            (*node.as_ptr()).next = Some(node);
            (*node.as_ptr()).prev = Some(node);

            node
        };

        Self {
            capcity: capcity as usize,
            dummy: Some(dummpy),
            key_to_node: HashMap::new(),
        }
    }

    fn get(&mut self, key: i32) -> i32 {
        if let Some(node) = self.key_to_node.get(&key) {
            unsafe {
                let data = node.as_ref().data.clone().assume_init_read();
                let ptr = node.clone();
                self.remove(ptr);
                self.push_front(ptr);

                data.1
            }
        } else {
            -1
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        if let Some(node) = self.key_to_node.get(&key) {
            let node = node.as_ptr();

            unsafe {
                (*(*node).data.as_mut_ptr()).1 = value;
                let node = NonNull::new_unchecked(node);
                self.remove(node);
                self.push_front(node);
            }

            return;
        }

        let node_ptr = Box::into_raw(Box::new(Node::new((key, value))));

        unsafe {
            let node = NonNull::new_unchecked(node_ptr);
            self.key_to_node.insert(key, node);
            self.push_front(node);
        }

        if self.key_to_node.len() > self.capcity {
            unsafe {
                let back_node = (*self.dummy.unwrap().as_ptr()).prev.unwrap();
                self.key_to_node
                    .remove(&back_node.as_ref().data.assume_init_read().0);
                self.remove(back_node);
            }
        }
    }

    unsafe fn remove(&mut self, node: NonNull<Node<(i32, i32)>>) {
        let prev = node.as_ref().prev.unwrap();
        let next = node.as_ref().next.unwrap();

        (*prev.as_ptr()).next = Some(next);
        (*next.as_ptr()).prev = Some(prev);
    }

    unsafe fn push_front(&mut self, node: NonNull<Node<(i32, i32)>>) {
        let next = (*self.dummy.unwrap().as_ptr()).next;

        (*node.as_ptr()).prev = self.dummy;
        (*node.as_ptr()).next = next;

        (*self.dummy.unwrap().as_ptr()).next = Some(node);
        (*next.unwrap().as_ptr()).prev = Some(node);
    }
}

impl Drop for LRUCache {
    fn drop(&mut self) {
        unsafe {
            (*(*self.dummy.unwrap().as_ptr()).prev.unwrap().as_ptr()).next = None;
            let mut cur_node = self.dummy;
            while let Some(node) = cur_node.take() {
                let next_node = (*node.as_ptr()).next;
                cur_node = next_node;

                (*node.as_ptr()).data.assume_init_drop();
                drop(Box::from_raw(node.as_ptr()));
            }
        }
    }
}

fn main() {}
