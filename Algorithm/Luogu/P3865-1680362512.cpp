#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#if __cplusplus >= 202002L
	namespace rgs = std::ranges;
#endif
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

namespace Royal_Guard::Data_Structure::Requires_DS::SparseTable {
	namespace ST_Info {
		template <typename Value>
			requires requires(Value v) { {std::max<Value>(v, v)}; }
		struct Max_Info {
			Value val;
			Max_Info(const Value &v = {}) : val{v} {}
			constexpr auto operator <=> (const Max_Info &that) const = default;
			constexpr auto operator + (const Max_Info &x) const -> Max_Info {
				return Max_Info{ std::max<Value>({val, x.val}) };
			}
		};

		template <typename Value>
			requires requires(Value v) { {std::min<Value>(v, v)}; }
		struct Min_Info {
			Value val;
			Min_Info(const Value &v = {}) : val{v} {}
			constexpr auto operator <=> (const Min_Info &that) const = default;
			constexpr auto operator + (const Min_Info &x) const -> Min_Info {
				return Min_Info{ std::min<Value>({val, x.val}) };
			}
		};
	};

	namespace __DS_ST_SP {
		template <typename Ret>
		struct Translate {
			template <typename Val>
				requires requires(Val v) { {Ret{v}}; }
			constexpr auto operator () (const Val &v) const -> Ret {
				return Ret{v};
			}
		};
	}

	template <typename Info>
		requires requires(Info a, Info b) { {a + b} -> std::convertible_to<Info>; }
	struct SparseTable {
		int n;
		std::vector<std::vector<Info>> f;

		explicit SparseTable(int _n, const Info &__init_v = Info{}) 
			: n(_n), f(std::__lg(_n) + 1, std::vector<Info>(_n + 1, __init_v)) {}

		template <typename T, typename Container, typename Transfrom = __DS_ST_SP::Translate<Info>>
			requires requires(Container a, int idx, T b, Transfrom func) {
				{a[idx]} -> std::convertible_to<T>;
				{func(b)} -> std::convertible_to<Info>;
			}
		auto init(const Container &a, const Transfrom &trans = Transfrom{}) -> void {
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
using Royal_Guard::Data_Structure::Requires_DS::SparseTable::SparseTable;

void Main() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	using Info = Royal_Guard::Data_Structure::Requires_DS::SparseTable::ST_Info::Max_Info<int>;
	SparseTable<Info> f(n, {-inf<int>});
	f.init<int>(a);
	f.build();
	while (q --) {
		int l, r;
		cin >> l >> r;
		cout << f.query(l, r).val << '\n';
	}
}

std::int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Main();
	}
}