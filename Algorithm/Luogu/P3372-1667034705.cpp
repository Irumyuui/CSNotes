#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 10;
ll a[N], b[N];

void update(int x, int n, ll d) {
	for (int i = x; i <= n; i += i & -i) {
		a[i] += d;
		b[i] += (x - 1) * d;
	}
}
ll query(int x) {
	ll ret = 0;
	for (int i = x; i > 0; i -= i & -i) {
		ret += x * a[i] - b[i];
	}
	return ret;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	vector<int> v(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> v[i];
		update(i, n, v[i] - v[i - 1]);
	}
	while (q --) {
		int opt, l, r;
		cin >> opt >> l >> r;
		if (opt == 1) {
			ll k;
			cin >> k;
			update(l, n, k);
			update(r + 1, n, -k);
		} else {
			cout << query(r) - query(l - 1) << '\n';
		}
	}
}