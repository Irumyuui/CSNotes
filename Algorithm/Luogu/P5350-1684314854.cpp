#include <bits/stdc++.h>
using namespace std;

#define cerr

template <int _P>
struct Modint {
	using ll = int64_t;
	static constexpr int P = _P;
	int v;
	Modint() : v(0) {}
	Modint(ll _v) { v = _v % P; if (v < 0)v += P; }
	explicit operator int() const { return v; }
	explicit operator long long() const { return v; }
	explicit operator bool() const { return v > 0; }
	bool operator == (const Modint &o) const { return v == o.v; }
	bool operator != (const Modint &o) const { return v != o.v; }
	Modint operator - () const { return Modint(v ? P - v : 0); }
	Modint operator + () const { return *this; }
	Modint & operator ++ () { v++; if (v == P)v = 0; return *this; }
	Modint & operator -- () { if (v == 0)v = P; v--; return *this; }
	Modint operator ++ (int) { Modint r = *this; ++*this; return r; }
	Modint operator -- (int) { Modint r = *this; --*this; return r; }
	Modint & operator += (const Modint &o) { v += o.v; if (v >= P)v -= P; return *this; }
	Modint operator + (const Modint & o)const { return Modint(*this) += o; }
	Modint & operator -= (const Modint & o) { v -= o.v; if (v < 0)v += P; return *this; }
	Modint operator - (const Modint &o)const { return Modint(*this) -= o; }
	Modint & operator *=(const Modint & o) { v = (int)(((ll)v)*o.v%P); return *this; }
	Modint operator * (const Modint & o)const { return Modint(*this) *= o; }
	Modint & operator /= (const Modint & o) { return (*this) *= o.Inv(); }
	Modint operator / (const Modint & o)const { return Modint(*this) /= o; }
	friend Modint operator + (const Modint &x, const ll &o) { return x + (Modint)o; }
	friend Modint operator + (const ll &o, const Modint &x) { return x + (Modint)o; }
	friend Modint operator - (const Modint &x, const ll &o) { return x - (Modint)o; }
	friend Modint operator - (const ll &o, const Modint &x) { return (Modint)o - x; }
	friend Modint operator * (const Modint &x, const ll &o) { return x * (Modint)o; }
	friend Modint operator * (const ll &o, const Modint &x) { return x * (Modint)o; }
	friend Modint operator / (const Modint &x, const ll &o) { Modint c = o; return x * c.Inv(); }
	friend Modint operator / (const ll &o, const Modint &x) { Modint c = o; return c * x.Inv(); }
	Modint operator ^ (ll o)const { Modint r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
	Modint operator ~ () { return (*this) ^ (P - 2); }
	Modint Inv() const { return (*this) ^ (P - 2); }
	friend std::istream & operator >> (std::istream &in, Modint &x) { ll d; in >> d; x = d; return in; }
	friend std::ostream & operator << (std::ostream &out, const Modint &x) { out << x.v; return out; }
};
using mint = Modint<int(1e9+7)>;

using i64 = int64_t;

template <typename T>
struct BaseChthollyTree {
	std::map<int,T> mp;  // 区间开始 : 数据

	// [l, r)
	BaseChthollyTree(int l, const T &init_val)
		: mp{ {l - 1, init_val} } {
	}

	void Split(int x) {
		auto it = std::prev(mp.upper_bound(x));
		mp[x] = it->second;
	}

	void SplitRange(int l, int r) {
		Split(l);
		Split(r);
	}

	// 删除 [l, r - 1], 建立新区间
	void Assign(int l, int r, const T &v) {
		Split(l); Split(r);
		auto it = mp.find(l);
		while (it->first != r) {
			it = mp.erase(it);
		}
		mp[l] = v;
	}

	void EraseRange(int l, int r) {
		mp.erase(mp.find(l), std::prev(mp.upper_bound(r)));
	}

	// 其他操作
	// void Opt() {}
};

struct ChthollyTree : BaseChthollyTree<mint> {
	ChthollyTree(int l, const mint &init_val) : BaseChthollyTree(l, init_val) {};

	mint GetRangeSum(int l, int r) {
		SplitRange(l, r);
		mint ret = 0;
		for (auto it = mp.find(l); it->first != r; it = std::next(it)) {
			ret += (std::next(it)->first - it->first) * it->second;
		}
		return ret;
	}

	void Add(int l, int r, const mint &d) {
		SplitRange(l, r);
		for (auto it = mp.find(l); it->first != r; it = std::next(it)) {
			it->second += d;
		}
	}

	void SwapRange(int l1, int r1, int l2, int r2) {
		SplitRange(l1, r1); SplitRange(l2, r2);
		
		std::vector<std::pair<int,mint>> rg1, rg2;
		auto GetRange = [&](auto &&vec, int l, int r) {
			for (auto it = mp.find(l); it->first != r; it = std::next(it)) {
				vec.emplace_back(it->first - l, it->second);
			}
		};
		GetRange(rg1, l1, r1);
		GetRange(rg2, l2, r2);

		EraseRange(l1, r1);
		EraseRange(l2, r2);

		for (auto [p, x] : rg1) {
			mp[p + l2] = x;
		}
		for (auto [p, x] : rg2) {
			mp[p + l1] = x;
		}
	}

	void CopyRange(int l1, int r1, int l2, int r2) {
		SplitRange(l1, r1); SplitRange(l2, r2);
		std::vector<std::pair<int,mint>> rg;
		auto GetRange = [&](auto &&vec, int l, int r) {
			for (auto it = mp.find(l); it->first != r; it = std::next(it)) {
				vec.emplace_back(it->first - l, it->second);
			}
		};
		GetRange(rg, l1, r1);

		EraseRange(l2, r2);
		for (auto [p, x] : rg) {
			mp[p + l2] = x;
		}
	}

	void ReverseRange(int l, int r) {
		SplitRange(l, r);
		
		std::vector<std::pair<int,mint>> rg;
		auto GetRange = [&](auto &&vec, int l, int r) {
			for (auto it = mp.find(l); it->first != r; it = std::next(it)) {
				vec.emplace_back(std::next(it)->first - 1, it->second);
			}
		};
		GetRange(rg, l, r);

		EraseRange(l, r);
		for (auto [p, x] : rg) {
			mp[(r - l) - (p - l) - 1 + l] = x;
		}
	}
};

void Main() {
	int n, q;
	cin >> n >> q;
	
	ChthollyTree cht(1, 0);
	for (int i = 1; i <= n; i ++) {
		mint x;
		cin >> x;
		cht.mp[i] = x;

		// cerr << x << '\n';
	}

	for (int _ = 1; _ <= q; _ ++) {
		int opt;
		cin >> opt;

		if (opt == 1) {
			int l, r;
			cin >> l >> r;
			cout << cht.GetRangeSum(l, r + 1) << '\n';
		} else if (opt == 2) {
			int l, r;
			mint val;
			cin >> l >> r >> val;
			cht.Assign(l, r + 1, val);
		} else if (opt == 3) {
			int l, r;
			mint val;
			cin >> l >> r >> val;
			cht.Add(l, r + 1, val);
		} else if (opt == 4) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			cht.CopyRange(l1, r1 + 1, l2, r2 + 1);
		} else if (opt == 5) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			if (l2 < l1) {
				swap(l1, l2);
				swap(r1, r2);
			}
			cht.SwapRange(l1, r1 + 1, l2, r2 + 1);
		} else {
			int l, r;
			cin >> l >> r;
			cht.ReverseRange(l, r + 1);
		}
	}

	cht.SplitRange(1, n + 1);
	for (auto it = cht.mp.find(1); it->first != n + 1; it = next(it)) {
		int cnt = next(it)->first - it->first;
		for (int i = 0; i < cnt; i ++) {
			cout << it->second << ' ';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}