#include <bit>
#include <concepts>
#include <iostream>
#include <vector>

template <typename _Ty, typename _Oper>
class SparseTable {
private:
    std::vector<std::vector<_Ty>> _f;
    _Oper _oper;
    std::size_t _n;

public:
    using value_type = _Ty;
    using operator_type = _Oper;

private:
    explicit SparseTable(std::size_t n, _Ty value, _Oper oper)
        : _f(std::bit_width(n), std::vector<_Ty>(n, value)),
          _oper(std::move(oper)), _n(n) {}

public:
    template <std::input_iterator __Iter, typename __Oper>
        requires requires(typename std::iterator_traits<__Iter>::value_type x,
                          __Oper oper) {
            {
                oper(x, x)
            }
            -> std::same_as<typename std::iterator_traits<__Iter>::value_type>;
        }
    explicit SparseTable(__Iter first, __Iter last, __Oper oper)
        : SparseTable(std::distance(first, last),
                      (typename __Iter::value_type){}, std::move(oper)) {
        std::copy(first, last, _f[0].begin());

        for (std::size_t i = 1; i < _f.size(); i++) {
            for (std::size_t j = 0; j + (1 << i) - 1 < _n; j++) {
                _f[i][j] = _oper(_f[i - 1][j], _f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    auto Ask(std::size_t l, std::size_t r) const -> _Ty {
        auto s = std::bit_width(r - l) - 1;
        return _oper(_f[s][l], _f[s][r - (1 << s)]);
    }

    auto Size() const noexcept -> std::size_t {
        return _n;
    }
};

template <typename __Iter, typename __Oper>
explicit SparseTable(__Iter, __Iter, __Oper)
    -> SparseTable<typename std::iterator_traits<__Iter>::value_type, __Oper>;

auto main() -> int {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &item : a) {
        std::cin >> item;
    }

    SparseTable st(
        a.begin(), a.end(), [](int a, int b) { return std::max(a, b); });

    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        std::cout << st.Ask(l, r) << '\n';
    }
}