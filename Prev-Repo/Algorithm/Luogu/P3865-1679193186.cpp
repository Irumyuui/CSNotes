#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

namespace Data_Structure_SparseTable {
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
using Data_Structure_SparseTable::SparseTable;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}

	SparseTable st(n, Data_Structure_SparseTable::ST_Info::Max_Info<int>{-inf<int>});
	st.init<int>(a);
	st.build();
	
	for (int _ = 1; _ <= q; _ ++) {
		int l, r;
		cin >> l >> r;
		cout << st.query(l, r).val << '\n';
	}
}