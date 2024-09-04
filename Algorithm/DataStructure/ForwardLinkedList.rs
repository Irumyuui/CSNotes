pub struct Node<T> {
    value: T,
    next: Option<Box<Node<T>>>,
}

pub struct ForwardLinkedList<T> {
    head: Option<Box<Node<T>>>,
    size: usize,
}

impl<T> Node<T> {
    pub fn new(value: T, next: Option<Box<Node<T>>>) -> Self {
        Self { value, next }
    }
}

impl<T> ForwardLinkedList<T> {
    pub fn new() -> Self {
        Self {
            head: None,
            size: 0,
        }
    }

    pub fn size(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.size() == 0
    }

    pub fn push_front(&mut self, value: T) {
        let new_node = Box::new(Node::new(value, self.head.take()));
        self.head = Some(new_node);
        self.size += 1;
    }

    pub fn pop_front(&mut self) -> Option<T> {
        let node = self.head.take()?;
        self.head = node.next;
        self.size -= 1;
        Some(node.value)
    }
}

impl<T> std::fmt::Display for ForwardLinkedList<T>
where
    T: std::fmt::Display,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut current = &self.head;
        let mut result = String::new();

        while let Some(node) = current {
            if result.len() == 0 {
                result = format!("{}", node.value);
            } else {
                result = format!("{}, {}", result, node.value);
            }
            current = &node.next;
        }

        write!(f, "{}", result)
    }
}

impl<T> Drop for ForwardLinkedList<T> {
    fn drop(&mut self) {
        let mut current = self.head.take();
        while let Some(mut node) = current {
            current = node.next.take();
        }
    }
}

impl<T> Clone for ForwardLinkedList<T>
where
    T: Clone,
{
    fn clone(&self) -> Self {
        let mut result = ForwardLinkedList::new();

        result.size = self.size;
        result.head = match &self.head {
            Some(node) => Some(Box::new(Node::new(node.value.clone(), None))),
            None => return result,
        };

        let mut p1 = &self.head.as_ref().unwrap().next;
        let mut p2 = &mut result.head;

        while let Some(n) = p1 {
            p2.as_mut().unwrap().next = Some(Box::new(Node::new(n.value.clone(), None)));
            p1 = &n.next;
            p2 = &mut p2.as_mut().unwrap().next;
        }

        result
    }
}

impl<T> PartialEq for ForwardLinkedList<T>
where
    T: PartialEq,
{
    fn eq(&self, other: &Self) -> bool {
        if self.size() != other.size() {
            return false;
        }

        if self.size() == 0 {
            return true;
        }

        let mut p1 = &self.head;
        let mut p2 = &other.head;

        while let (Some(n1), Some(n2)) = (p1, p2) {
            if n1.value != n2.value {
                return false;
            }
            p1 = &n1.next;
            p2 = &n2.next;
        }

        true
    }
}

pub struct ForwardLinkedListIntoIter<T> {
    current: Option<Box<Node<T>>>,
}

pub struct ForwardLinkedListIter<'a, T> {
    current: &'a Option<Box<Node<T>>>,
}

impl<T> Iterator for ForwardLinkedListIntoIter<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        match self.current.take() {
            Some(node) => {
                let data = node.value;
                self.current = node.next;
                Some(data)
            }
            None => None,
        }
    }
}

impl<T> IntoIterator for ForwardLinkedList<T> {
    type Item = T;
    type IntoIter = ForwardLinkedListIntoIter<T>;

    fn into_iter(mut self) -> Self::IntoIter {
        Self::IntoIter {
            current: self.head.take(),
        }
    }
}

impl<'a, T> Iterator for ForwardLinkedListIter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        match self.current {
            Some(node) => {
                self.current = &node.next;
                Some(&node.value)
            }
            None => None,
        }
    }
}

impl<'a, T> IntoIterator for &'a ForwardLinkedList<T> {
    type Item = &'a T;
    type IntoIter = ForwardLinkedListIter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        Self::IntoIter {
            current: &self.head,
        }
    }
}

impl<T> std::fmt::Debug for ForwardLinkedList<T>
where
    T: std::fmt::Debug + std::fmt::Display,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let debug_f = &mut f.debug_struct("LinkedList");
        debug_f.field("size", &self.size);
        debug_f.field("value", &format!("{}", self));
        debug_f.finish()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_clone() {
        let mut l1: ForwardLinkedList<i32> = ForwardLinkedList::new();
        l1.push_front(1);
        l1.push_front(2);
        l1.push_front(4);
        l1.push_front(2);
        let l2 = l1.clone();
        println!(
            "size: {} values: {}\nsize: {} values: {}\n",
            l1.size, l1, l2.size, l2
        );
    }
    #[test]
    fn test_euqal() {
        let mut l1: ForwardLinkedList<i32> = ForwardLinkedList::new();
        l1.push_front(1);
        l1.push_front(2);
        l1.push_front(4);
        l1.push_front(2);
        let l2 = l1.clone();
        assert_eq!(l1, l2);
    }
    #[test]
    fn test_debug() {
        let mut l1: ForwardLinkedList<i32> = ForwardLinkedList::new();
        l1.push_front(1);
        l1.push_front(2);
        l1.push_front(4);
        l1.push_front(2);
        let mut l2 = l1.clone();
        l2.push_front(3);
        assert_ne!(l1, l2);
    }
    #[test]
    fn test_iter() {
        let mut l1: ForwardLinkedList<i32> = ForwardLinkedList::new();
        l1.push_front(1);
        l1.push_front(2);
        l1.push_front(4);
        l1.push_front(2);
        let mut vec1 = vec![];
        let mut vec2 = vec![];
        for v in &l1 {
            vec1.push(*v);
        }
        for v in &l1 {
            vec2.push(*v);
        }
        assert_eq!(vec1, vec2);
    }
    #[test]
    fn test_into_iter() {
        let mut l1: ForwardLinkedList<i32> = ForwardLinkedList::new();
        l1.push_front(1);
        l1.push_front(2);
        l1.push_front(4);
        l1.push_front(2);
        let mut vec1 = vec![];
        let vec2 = vec![];
        for v in l1 {
            vec1.push(v);
        }
        // no!!!
        // for v in l1 {
        //     vec2.push(v);
        // }
        assert_ne!(vec1, vec2);
        println!("vec1: {:?}\nvec2: {:?}", vec1, vec2);
    }
}

fn main() {}
