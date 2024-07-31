#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

ll f[20][10];
int len, digit[20];

ll dfs(int pos, int pre, bool limit) {
	if (!pos) {
		return 1;
	}
	if (~f[pos][pre] && !limit) {
		return f[pos][pre];
	}
	ll ret = 0;
	int LIM = limit ? digit[pos] : 9;
	for (int i = 0; i <= LIM; ++ i) {
		if (pre != 5 || i != 9)
			ret += dfs(pos - 1, i, limit && i == LIM);
	}
	if (!limit) {
		f[pos][pre] = ret;
	}
	return ret;
}
ll solve(ll n) {
	len = 0;
	while (n > 0) {
		digit[++ len] = n % 10;
		n /= 10;
	}
	return dfs(len, 0, true);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(f, -1, sizeof f);
	ll l, r;
	cin >> l >> r;
	ll a = r - solve(r);
	ll b = l - 1 - solve(l - 1);
	cout << a - b << endl;
}