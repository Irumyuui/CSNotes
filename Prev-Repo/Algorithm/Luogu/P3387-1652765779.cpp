#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, m;
vector<int> edge[N];
int w[N], W[N];
int dfn[N], low[N], step = 0, scc = 0, id[N];
bool inst[N];
stack<int> st;
bool vis[N];
int ind[N];
vector<int> g[N];
int dist[N];
void tarjan(int u) {
	dfn[u] = low[u] = ++ step;
	inst[u] = true;
	st.push(u);
	for (auto v : edge[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (inst[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (dfn[u] == low[u]) {
		scc ++;
		int tmp = 0;
		do {
			tmp = st.top();
			st.pop();
			inst[tmp] = false;
			id[tmp] = scc;
			W[scc] += w[tmp];
		} while (tmp != u);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> w[i];
	}
	for (int i = 0; i < m; ++ i) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		vector<bool> vis(scc + 1, false);
		for (auto j : edge[i]) {
			if (id[i] != id[j]) {
				if (!vis[id[j]]) {
					g[id[i]].push_back(id[j]), vis[id[j]] = true;
					ind[id[j]] ++;
				}
			}
		}
	}
	queue<int> q;
	for (int i = 1; i <= scc; ++ i) {
		if (!ind[i]) {
			q.push(i);
			dist[i] = W[i];
		}
	}
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (auto nex : g[now]) {
			if (dist[nex] < dist[now] + W[nex]) {
				dist[nex] = dist[now] + W[nex];
			}
			if (-- ind[nex] == 0) {
				q.push(nex);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= scc; ++ i) {
		ans = max(ans, dist[i]);
	}
	cout << ans << '\n';
}