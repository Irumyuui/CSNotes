/* P2982 [USACO10FEB]Slowing down G */
#include <bits/stdc++.h>
using namespace std;

#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e5 + 10;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int son[N], fa[N], siz[N], dfn[N], rnk[N], dep[N], top[N];
int stamp = 0;

void build(int root) {
	function<void(int)> dfs1 = [&](int from) {
		son[from] = -1;
		siz[from] = 1;
		for (auto to : edge[from]) {
			if (dep[to] == -1) {
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
		top[from] = root;
		dfn[from] = ++ stamp;
		rnk[stamp] = root;
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

	memset(dep, -1, sizeof dep);
	dep[root] = stamp = 0;
	dfs1(root);
	dfs2(root,root);
}

struct Info {
	int val;
	void init(int x) { val = x; }
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.val + b.val,
		};
	}
};
struct Node {
	Info val;
	int lz_a;
} seg[N << 2];

void update(int l, int r, int id, int d) {
	seg[id].val.val += (r - l + 1) * d;
	seg[id].lz_a += d;
}

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void down(int l, int r, int id) {
	if (seg[id].lz_a == 0) {
		return;
	}
	auto &d = seg[id].lz_a;
	int mid = l + ((r - l) >> 1);
	update(l, mid, id * 2, d);
	update(mid + 1, r, id * 2 + 1, d);
	d = 0;
}

void add(int l, int r, int id, int al, int ar, int d) {
	if (l == al && r == ar) {
		update(l, r, id, d);
	} else {
		int mid = l + ((r - l ) >> 1);
		down(l, r, id);
		if (ar <= mid) {
			add(l, mid, id * 2, al, ar, d);
		} else if (al > mid) {
			add(mid + 1, r, id * 2 + 1, al, ar, d);
		} else {
			add(l, mid, id * 2, al, mid, d);
			add(mid + 1, r, id * 2 + 1, mid + 1, ar, d);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

void Solution() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		cout << query(1, n, 1, dfn[x], dfn[x]).val << '\n';
		add(1, n, 1, dfn[x], dfn[x] + siz[x] - 1, 1);
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}