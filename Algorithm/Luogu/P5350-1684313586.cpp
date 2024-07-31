#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include ".vscode/debug.hpp"
#else
	#define debug(...)
#endif

template <typename T, typename Compare = std::greater<T>, template <typename E, typename Alloc = std::allocator<E>> typename Container = std::vector>
using PriorityQueue = std::priority_queue<T, Container<T>, Compare>;
template <typename T, template <typename E, typename Alloc = std::allocator<E>> typename Container = std::vector>
using Stack = std::stack<T, Container<T>>;
using i64 = int64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

struct Macro {};
template <> struct std::ranges::view_interface<Macro> {
	static void Main();
};

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
using mint = Modint<0x3b9aca07>;

using namespace std;

auto std::ranges::view_interface<Macro>::Main() -> void {
	int n, q;
	cin >> n >> q;

	map<int,mint> mp;
	for (int i = 0; i < n; i ++) {
		cin >> mp[i];
	}
	mp[-1] = 0;

	auto Split = [&](int x) {
		auto it = prev(mp.upper_bound(x));
		mp[x] = it->second;
	};
	auto Assign = [&](int l, int r, mint d) {
		Split(l); Split(r);
		auto it = mp.find(l);
		while (it->first != r) {
			it = mp.erase(it);
		}
		mp[l] = d;
	};

	auto GetRangeSum = [&](int l, int r) {
		Split(l); Split(r);
		mint ret = 0;
		auto it = mp.find(l);
		while (it->first != r) {
			ret += (next(it)->first - it->first) * it->second;
			it = next(it);
		}
		return ret;
	};

	auto RangeAdd = [&](int l, int r, mint d) {
		Split(l); Split(r);
		auto it = mp.find(l);
		while (it->first != r) {
			it->second += d;
			it = next(it);
		}
	};

	auto RangeCopy = [&](int l1, int r1, int l2, int r2) {
		Split(l1); Split(r1);
		Split(l2); Split(r2);
		Assign(l2, r2, 0);
		auto it = mp.find(l1);
		while (it->first != r1) {
			mp[it->first - l1 + l2] = it->second;
			it = next(it);
		}
	};

	auto RangeSwap = [&](int l1, int r1, int l2, int r2) {
		if (l1 > l2) {
			swap(l1, l2);
			swap(r1, r2);
		}
		Split(l1); Split(r1);
		Split(l2); Split(r2);
		
		vector tmp(mp.find(l2), mp.find(r2));
		Assign(l2, r2, 0);
		for (auto it = mp.find(l1); it->first != r1; ) {
			mp[it->first - l1 + l2] = it->second;
			it = next(it);
		}
		Assign(l1, r1, 0);
		for (auto it : tmp) {
			mp[it.first - l2 + l1] = it.second;
		}
	};

	auto RangeReverse = [&](int l, int r) {
		Split(l); Split(r);
		// vector tmp(mp.find(l), mp.find(r));

		vector<pair<int,mint>> tmp;
		for (auto it = mp.find(l); it->first != r; it = next(it)) {
			tmp.emplace_back(next(it)->first - 1, it->second);
		}

		Assign(l, r, 0);
		for (auto it : tmp) {
			mp[(r - l) - (it.first - l) - 1 + l] = it.second;
		}
	};

	for (int _ = 1; _ <= q; _ ++) {
		int opt;
		cin >> opt;
		// debug(_, opt);
		if (opt == 1) {
			int l, r;
			cin >> l >> r;
			l --;
			cout << GetRangeSum(l, r) << '\n';
		} else if (opt == 2) {
			int l, r;
			cin >> l >> r;
			l --;
			mint d;
			cin >> d;
			Assign(l, r, d);
		} else if (opt == 3) {
			int l, r;
			cin >> l >> r;
			l --;
			mint d;
			cin >> d;
			RangeAdd(l, r, d);
		} else if (opt == 4) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1 --; l2 --;		
			RangeCopy(l1, r1, l2, r2);
		} else if (opt == 5) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1 --; l2 --;		
			RangeSwap(l1, r1, l2, r2);
		} else {
			int l, r;
			cin >> l >> r;
			l --;
			RangeReverse(l, r);
		}
	}


	Split(0); Split(n);
	vector tmp(mp.find(0), mp.find(n));
	int tag = 0;
	mint now = tmp[0].second;
	for (int i = 1; i < tmp.size(); i ++) {
		while (tag < tmp[i].first) {
			cout << now << ' ';
			tag ++;
		}
		now = tmp[i].second;
	}
	while (tag < n) {
		cout << now << ' ';
		tag ++;
	}
	cout << '\n';
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