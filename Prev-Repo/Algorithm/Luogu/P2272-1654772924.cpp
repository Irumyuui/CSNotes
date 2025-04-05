#include <bits/stdc++.h>
using namespace std;
#pragma region DEBUG
#ifndef ONLINE_JUDGE
#define debug(...) _DECON::ddebug(__LINE__, #__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif
#define endl '\n'
#pragma endregion 
#define all(X) std::begin(X), std::end(x)
using ll = long long;

const int N = 1e5 + 10;
vector<int> edge[N];
set<int> graph[N];
int n, m, ind[N], out[N], dfn[N], low[N], tt = 0, id[N], scc = 0, cnt[N];
ll mod, f[N], g[N];
bool vis[N];
stack<int> st;

void tarjan(int from) {
	dfn[from] = low[from] = ++ tt;
	st.push(from);
	vis[from] = true;
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			tarjan(to);
			low[from] = min(low[from], low[to]);
		} else if (vis[to]) {
			low[from] = min(low[from], low[to]);
		}
	}
	if (dfn[from] == low[from]) {
		int v = 0;
		++ scc;
		do {
			v = st.top();
			st.pop();
			vis[v] = false;
			id[v] = scc;
			cnt[scc] ++;
		} while (v != from);
	}
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> mod;
	for (int i = 1; i <= m; ++ i) {
		int from, to;
		cin >> from >> to;
		edge[from].push_back(to);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (auto j : edge[i]) {
			if (id[i] != id[j]) {
				graph[id[i]].emplace(id[j]);
			}
		}
	}
	for (int i = 1; i <= scc; ++ i) {
		for (auto j : graph[i]) {
			ind[j] ++;
			out[i] ++;
		}
	}
	queue<int> tmp;
	for (int i = 1; i <= scc; ++ i) {
		if (!ind[i]) {
			tmp.push(i);
			f[i] = cnt[i];
			g[i] = 1;
		}
	}
	vector<int> ed;
	for (int i = 1; i <= scc; ++ i) {
		if (!out[i]) {
			ed.push_back(i);
		}
	}
	auto q = tmp;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (auto to : graph[from]) {
			if (f[to] < f[from] + cnt[to]) {
				f[to] = f[from] + cnt[to];
				g[to] = g[from];
			} else if (f[to] == f[from] + cnt[to]) {
				g[to] = (g[to] + g[from]) % mod;
			}
			if (-- ind[to] == 0) {
				q.push(to);
			}
		}
	}
	q = tmp;
	ll ans1 = 0, ans2 = 0;
	for (auto v : ed) {
		if (f[v] > ans1) {
			ans1 = f[v];
			ans2 = g[v];
		} else if (f[v] == ans1) {
			ans2 += g[v];
			ans2 %= mod;
		}
	}
	cout << ans1 << endl << ans2 << endl;
}