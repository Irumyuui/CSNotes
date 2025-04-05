#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

ll f[13][10][10][2][2][2];
int len, digit[13];

ll dfs(int pos, int pre2, int pre1, int same, int eight, int four, bool lead, bool limit) {
	if (eight && four) {
		return 0;
	} else if (!pos) {
		return same;
	} else if (!lead && !limit && f[pos][pre2][pre1][same][eight][four] != -1) {
		return f[pos][pre2][pre1][same][eight][four];
	}
	ll ret = 0;
	int LIM = limit ? digit[pos] : 9;
	for (int i = 0; i <= LIM; ++ i) {
		if (lead && i == 0) {
			continue;
		}
		ret += dfs(
			pos - 1,
			pre1,
			i,
			(i == pre1 && pre1 == pre2 && i == pre2) || same,
			eight || i == 8,
			four || i == 4,
			lead && i == 0,
			limit && i == LIM);
	}
	if (!lead && !limit) {
		f[pos][pre2][pre1][same][eight][four] = ret;
	}
	return ret;
}
ll solve(ll num) {
	memset(digit, 0, sizeof digit);
	len = 0;
	while (num > 0) {
		digit[++ len] = num % 10;
		num /= 10;
	}
	return dfs(11, 0, 0, false, 0, 0, true, true);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(f, -1, sizeof f);
	ll l, r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1) << endl;
}