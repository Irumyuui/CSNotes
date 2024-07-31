#include <bits/stdc++.h>
using namespace std;

const int N = 114, M = 514;
vector<int> edge[N], graph[N];
int dfn[N], low[N], id[N], scc = 0, stamp = 0;
int w[N], sw[N], v[N], sv[N];
bool inst[N];
stack<int> st;
int n, m;
int ind[N], out[N];

int f[N][M];

void tarjan(int from) {
	dfn[from] = low[from] = ++ stamp;
	st.push(from);
	inst[from] = true;
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			tarjan(to);
			low[from] = min(low[from], low[to]);
		} else if (inst[to]) {
			low[from] = min(low[from], low[to]);
		}
	}
	if (dfn[from] == low[from]) {
		scc ++;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			inst[now] = false;
			id[now] = scc;
			sw[id[now]] += w[now];
			sv[id[now]] += v[now];
		} while (now != from);
	}
}


int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) 
		cin >> w[i];
	for (int i = 1; i <= n; ++ i)
		cin >> v[i];
	for (int i = 1; i <= n; ++ i) {
		int dad;
		cin >> dad;
		if (dad) {
			edge[dad].push_back(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (auto j : edge[i]) {
			if (id[j] != id[i]) {
				ind[id[j]] ++;
				out[id[i]] ++;
				graph[id[i]].push_back(id[j]);
			}
		}
	}
	for (int i = 1; i <= scc; ++ i) {
		if (!ind[i]) {
			graph[0].push_back(i);
		}
	}
	function<void(int)> dfs = [&](int from) -> void {
		for (int i = sw[from]; i <= m; ++ i) {
			f[from][i] = sv[from];
		}
		for (auto to : graph[from]) {
			dfs(to);
			for (int j = m - sw[from]; j >= 0; -- j) {
				for (int k = 0; k <= j; ++ k) {
					f[from][j + sw[from]] = max(f[from][j + sw[from]], f[from][j + sw[from] - k] + f[to][k]);
				}
			}
		}
	};
	dfs(0);
	cout << f[0][m];
}