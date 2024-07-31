#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <debug.hpp>
#else
#define debug(...) // Sad.
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
std::mt19937 mrand(std::chrono::system_clock::now().time_since_epoch().count());
using uint = uint32_t;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using namespace std;

template <class Info>
struct SegTree {
	struct Node {
		Info val;
		Node() : val() {}
	};
	std::vector<Node> seg;
	int n;
	SegTree(int _n) : seg(_n * 4, Node()), n(_n) {}
	// [l, r]
	template<class T> SegTree(const T &a, int l, int r, int _n) : seg(_n * 4, Node()), n(_n) {
		build(a, l, r, 1);
	}
	void rise(int id) {
		seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
	}
	template<class T> void build(const T &a, int l, int r, int id) {
		if (l == r) {
			seg[id].val = a[l];
		} else {
			int mid = l + ((r - l) >> 1);
			build(a, l, mid, id * 2);
			build(a, mid + 1, r, id * 2 + 1);
			rise(id);
		}
	}
	// Opt(Info &x, T d);
	template <class Opt, class T> void modify(int tag, T d, Opt opt) {
		static auto modify = [&](auto &&self, int l, int r, int id) -> void {
			if (l == r) {
				opt(seg[id].val, d);
			} else {
				int mid = l + ((r - l) >> 1);
				if (tag <= mid) {
					self(self, l, mid, id * 2);
				} else {
					self(self, mid + 1, r, id * 2 + 1);
				}
				rise(id);
			}
		};
		modify(modify, 1, n, 1);
	}
	Info query(int ql, int qr) {
		static auto query = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
			if (l == ql && r == qr) {
				return seg[id].val;
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
		return query(query, 1, n, 1, ql, qr);
	}
};

void opti(int &a, int d) {
    a += d;
}

void Solution() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
	}
	SegTree<int> seg(a, 0, n - 1, n);
	while (q --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, k;
			cin >> x >> k;
			seg.modify(x, k, opti);
		} else {
			int l, r;
			cin >> l >> r;
			cout << seg.query(l, r) << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}