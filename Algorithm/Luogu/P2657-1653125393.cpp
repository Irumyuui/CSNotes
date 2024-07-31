#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

int d[20], m;
ll f[20][20];
ll dfs(int pos, int pre, bool lead, bool limit) {
	if (pos > m) {
		return 1;
	}
	if (f[pos][pre] != -1 && !limit) {
		return f[pos][pre];
	}
	ll ret = 0;
	int LIMIT = limit ? d[pos] : 9;
	for (int i = 0; i <= LIMIT; ++ i) {
		if (abs(i - pre) < 2) {
			continue;
		} else if (lead && !i) {
			ret += dfs(pos + 1, -2, true, i == LIMIT && limit);
		} else {
			ret += dfs(pos + 1, i, false, i == LIMIT && limit);
		}
	} 
	if (!lead && !limit) {
		f[pos][pre] = ret;
	}
	return ret;
}
ll dfs(ll a) {
	memset(f, -1, sizeof f);
	memset(d, 0, sizeof d);
	m = 0;
	while (a > 0) {
		d[++ m] = a % 10;
		a /= 10;
	}
	reverse(d + 1, d + 1 + m);
	return dfs(1, -2, true, true);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	ll a, b;
	cin >> a >> b;
	cout << dfs(b) - dfs(a - 1) << endl;
}