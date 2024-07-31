#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

const int N = 2e5 + 10;
struct Info {
	i64 val;
	Info(i64 val = {}) : val{val} {}
	Info operator + (const Info &o) const {
		return Info{val + o.val};
	}
};
struct Node {
	Info val;
	int lc, rc;
	Node(const Info val = {}, int lc = 0, int rc = 0)
		: val{val}, lc{lc}, rc{rc} {}
};
vector<Node> seg{{}};

int GetNode() {
	seg.emplace_back(Node{});
	return int(seg.size()) - 1;
}

void rise(int id) {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

void add(int l, int r, int &id, int tag, int d) {
	if (!id) id = GetNode();
	if (l == r) {
		seg[id].val.val += d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) add(l, mid, seg[id].lc, tag, d);
		else add(mid + 1, r, seg[id].rc, tag, d);
		rise(id);
	}
}

void Main() {
	seg.reserve(N * 30);

	int n;
	cin >> n;
	i64 ans = 0;
	auto build = [&](auto &&build) -> int {
		int x;
		cin >> x;
		if (x == 0) {
			int lroot = build(build);
			int rroot = build(build);
			i64 cnt = 0, rcnt = 0;
			auto Merge = [&](auto &&Merge, int l, int r, int &aid, int &bid) {
				if (!aid) {
					aid = bid;
				} else if (!bid) {
					return;
				} else {
					if (l == r) {
						seg[aid].val.val += seg[bid].val.val;
					} else {
						int mid = l + ((r - l) >> 1);
						cnt += seg[seg[aid].rc].val.val * seg[seg[bid].lc].val.val;
						rcnt += seg[seg[aid].lc].val.val * seg[seg[bid].rc].val.val;
						Merge(Merge, l, mid, seg[aid].lc, seg[bid].lc);
						Merge(Merge, mid + 1, r, seg[aid].rc, seg[bid].rc);
						rise(aid);
					}
				}
			};
			Merge(Merge, 1, n, lroot, rroot);
			ans += min(cnt, rcnt);
			return lroot;
		} else {
			int root = 0;
			add(1, n, root, x, 1);
			return root;
		}
	};
	build(build);
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}