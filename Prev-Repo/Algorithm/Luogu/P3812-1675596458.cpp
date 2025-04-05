#include <bits/stdc++.h>
using namespace std;

template <typename T, int N>
struct Linear_Base {
	std::array<T,N> a;
	Linear_Base() : a{} {}
	auto insert(T x) -> void {
		for (int i = N - 1; i >= 0; i --) {
			if (x & (T{1} << i)) {
				if (!a[i]) {
					a[i] = x;
					return;
				}
				x ^= a[i];
			}
		}
	}
	auto query_max() -> T {
		T ret = {};
		for (int i = N - 1; i >= 0; i --) {
			ret = max(ret, ret ^ a[i]);
		}
		return ret;
	}
	auto query_min() -> T {
		for (auto it : a) 
			if (it)
				return it;
		return 0;
	}
	auto contains(T x) -> bool {
		for (int i = N - 1; i >= 0; i --) {
			if (x & (T{1} << i)) {
				if (!a[i])
					return false;
				x ^= a[i];
			}
		}
		return true;
	}
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	Linear_Base<uint64_t,64> a;
	for (int i = 0; i < n; i ++) {
		uint64_t x;
		cin >> x;
		a.insert(x);
	}
	cout << a.query_max() << '\n';
}