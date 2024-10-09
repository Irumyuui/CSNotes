#include <atomic>
#include <iostream>

template <typename T>
class LockFreeStack {
   private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(std::move(value)) {}
    };

    std::atomic<Node*> top_;

   public:
    explicit LockFreeStack() : top_(nullptr) {}
    ~LockFreeStack() {
        auto node = top_.load();
        while (node) {
            auto next = node->next;
            delete node;
            node = next;
        }
    }

    void push(T data) {
        auto new_node = new Node(std::move(data));
        do {
            new_node->next = top_.load();
        } while (!top_.compare_exchange_weak(new_node->next, new_node));
    }

    bool pop(T& ret) {
        Node* result = nullptr;
        do {
            result = top_.load(std::memory_order_relaxed);
        } while (!top_.load() || !top_.compare_exchange_weak(result, result->next));

        if (result == nullptr) [[unlikely]] {
            return false;
        }
        ret = std::move(result->data);
        return true;
    }
};

int main() {
    auto stk = LockFreeStack<int>();

    std::cout << "push" << '\n';

    stk.push(1);
    stk.push(2);
    stk.push(3);

    std::cout << "pop" << '\n';

    for (int i = 0; i < 3; i ++) {
        int x;
        std::cout << stk.pop(x) << ' ';
        std::cout << x << '\n';
    }
}