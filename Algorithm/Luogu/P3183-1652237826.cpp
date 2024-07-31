#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];
int ind[N], cnt[N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		ind[b] ++;		
	}
	queue<int> q;
	for (int i = 1; i <= n; ++ i) {
		if (ind[i] == 0 && !g[i].empty()) {
			q.push(i); cnt[i] = 1;
		}
	}
	int ans = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		if (g[now].empty()) ans += cnt[now];
		for (auto nex : g[now]) {
			cnt[nex] += cnt[now];
			if (-- ind[nex] == 0) q.push(nex);
		}
	}
	cout << ans << '\n';
}