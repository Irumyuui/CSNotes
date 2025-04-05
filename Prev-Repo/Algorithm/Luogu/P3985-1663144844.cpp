#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 110;

int n;
ll w;
ll a[N], b[N];
unordered_map<ll,ll> f[N];

ll dfs(int id, ll cost) {
	if (id > n) {
		return 0;
	}
	if (f[id].count(cost)) {
		return f[id][cost];
	}
	ll ret = 0;
	if (cost + a[id] <= w) {
		ret = max(dfs(id + 1, cost), dfs(id + 1, cost + a[id]) + b[id]);
	} else {
		ret = dfs(id + 1, cost);
	}
	f[id][cost] = ret;
	return ret;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> w;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i] >> b[i];
	}
	cout << dfs(1, 0) << '\n';
}