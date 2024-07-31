#include <bits/stdc++.h>
using namespace std;

#if !defined (ONLINE_JUDGE)
#include "debug.hpp"
#else
#define debug(...) // なんでもいい
#endif

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = int64_t;

const int N = 1e5 + 10;
using Info = int;
struct Node {
	Info val;
	int lc, rc;
	Node(Info val = {}, int lc = 0, int rc = 0)
		: val{val}, lc{lc}, rc{rc} {}
};
std::vector<Node> seg{{}};

int GetNode() {
	seg.emplace_back(Node{});
	return int(seg.size()) - 1;
}

void rise(int id) {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

void add(int l, int r, int &id, int tag, int d) {
	debug(l, r, id, tag, d);
	if (!id) id = GetNode();
	if (l == r) {
		seg[id].val += d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) add(l, mid, seg[id].lc, tag, d);
		else add(mid + 1, r, seg[id].rc, tag, d);
		rise(id);
	}
}

void Merge(int l, int r, int &a, int &b) {
	if (!a) {
		a = b;
	} else if (!b) {
		return;
	} else {
		if (l == r) {
			seg[a].val += seg[b].val;
		} else {
			int mid = l + ((r - l) >> 1);
			Merge(l, mid, seg[a].lc, seg[b].lc);
			Merge(mid + 1, r, seg[a].rc, seg[b].rc);
			rise(a);
		}
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query(l, mid, seg[id].lc, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, seg[id].rc, ql, qr);
		} else {
			return query(l, mid, seg[id].lc, ql, mid) + query(mid + 1, r, seg[id].rc, mid + 1, qr);
		}
	}
}

void Main() {
	seg.reserve(N * 60);
	int n;
	cin >> n;
	vector<int> vw(n + 1, -inf<int>);
	for (int i = 1; i <= n; i ++) {
		cin >> vw[i];
	}
	debug(1);
	auto tmp = vw;
	ranges::sort(tmp);
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	for (auto &x : vw | views::drop(1)) {
		x = ranges::lower_bound(tmp, x) - tmp.begin();
	}
	vector adj(n + 1, vector<int>());
	for (int i = 2; i <= n; i ++) {
		int x;
		cin >> x;
		adj[i].emplace_back(x);
		adj[x].emplace_back(i);
	}
	debug(2);
	vector<int> ans(n + 1), root(n + 1);
	auto dfs = [&](auto &&dfs, int from, int come) -> void {
		debug(from, come);
		add(1, n, root[from], vw[from], 1);
		for (auto to : adj[from]) {
			if (to != come) {
				dfs(dfs, to, from);
				Merge(1, n, root[from], root[to]);
			}
		}
		if (vw[from] + 1 <= n)
			ans[from] = query(1, n, root[from], vw[from] + 1, n);
	};
	dfs(dfs, 1, 0);
	debug(3);
	for (auto x : ans | views::drop(1)) {
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}