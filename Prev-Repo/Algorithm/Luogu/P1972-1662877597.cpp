#include <bits/stdc++.h>
using namespace std;
struct Fread {
	char *p1, *p2, buf[100000];
	constexpr char nextchar() noexcept {
		return (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++);
	}
	template <class T> void read(T &val) noexcept {
		val = 0;
		int f = 1;
		char ch = nextchar();
		while (ch < 48 || ch > 57) {
			if (ch == '-') {
				f = -1;
			}
			ch = nextchar();
		}
		while (ch >= 48 && ch <= 57) {
			val = val * 10 + ch - 48, ch = nextchar();
		}
		val *= f;
	}
	template <class T> Fread& operator >> (T &val) noexcept {
		this->read(val);
		return *this;
	}
} fin;

struct Fwrite {
	template <class T> void write(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
	void write(char x) { putchar(x); }
	void write(const char *x) { puts(x); }
	template <class T> Fwrite& operator << (const T &x) {
		this->write(x);
		return *this;
	}
} fout;

const int N = 5e6 + 10;

struct Node {
	int val = 0;
	int lc = 0, rc = 0;
} seg[N * 10];
int ver[N], last[N];

int tt = 0;
inline int getNode() noexcept {
	return ++ tt;
}

inline void rise(int id) noexcept {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

inline void build(int l, int r, int &id) noexcept {
	id = getNode();
	if (l == r) {
		
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, seg[id].lc);
		build(mid + 1, r, seg[id].rc);
	}
}

inline void change(int l, int r, int oid, int &nid, int tag, int d) noexcept {
	nid = getNode();
	if (l == r) {
		seg[nid].val = d;
	} else {
		int mid = l + ((r - l) >> 1);
		seg[nid].lc = seg[oid].lc;
		seg[nid].rc = seg[oid].rc;
		if (tag <= mid) {
			change(l, mid, seg[oid].lc, seg[nid].lc, tag, d);
		} else {
			change(mid + 1, r, seg[oid].rc, seg[nid].rc, tag, d);
		}
		rise(nid);
	}
}

inline int query(int l, int r, int id, int ql, int qr) noexcept {
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

int main() {
	int n;
	fin >> n;
	build(1, n, ver[0]);
	for (int i = 1; i <= n; ++ i) {
		int x;
		fin >> x;
		change(1, n, ver[i - 1], ver[i], i, 1); 
		if (last[x]) {
			change(1, n, ver[i], ver[i], last[x], 0);
		}
		last[x] = i;
	}
	int q;
	fin >> q;
	while (q --) {
		int l, r;
		fin >> l >> r;
		fout << query(1, n, ver[r], l, r) << '\n';
	}
}