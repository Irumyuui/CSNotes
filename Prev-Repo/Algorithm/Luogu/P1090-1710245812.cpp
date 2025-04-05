#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

template <typename Ty, typename Compare, typename Container = std::vector<Ty>>
  requires requires(Compare comp, Ty a, Ty b) {
    std::is_same_v<bool, decltype(comp(a, b))>;
  } &&
           requires(Container cont, Ty value) {
             std::is_same_v<decltype(cont[0]), Ty>;
             std::is_same_v<decltype(cont.front()), Ty>;
             std::is_same_v<decltype(cont.back()), Ty>;
             cont.push_back(value);
             cont.emplace_back(value);
             cont.emplace_back(std::move(value));
             cont.pop_back();
           } && requires(const Container cont) {
             std::is_same_v<decltype(cont.front()), Ty>;
             std::is_same_v<decltype(cont.back()), Ty>;
             std::is_same_v<decltype(cont.size()), std::size_t>;
             std::is_same_v<decltype(cont.empty()), bool>;
           }
class BinaryHeap {
public:
  BinaryHeap() : cont_(), comp_() {}

  explicit BinaryHeap(const Compare &comp) : cont_(), comp_(comp) {}

  explicit BinaryHeap(Compare comp) : cont_(), comp_(std::move(comp)) {}

  BinaryHeap(const BinaryHeap &other)
      : cont_(other.cont_), comp_(other.comp_) {}

  BinaryHeap(BinaryHeap &&other)
      : cont_(std::move(other.cont_)), comp_(std::move(other.comp_)) {}

  template <typename Comp, typename Cont>
  explicit BinaryHeap(Comp &&comp, Cont &&cont)
      : cont_(std::forward<Cont>(cont)), comp_(std::forward<Comp>(comp)) {
    for (int i = static_cast<int>(this->cont_.size()) - 1; i >= 0; i--) {
      this->Down(i);
    }
  }

  auto operator=(BinaryHeap other) -> BinaryHeap & {
    this->Swap(other);
    return *this;
  }

  auto Swap(BinaryHeap &other) noexcept -> void {
    std::swap(this->cont_, other.cont_);
    std::swap(this->comp_, other.comp_);
  }

public:
  auto Size() const noexcept -> std::size_t { return this->cont_.size(); }

  auto Empty() const noexcept -> bool { return this->cont_.empty(); }

  auto Push(Ty value) -> void {
    this->cont_.emplace_back(std::move(value));
    this->Up(this->Size() - 1);
  }

  template <typename... Ts>
    requires requires(Ts &&...args) { Ty(std::forward<Ts>(args)...); }
  auto Emplace(Ts &&...args) -> void {
    this->cont_.emplace_back(std::forward<Ts>(args)...);
    this->Up(this->Size() - 1);
  }

  auto Top() const -> const Ty & { return this->cont_[0]; }

  auto Top() -> Ty & { return this->cont_[0]; }

  auto Pop() -> void {
    std::swap(this->cont_.front(), this->cont_.back());
    this->cont_.pop_back();
    this->Down(0);
  }

private:
  auto Up(std::size_t idx) -> void {
    while (idx > 0 &&
           this->comp_(this->cont_[idx], this->cont_[(idx - 1) / 2])) {
      std::swap(this->cont_[(idx - 1) / 2], this->cont_[idx]);
      idx = (idx - 1) / 2;
    }
  }

  auto Down(std::size_t idx) -> void {
    while (idx * 2 + 1 < this->Size()) {
      auto t = idx * 2 + 1;
      if (t + 1 < this->Size() &&
          this->comp_(this->cont_[t + 1], this->cont_[t])) {
        t += 1;
      }
      if (this->comp_(this->cont_[idx], this->cont_[t])) {
        break;
      }
      std::swap(this->cont_[idx], this->cont_[t]);
      idx = t;
    }
  }

private:
  Container cont_;
  Compare comp_;
};

template <typename Comp, typename Cont>
BinaryHeap(Comp &&, Cont &&)
    -> BinaryHeap<typename Cont::value_type, Comp, Cont>;

auto main() -> int {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  BinaryHeap<int, std::less<int>> heap;

  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    heap.Emplace(x);
  }

  int res = 0;
  if (heap.Size() == 1) {
    res = heap.Top();
  }
  while (heap.Size() > 1) {
    int a = heap.Top();
    heap.Pop();
    int b = heap.Top();
    heap.Pop();
    heap.Push(a + b);
    res += a + b;
  }

  std::cout << res << '\n';
}
