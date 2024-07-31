#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 10;
const int MOD = 998244353;

#define int long long

ll mul(ll a, ll b, ll p) {
	return static_cast<__int128_t>(a) * b % p;
}
ll power(ll a, ll i, ll p) {
	ll res = 1;
	while (i) {
		if (i & 1) {
			res = mul(res, a, p);
		}
		a = mul(a, a, p);
		i >>= 1;
	}
	return res;
}

vector<int> g[N];
int ind[N], cnt[N];
int dis[N];

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	while (m --) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		ind[b] ++;
	}
	queue<int> q;
	for (int i = 1; i <= n; ++ i) { 
		if (!ind[i]) {
			q.push(i);
		}
		cnt[i] = 1;
	}
	for (; !q.empty(); ) {
		int now = q.front();
		q.pop();
		for (auto nex : g[now]) {
			dis[nex] += dis[now] + 1 * cnt[now];
			cnt[nex] += cnt[now];
			dis[nex] %= MOD; cnt[nex] %= MOD;
			if (-- ind[nex] == 0) {
				q.push(nex);
			}
		}
	}

	ll sd = 0, sc = 0;
	for (int i = 1; i <= n; ++ i) {
		sd = (sd + dis[i]) % MOD;
		sc = (sc + cnt[i]) % MOD;
	}

	ll ans = sd * power(sc, MOD - 2, MOD) % MOD;
	cout << ans << '\n';
}