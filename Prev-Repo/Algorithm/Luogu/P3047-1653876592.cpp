#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, k;
int c[N], f[N][25], v[N][25], dep[N];
bool vis[N];
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}

void down(int now) {
	vis[now] = true;
	f[now][0] = c[now];
	for (auto nex : edge[now]) {
		if (!vis[nex]) {
			down(nex);
			dep[now] = max(dep[now], dep[nex] + 1);
			for (int i = 0; i <= min(dep[nex], k); ++ i) {
				f[now][i + 1] += f[nex][i];
			}
		}
	}
}
void rise(int now) {
	vis[now] = true;
	for (auto nex : edge[now]) {
		if (!vis[nex]) {
			v[nex][1] += c[now];
			for (int i = 2; i <= k; ++ i) {
				v[nex][i] += f[now][i - 1] - f[nex][i - 2] + v[now][i - 1];
			}
			rise(nex);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	for (int i = 1; i <= n; ++ i) {
		cin >> c[i];
	}
	down(1);
	memset(vis, 0, sizeof vis);
	rise(1);
	for (int i = 1; i <= n; ++ i) {
		int ans = 0;
		for (int j = 0; j <= k; ++ j) {
			ans += f[i][j] + v[i][j];
		}
		cout << ans << endl;
	}
}