#include <bits/stdc++.h>
using namespace std;

struct Info {
	int val;
	Info(int val = {}) : val{val} {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info{0};
	}
};
struct Node {
	Info val;
	int lc, rc;
	Node(Info val = {}, int lc = {}, int rc = {}) : val{val}, lc{lc}, rc{rc} {}
};
vector<Node> seg(1);
vector<int> version;

int get_node() {
	seg.emplace_back(Node{});
	return int(seg.size()) - 1;
}
void extend(int now, int pre) {
	seg[now] = seg[pre];
}
void rise(int id) {
	// seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

template <typename T>
void build(int l, int r, int &now, const T &a) {
	now = get_node();
	if (l == r) {
		seg[now].val = a[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, seg[now].lc, a);
		build(mid + 1, r, seg[now].rc, a);
		rise(now);
	}
}

void change(int l, int r, int pre, int &now, int tag, int d) {
	now = get_node();
	extend(now, pre);
	if (l == r) {
		seg[now].val = d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, seg[pre].lc, seg[now].lc, tag, d);
		} else {
			change(mid + 1, r, seg[pre].rc, seg[now].rc, tag, d);
		}
		rise(now);
	}
}

Info query(int l, int r, int now, int tag) {
	if (l == r) {
		return seg[now].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			return query(l, mid, seg[now].lc, tag);
		} else {
			return query(mid + 1, r, seg[now].rc, tag);
		}
	}
}

void Main() {
	seg.reserve(int(2e7));
	
	int n, q;
	cin >> n >> q;
	
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	version.reserve(q + 1);
	version.emplace_back(0);
	build(1, n, version[0], a);
	
	for (int t = 1; t <= q; t ++) {
		int ver, opt;
		cin >> ver >> opt;
		if (opt == 1) {
			int pos, d;
			cin >> pos >> d;
			version.emplace_back(0);
			change(1, n, version[ver], version.back(), pos, d);
		} else {
			int pos;
			cin >> pos;
			version.emplace_back(version[ver]);
			cout << query(1, n, version[ver], pos).val << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}