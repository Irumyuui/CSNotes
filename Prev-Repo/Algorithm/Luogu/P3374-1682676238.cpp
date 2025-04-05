#include <bits/stdc++.h>
using namespace std;

namespace Trickster {
	namespace PrefixFenwickTreeAble {
		template <typename _Opt, typename _Tp>
		concept OperatorAble = requires(const _Tp a, _Tp b, _Opt op) {
			{op(a, b)} -> std::convertible_to<_Tp>;
		};
	}

	template <typename _Tp, PrefixFenwickTreeAble::OperatorAble<_Tp> _Operator = std::plus<_Tp>>
	class PrefixFenwickTree {
		public:
			using Type = _Tp;
			using Operator = _Operator;

		private:
			constexpr static std::size_t Lowbit(std::size_t x) noexcept {
				return x & -x;
			}

		public:
			explicit PrefixFenwickTree(std::size_t _n, Type &&initValue = {}, const Operator &opt = Operator{})
				: bit(_n + 1, initValue), n{_n}, opt{opt} {}

			void Assign(std::size_t _n, const Type &value) {
				n = _n;
				bit.Assign(_n + 1, value);
			}

			void Set(std::size_t pos, Type &&value) {
				for (std::size_t i = pos; i <= n; i += Lowbit(i)) {
					bit[i] = opt(bit[i], value);
				}
			}

			Type Get(std::size_t pos, Type result = Type{}) const {
				for (std::size_t i = pos; i > 0; i -= Lowbit(i)) {
					result = opt(result, bit[i]);
				}
				return result;
			}

			Type& operator [] (std::size_t pos) {
				return bit[pos];
			}
			const Type& operator [] (std::size_t pos) const {
				return bit[pos];
			}

		private:
			std::vector<Type> bit;
			std::size_t n;
			const Operator opt;
	};
}

using i64 = int64_t;

void Main() {
	int n, q;
	cin >> n >> q;

	Trickster::PrefixFenwickTree<i64> bit(n);
	for (int i = 1; i <= n; i ++) {
		int x;
		cin >> x;
		bit.Set(i, x);
	}

	for (int _ = 1; _ <= q; _ ++) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, k;
			cin >> x >> k;
			bit.Set(x, k);
		} else {
			int l, r;
			cin >> l >> r;
			cout << bit.Get(r) - bit.Get(l - 1) << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}