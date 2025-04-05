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

template <typename... Args> using Func = std::function<Args...>;
template <typename T> using Vec = std::vector<T>;

using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

struct Macro {};
template <> struct std::ranges::view_interface<Macro> {
	static auto Main() -> void;
};

using namespace std;

const int N = 1e5 + 10;
bitset<N> npr;
vector<int> pri;

void Init() {
	npr[0] = npr[1] = 1;
	for (int i = 2; i < N; i ++) {
		if (!npr[i])
			pri.emplace_back(i);
		for (i64 j : pri) {
			if (i * j >= N) break;
			npr[i * j] = 1;
			if (i % j == 0) break;
		}
	}
}

auto std::ranges::view_interface<Macro>::Main() -> void {
	i64 n;
	cin >> n;

	for (auto x : pri) {
		if (x > n) {
			break;
		}
		if (n % x == 0) {
			int c = 0;
			while (n % x == 0) {
				c ++;
				n /= x;
			}
			if (c == 1) {
				cout << "no\n";
				return;
			}
		} 
	}

	auto Sqrt = [&](i64 n) -> i64 {
		i64 x = sqrtl(n);
		while (x * x <= n) {
			x ++;
		}
		while (x * x > n) {
			x --;
		}
		return x;
	};
	auto Cbrt = [&](i64 n) -> i64 {
		i64 x = cbrt(n);
		while (x * x * x <= n) {
			x ++;
		}
		while (x * x * x > n) {
			x --;
		}
		return x;
	};

	auto tmp = Sqrt(n);
	if (tmp * tmp == n) {
		cout << "yes\n";
		return;
	}
	tmp = Cbrt(n);
	if (tmp * tmp * tmp == n) {
		cout << "yes\n";
		return;
	}
	cout << "no\n";
}

auto main() -> decltype(0) {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(15);

	Init();

	int test = 1;
	std::cin >> test;

	for (int rp = 1; test --> 0; rp ++) {
		debug(rp);
		std::ranges::view_interface<Macro>::Main();
	}
}