#include <bits/stdc++.h>
using namespace std;

vector<int> g[10010];
int n, m;

int cat[10010];
bool vis[10010];
bool match(int now) {
	for (auto nex : g[now]) {
		if (!vis[nex]) {
			vis[nex] = true;
			if (cat[nex] == 0 || match(cat[nex])) {
				cat[nex] = now;
				return true;
			}
		}
	}
	return false;
}
int xiong() {
	memset(cat, 0, sizeof cat);
	int cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		memset(vis, 0, sizeof vis);
		if (match(i))
			cnt ++;
	}
	return cnt;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> n >> m >> t;;
	for (int i = 1; i <= t; ++ i) {
		int a, b;
		cin >> a >> b;
		b += n;
		g[a].push_back(b); g[b].push_back(a);
	}
	int ans = xiong();
	cout << ans << '\n';
}