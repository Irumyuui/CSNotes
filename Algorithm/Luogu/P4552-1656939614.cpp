#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<ll> a(n + 1), d(a);
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		d[i] = a[i] - a[i - 1];
	}
	ll add = 0, sub = 0;
	for (int i = 2; i <= n; ++ i) {
		if (d[i] > 0) {
			add += d[i];
		} else if (d[i] < 0) {
			sub += -d[i];
		}
	}
	cout << max(add, sub) << '\n' << abs(add - sub) + 1 << '\n';
}