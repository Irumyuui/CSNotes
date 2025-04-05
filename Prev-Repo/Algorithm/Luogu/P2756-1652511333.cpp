#include <bits/stdc++.h>
using namespace std;

vector<int> g[110];
int n, m;

int cat[110];
bool vis[110];
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
	int cnt = 0;
	memset(cat, 0, sizeof cat);
	for (int i = 1; i <= m; ++ i) {
		memset(vis, 0, sizeof vis);
		if (match(i)) {
			cnt ++;
		}
	}
	return cnt;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> m >> n;
	int a, b;
	while (cin >> a >> b && (a != -1 && b != -1)){
		g[a].push_back(b);
		g[b].push_back(a);
	}
	auto k = xiong();
	cout << k << '\n';
	for (int i = m + 1; i <= n; ++ i) {
		if (cat[i]) {
			cout << cat[i] << ' ' << i << '\n';
		}
	}
}	