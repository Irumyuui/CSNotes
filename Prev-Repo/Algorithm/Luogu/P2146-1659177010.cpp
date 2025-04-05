/* Filename: P2146 [NOI2015] 软件包管理器 */
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> edge[N];
int dep[N], son[N], fa[N], top[N], siz[N], dfn[N], rnk[N];
int stamp = 0;

int n;

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

void build(int root) {
	function<void(int)> dfs1 = [&](int from) {
		son[from] = -1;
		siz[from] = 1;
		for (auto to : edge[from]) {
			if (!dep[to]) {
				dep[to] = dep[from] + 1;
				fa[to] = from;
				dfs1(to);
				siz[from] += siz[to];
				if (son[from] == -1 || siz[to] > siz[son[from]]) {
					son[from] = to;
				}
			}
		}
	};
	function<void(int,int)> dfs2 = [&](int from, int root) {
		dfn[from] = ++ stamp;
		rnk[from] = stamp;
		top[from] = root;
		if (son[from] == -1) {
			return;
		}
		dfs2(son[from], root);
		for (auto to : edge[from]) {
			if (to != son[from] && to != fa[from]) {
				dfs2(to, to);
			}
		}
	};

	dep[root] = 1; 
	dfs1(root);
	dfs2(root, root);
}

// __int128_t

int seg[N << 2], lazy[N << 2];
void build(int l, int r, int id) {
	if (l == r) {
		lazy[id] = -1;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		lazy[id] = -1;
	}
}
void rise(int id) {
	seg[id] = seg[id * 2] + seg[id * 2 + 1];
}
void down(int l, int r, int id) {
	auto &d = lazy[id];
	if (d == -1) {
		return;
	}
	int mid = l + ((r - l) >> 1);
	seg[id * 2] = (mid - l + 1) * d;
	seg[id * 2 + 1] = (r - mid) * d;
	lazy[id * 2] = d;
	lazy[id * 2 + 1] = d;
	d = -1;
}
int change(int l, int r, int id, int sl, int sr, int d) {
	if (l == sl && r == sr) {
		int ret = seg[id];
		seg[id] = (r - l + 1) * d;
		lazy[id] = d;
		ret = abs(ret - seg[id]);
		return ret;
	} else {
		int mid = l + ((r - l) >> 1);
		int ret = 0;
		down(l, r, id);
		if (sr <= mid) {
			ret = change(l, mid, id * 2, sl, sr, d);
		} else if (sl > mid) {
			ret = change(mid + 1, r, id * 2 + 1, sl, sr, d);
		} else {
			ret = change(l, mid, id * 2, sl, mid, d) + change(mid + 1, r, id * 2 + 1, mid + 1, sr, d);
		}
		rise(id);
		return ret;
	}
}

int opt1(int x) {
	int ret = 0;
	while (dep[top[x]] > 1) {
		ret += change(1, n, 1, dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
	ret += change(1, n, 1, dfn[top[x]], dfn[x], 1);
	return ret;
}

int opt2(int x) {
	return change(1, n, 1, dfn[x], dfn[x] + siz[x] - 1, 0);
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int x;
		cin >> x;
		add_edge(x, i);
	}
	build(0);

	int q;
	cin >> q;
	while (q --) {
		string opt;
		cin >> opt;
		if (opt == "install") {
			int x;
			cin >> x;
			cout << opt1(x) << '\n';
		} else {
			int x;
			cin >> x;
			cout << opt2(x) << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}