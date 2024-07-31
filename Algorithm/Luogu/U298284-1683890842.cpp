#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include ".vscode/debug.hpp"
#else
	#define debug(...)
#endif

template <typename _Tp, typename _Cmp = std::greater<_Tp>, typename _Seq = std::vector<_Tp>>
using PriorityQueue = std::priority_queue<_Tp, _Seq, _Cmp>;
template <typename _Tp, typename _Seq = std::vector<_Tp>>
using Stack = std::stack<_Tp, _Seq>;
using i64 = int64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

struct Macro {};
template <> struct std::ranges::view_interface<Macro> {
	static void Main();
};

using namespace std;

auto std::ranges::view_interface<Macro>::Main() -> void {
	int n;
	cin >> n;

	vector adj1(n + 1, vector<int>{}), adj2(adj1);
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj1[u].emplace_back(v);
		adj1[v].emplace_back(u);
	}
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj2[u].emplace_back(v);
		adj2[v].emplace_back(u);
	}

	vector<int> dfn(n + 1), rnk(dfn), siz(dfn);
	auto dfs1 = [&, stamp{0}](auto &&dfs, int from, int come) mutable -> void {
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		siz[from] = 1;
		for (auto to : adj1[from]) {
			if (to != come) {
				dfs(dfs, to, from);
				siz[from] += siz[to];
			}
		}
	};
	dfs1(dfs1, 1, 0);
	
	struct Info {
		int val;
		Info(int val = {}) : val{val} {}
		Info operator + (const Info &x) {
			return Info{val + x.val};
		}
	};
	struct Node {
		Info val;
		int lz;
		Node(const Info &val = {}, const int &lz = {}) : val{val}, lz{lz} {}
	};
	vector<Node> seg((n + 10) * 4);

	auto rise = [&](int id) {
		seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
	};
	auto update = [&](int l, int r, int id, int d) {
		seg[id].lz += d;
        if (l != r) {
            return;
        }
		seg[id].val.val += (r - l + 1) * d;
	};
	auto down = [&](int l, int r, int id) {
		if (seg[id].lz != 0) {
			int mid = l + ((r - l) >> 1);
			update(l, mid, id * 2, seg[id].lz);
			update(mid + 1, r, id * 2 + 1, seg[id].lz);
			seg[id].lz = 0;
		}	
	};

	auto modify = [&](auto &&dfs, int l, int r, int id, int ml, int mr, int d) -> void {
		if (l == ml && r == mr) {
			update(l, r, id, d);
		} else {
			int mid = l + ((r - l) >> 1);
			down(l, r, id);
			if (mr <= mid) {
				dfs(dfs, l, mid, id * 2, ml, mr, d);
			} else if (ml > mid) {
				dfs(dfs, mid + 1, r, id * 2 + 1, ml, mr, d);
			} else {
				dfs(dfs, l, mid, id * 2, ml, mid, d);
				dfs(dfs, mid + 1, r, id * 2 + 1, mid + 1, mr, d);
			}
			rise(id);
		}
	};

	auto query = [&](auto &&dfs, int l, int r, int id, int ql, int qr) -> Info {
		if (l == ql && r == qr) {
			return seg[id].val;
		} else {
			int mid = l + ((r - l) >> 1);
			down(l, r, id);
			if (qr <= mid) {
				return dfs(dfs, l, mid, id * 2, ql, qr);
			} else if (ql > mid) {
				return dfs(dfs, mid + 1, r, id * 2 + 1, ql, qr);
			} else {
				return dfs(dfs, l, mid, id * 2, ql, mid) + dfs(dfs, mid + 1, r, id * 2 + 1, mid + 1, qr);
			}
		}
	};

	i64 ans = 0;
	auto dfs2 = [&](auto &&dfs, int from, int come) -> void {
		ans += query(query, 1, n, 1, dfn[from], dfn[from]).val;
		modify(modify, 1, n, 1, dfn[from], dfn[from] + siz[from] - 1, 1);
		for (auto to : adj2[from]) {
			if (to != come) {
				dfs(dfs, to, from);
			}
		}
		modify(modify, 1, n, 1, dfn[from], dfn[from] + siz[from] - 1, -1);
	};
	dfs2(dfs2, 1, 0);

	cout << ans << '\n';
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);

	int test = 1;
	// std::cin >> test;

	for (int rp = 1; test --> 0; rp ++) {
		debug(rp);
		std::ranges::view_interface<Macro>::Main();
	}
}