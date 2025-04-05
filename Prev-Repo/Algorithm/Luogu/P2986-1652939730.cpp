#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e5 + 10;
vector<pair<int,int>> edge[N];
void add(int a, int b, int w) {
	edge[a].push_back({b, w});
}
int n;
ll c[N];
ll f[N], v[N], siz[N], cs[N], sumc;
bool vis[N];
void down(int now) {
	vis[now] = true;
	cs[now] = c[now];
	for (auto [nex, len] : edge[now]) {
		 if (!vis[nex]) {
		 	down(nex);
		 	cs[now] += cs[nex];
		 	f[now] += f[nex] + cs[nex] * len;
		 }
	}
}
void rise(int now) {
	vis[now] = true;
	for (auto [nex, len] : edge[now]) {
		if (!vis[nex]) {
			v[nex] += v[now] + f[now] - f[nex] - cs[nex] * len + (sumc - cs[nex]) * len;
			rise(nex);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> c[i];
		sumc += c[i];
	}
	for (int i = 1; i < n; ++ i) {
		int a, b, w;
		cin >> a >> b >> w;
		add(a, b, w);
		add(b, a, w);
	}
	memset(vis, 0, sizeof vis);
	down(1);
	memset(vis, 0, sizeof vis);
	rise(1);
	ll ans = 1ll << 60;
	for (int i = 1; i <= n; ++ i) {
		ans = min<ll>(ans, f[i] + v[i]);
	}
	cout << ans;
}	