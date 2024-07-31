#include <bit>
#include <iostream>
#include <vector>

template <typename _Tp, typename _Oper> class SparseTable {
private:
    std::vector<std::vector<_Tp>> _f;
    _Oper _oper;
    std::size_t _n;

    explicit SparseTable(std::size_t n, _Tp value, _Oper oper)
        : _f(std::bit_width(n), std::vector<_Tp>(n, value)),
          _oper(std::move(oper)), _n(n) {}

public:
    template <std::input_iterator Iter, typename Oper>
        requires requires(typename std::iterator_traits<Iter>::value_type x,
                          Oper oper) {
            {
                oper(x, x)
            } -> std::same_as<typename std::iterator_traits<Iter>::value_type>;
        }
    explicit SparseTable(Iter first, Iter last, Oper oper)
        : SparseTable(std::distance(first, last), (typename Iter::value_type){},
                      std::move(oper)) {
        for (auto target = first, it = _f[0].begin(); target != last;
             ++target, ++it) {
            *it = *target;
        }

        for (std::size_t i = 1; i < _f.size(); i++) {
            for (std::size_t j = 0; j + (1 << i) - 1 < _n; j++) {
                _f[i][j] = _oper(_f[i - 1][j], _f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    _Tp Ask(std::size_t l, std::size_t r) const {
        auto s = std::bit_width(r - l) - 1;
        return _oper(_f[s][l], _f[s][r - (1 << s)]);
    }

    std::size_t Size() const { return _n; }
};

template <typename Iter, typename Oper>
explicit SparseTable(Iter, Iter, Oper)
    -> SparseTable<typename std::iterator_traits<Iter>::value_type, Oper>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &item : a) {
        std::cin >> item;
    }

    SparseTable st(a.begin(), a.end(),
                   [](int a, int b) { return std::max(a, b); });

    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        std::cout << st.Ask(l, r) << '\n';
    }
}