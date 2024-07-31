#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll f[120][120][120];
int digit[120], len = 0;
ll dfs(int pos, int zero, int one, bool lead, bool limit) {
	if (pos > len) {
		return (zero || one) && zero >= one;
	}
	if (f[pos][zero][one] != -1 && !lead && !limit) {
		return f[pos][zero][one];
	}
	int LIM = limit ? digit[pos] : 1;
	ll ret = 0;
	for (int i = 0; i <= LIM; ++ i) {
		ret += dfs(pos + 1, zero + (!lead && i == 0), one + (i == 1),
			lead && i == 0, limit && i == LIM);
	}
	if (!lead && !limit) {
		f[pos][zero][one] = ret;
	}
	return ret;
}
ll solve(ll n) {
	memset(f, -1, sizeof f);
	len = 0;
	while (n > 0) {
		digit[++ len] = n & 1;
		n >>= 1;
	}
	reverse(digit + 1, digit + 1 + len);
	return dfs(1, 0, 0, true, true);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	ll l, r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1);
}