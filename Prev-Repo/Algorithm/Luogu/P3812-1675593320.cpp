#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;

	vector<ll> a(n);
	for (int i = 0; i < n; i ++) {
		cin >> a[i];
	}

	vector<ll> b;
	b.reserve(n);
	auto insert = [&](ll x) {
		for (auto i : b) 
			x = min(x, i ^ x);
		for (auto &i : b) 
			i = min(i, i ^ x);
		if (x)
			b.push_back(x);
	};

	for (auto it : a) {
		insert(it);
	}
	
	ll ans = 0;
	for (auto it : b) {
		ans ^= it;
	}
	cout << ans << '\n';
}