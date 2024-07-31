#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

template <typename T>
struct Linear_Base {
	std::vector<T> a;
	auto insert(T x) -> void {
		for (auto i : a) 
			x = min(x, i ^ x);
		for (auto &i : a)
			i = min(i, i ^ x);
		if (x)
			a.emplace_back(x);
	}
	auto ask() -> T {
		T ret = {};
		for (auto i : a)
			ret ^= i;
		return ret;
	}
	auto operator += (const Linear_Base &that) -> Linear_Base& {
		for (auto it : that.a) 
			insert(it);
		return *this;
	}
	auto operator + (const Linear_Base &that) -> Linear_Base {
		auto ret = *this;
		ret += that;
		return ret;
	}
};

auto Solve() -> void {
	int n;
	cin >> n;
	Linear_Base<uint64_t> b;
	for (int i = 0; i < n; i ++) {
		uint64_t x;
		cin >> x;
		b.insert(x);
	}
	cout << b.ask() << '\n';
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}