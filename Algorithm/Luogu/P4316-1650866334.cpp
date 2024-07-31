#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const int N = 1e5 + 10;
vector< pair<int, int> > g[N];
int in[N], deg[N];
ld ans[N];

void tops(int sta) {
	queue<int> q; q.push(sta);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto [nex, w] : g[now]) {
			ans[nex] += (ans[now] + w) / max<ld>(1, deg[nex]);
			if (-- in[nex] == 0) {
				q.push(nex);
			}
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int a, b, w; cin >> a >> b >> w;
		g[b].push_back({a, w});
		in[a] ++;
		deg[a] ++;
	}
	tops(n);
	cout << fixed << setprecision(2) << ans[1] << '\n';
}