#include <bits/stdc++.h>
using namespace std;

int n, m;
const int N = 1e4 + 10;
vector<int> g[N];
int cnt[N], id[N], scc_cnt = 0, step = 0, dfn[N], low[N];
bool inst[N];
stack<int> st;
int outd[N];

void tarjan(int u) {
	dfn[u] = low[u] = ++ step;
	st.push(u);
	inst[u] = true;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (inst[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int v = 0;
		++ scc_cnt;
		do {
			v = st.top();
			st.pop();
			inst[v] = false;
			id[v] = scc_cnt;
			cnt[scc_cnt] ++;
		} while (v != u);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < m; ++ i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
	}
	for (int i = 1; i <= n; ++ i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; ++ i) {
		for (auto j : g[i]) {
			if (id[i] != id[j]) {
				outd[id[i]] ++;
			}
		}
	}
	bool flag = false;
	int ans = 0;
	for (int i = 1; i <= scc_cnt; ++ i) {
		if (!outd[i]) {
			if (flag) {
				cout << 0;
				return 0;
			}
			flag = true;
			ans = cnt[i];
		}
	}
	cout << ans;
}