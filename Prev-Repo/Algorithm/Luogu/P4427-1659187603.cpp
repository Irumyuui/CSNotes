/* File: P4427 [BJOI2018]求和 */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 1e6 + 10;
vector<int> edge[N];

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int dfn[N], dep[N], son[N], siz[N], top[N], fa[N], stamp = 0;
int w[N];
void dfs1(int from) {
	siz[from] = 1;
	son[from] = -1;
	for (auto to : edge[from]) {
		if (dep[to] == -1) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to);
			if (son[from] == -1 || siz[to] > siz[son[from]]) {
				son[from] = to;
			}
		}
	} 
}
void dfs2(int from, int root) {
	top[from] = root;
	dfn[from] = ++ stamp;
	w[dfn[from]] = dep[from];
	if (son[from] == -1) {
		return;
	}
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != son[from] && to != fa[from]) {
			dfs2(to, to);
		}
	}
}

void build(int root) {
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root);
	dfs2(root, root);
}

using ll = long long;

const ll mod = 998244353;
constexpr ll add(ll a, ll b, ll p) {
	return (static_cast<__int128_t>(a) + b) % p;
}
constexpr ll mul(ll a, ll b, ll p) {
	a %= p; b %= p;
	ll d = static_cast<long double>(a) * b / p;
	d = a * b - d * p;
	if (d < 0) d += p; if (d >= p) d -= p;
	return d;
}
constexpr ll power(ll a, ll i, ll p) {
	ll ret = 1;
	for (; i; i >>= 1, a = mul(a, a, p)) {
		if (i & 1) {
			ret = mul(ret, a, p);
		}
	}
	return ret;
}

struct Info {
	array<ll,51> val;
} seg[N << 2];

void rise(int id) {
	for (int i = 1; i <= 50; ++ i) {
		seg[id].val[i] = add(seg[id * 2].val[i], seg[id * 2 + 1].val[i], mod);
	}
}
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val[1] = w[l];
		for (int i = 2; i <= 50; ++ i) {
			seg[id].val[i] = mul(seg[id].val[i - 1], w[l], mod);
		}
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}
ll query(int l, int r, int id, int sl, int sr, int k) {
	debug(l, r, sl, sr);
	if (l == sl && r == sr) {

		debug(seg[id].val, id, l, r);

		return seg[id].val[k];
	} else {
		int mid = l + ((r - l) >> 1);
		if (sr <= mid) {
			return query(l, mid, id * 2, sl, sr, k);
		} else if (sl > mid) {
			return query(mid + 1, r, id * 2 + 1, sl, sr, k);
		} else {
			return add(query(l, mid, id * 2, sl, mid, k), query(mid + 1, r, id * 2 + 1, mid + 1, sr, k), mod);
		}
	}
}

int n;

ll query(int a, int b, int k) {
	ll ret = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		debug(ret, dfn[top[a]], dfn[a]);
		ret = add(ret, query(1, n, 1, dfn[top[a]], dfn[a], k), mod);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	
	ret = add(ret, query(1, n, 1, dfn[a], dfn[b], k), mod);
	return ret;
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}

	build(1);
	build(1, n, 1);

	int q;
	cin >> q;

	debug(1);

	while (q --) {
		debug(q);
		int a, b, k;
		cin >> a >> b >> k;
		cout << query(a, b, k) << '\n'; 
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}