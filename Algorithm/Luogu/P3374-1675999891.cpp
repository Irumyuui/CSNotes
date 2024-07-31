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

template <typename T>
concept __Info = requires(T a, T b) {
	{a + b} -> std::same_as<T>;
};
template <typename Func, typename RetT, typename T>
concept __InitFunc = requires(Func init_func, T value) {
	{init_func(value)} -> std::same_as<RetT>;
};
template <typename T>
concept __Arr = requires(T a, int idx) {
	{a[idx]};
};
template <typename Func, typename T1, typename T2>
concept __OptFunc = requires(Func func, T1 a, T2 b) {
	{func(a, b)} -> std::same_as<T1>;
};

template <__Info Info>
struct SegmentTree {
	std::vector<Info> seg;
	int n;
	
	SegmentTree(int _n, const Info &v) : seg(_n * 4, v), n(_n) {}

	template <typename T, __Arr Arr, __InitFunc<Info,T> Trans>
	void build(const Arr &a, const Trans &trans_func) {
		static auto dfs = [&](auto &&self, int l, int r, int id) -> void {
			if (l == r) {
				seg[id] = trans_func(a[l]);
			} else {
				int mid = l + ((r - l) >> 1);
				self(self, l, mid, id * 2);
				self(self, mid + 1, r, id * 2 + 1);
				seg[id] = seg[id * 2] + seg[id * 2 + 1];
			}
		};
		dfs(dfs, 1, n, 1);
	}

	template <typename T, __OptFunc<Info,T> OptFunc>
	void change(int tag, T d, const OptFunc &opt_func) {
		static auto dfs = [&](auto &&self, int l, int r, int id) -> void {
			if (l == r) {
				seg[id] = opt_func(seg[id], d);
			} else {
				int mid = l + ((r - l) >> 1);
				if (tag <= mid) {
					self(self, l, mid, id * 2);
				} else {
					self(self, mid + 1, r, id * 2 + 1);
				}
				seg[id] = seg[id * 2] + seg[id * 2 + 1];
			}
		};
		dfs(dfs, 1, n, 1);
	}

	Info query(int _ql, int _qr) {
		static auto dfs = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
			if (l == ql && r == qr) {
				return seg[id];
			} else {
				int mid = l + ((r - l) >> 1);
				if (qr <= mid) {
					return self(self, l, mid, id * 2, ql, qr);
				} else if (ql > mid) {
					return self(self, mid + 1, r, id * 2 + 1, ql, qr);
				} else {
					return self(self, l, mid, id * 2, ql, mid) + self(self, mid + 1, r, id * 2 + 1, mid + 1, qr);
				}
			}
		};
		return dfs(dfs, 1, n, 1, _ql, _qr);
	}
};

auto Solve() -> void {
	int n, q;
	cin >> n >> q;
	vector<ll> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	SegmentTree<ll> seg(n, 0);
	seg.build<ll>(a, [](const auto &x) { return x; });
	while (q --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, k;
			cin >> x >> k;
			seg.change<ll>(x, k, [](const auto &a, const auto &b) {
				return a + b;
			});
		} else {
			int l, r;
			cin >> l >> r;
			cout << seg.query(l, r) << '\n';
		}
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