#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll qp(ll a, ll i) {
	ll ret = 1;
	for (; i > 0; i >>= 1, a *= a)
		if (i & 1) ret *= a;
	return ret;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	ll x, y;
	cin >> x >> y;
	if (y % x) {
		cout << 0;
		return 0;
	}
	ll z = y / x;
	ll cnt = 0;
	for (int i = 2; i <= z; i ++) {
		if (z % i == 0) {
			cnt ++;
			while (z % i == 0) {
				z /= i;
			}
		}
	}
	if (z > 1) {
		cnt ++;
	}
	cout << qp(2, cnt);
}