#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e6 + 10;
vector<int> edge[N];
void add(int a, int b) {
	edge[a].push_back(b);
}
int n;
ll f[N], v[N], siz[N];
bool vis[N];
void down(int now) {
	vis[now] = true;
	siz[now] = 1;
	for (auto nex : edge[now]) {
		if (vis[nex]) continue;
		down(nex);
		siz[now] += siz[nex];
		f[now] += f[nex] + siz[nex];
	}
}
void rise(int now) {
	vis[now] = true;
	for (auto nex : edge[now]) {
		if (vis[nex]) continue;
		v[nex] += v[now] + f[now] - f[nex] - siz[nex] + (n - siz[nex]);
		rise(nex);
	}
}


int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	memset(vis, 0, sizeof vis);
	down(1);
	memset(vis, 0, sizeof vis);
	rise(1);
	ll mx = 0, root = 0;
	for (int i = 1; i <= n; ++ i) {
		if (mx < f[i] + v[i]) {
			mx = f[i] + v[i];
			root = i;
		}
	}
	cout << root;
}