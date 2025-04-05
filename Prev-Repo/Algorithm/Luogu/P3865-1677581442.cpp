#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

namespace Data_Structure_SparseTable {	
	template <typename Info>
		requires requires(Info a, Info b) { {a + b} -> std::convertible_to<Info>; }
	struct SparseTable {
		int n;
		std::vector<std::vector<Info>> f;

		SparseTable(int _n, const Info &__init_v = Info{}) 
			: n(_n), f(std::__lg(_n) + 1, std::vector<Info>(_n + 1, __init_v)) {}

		template <typename T, typename Container, typename Transfrom>
			requires requires(Container a, int idx, T b, Transfrom func) {
				{a[idx]} -> std::convertible_to<T>;
				{func(b)} -> std::convertible_to<Info>;
			}
		auto init(const Container &a, const Transfrom &trans) -> void {
			for (int i = 1; i <= n; i ++) {
				f[0][i] = trans(a[i]);
			}
		}

		auto build() -> void {
			for (int i = 1; i <= std::__lg(n); i ++)
				for (int j = 1; j + (1 << i) - 1 <= n; j ++)
					f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
		}

		auto query(int l, int r) -> Info {
			int s = std::__lg(r - l + 1);
			return f[s][l] + f[s][r - (1 << s) + 1];
		}
	};
}
using Data_Structure_SparseTable::SparseTable;

auto Solve() -> void {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}

	struct Info {
		int val;
		Info(int v = {}) : val{v} {}
		Info operator + (const Info &b) const {
			return Info{max(val, b.val)};
		}
	};
	SparseTable<Info> st(n, {-inf<int>});
	st.init<int>(a, [](const auto &x) -> Info {
		return x;
	});

	st.build();
	for (int i = 0; i < q; i ++) {
		int l, r;
		cin >> l >> r;
		cout << st.query(l, r).val << '\n';
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}