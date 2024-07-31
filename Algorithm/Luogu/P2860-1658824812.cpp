/* Filename: USACO 2006 Jan, Redundant Paths */
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct Edge {
	int to, id;
};
vector<Edge> edge[N];
int dfn[N], low[N], belong[N], tot = 0, stamp = 0;
vector<int> cc[N];
stack<int> st;
bool inst[N];

void add(int from, int to, int id) {
	edge[from].push_back({to, id});
}

void tarjan(int from, int id) {
	dfn[from] = low[from] = ++ stamp;
	st.push(from);
	inst[from] = true;
	for (auto [to, _id] : edge[from]) {
		if (!dfn[to]) {
			tarjan(to, _id);
			low[from] = min(low[from], low[to]);
		} else if (id != _id) {
			low[from] = min(low[from], dfn[to]);
		}
	}
	if (dfn[from] == low[from]) {
		++ tot;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			inst[now] = false;
			belong[now] = tot;
			cc[tot].push_back(now);
		} while (now != from);
	}
}

void Solution() {
	int n, m;
	cin >> n >> m;
	while (m --) {
		int a, b;
		cin >> a >> b;
		add(a, b, m);
		add(b, a, m);
	}
	tarjan(1, -1);
	int ans = 0;  // ceil(ans * 1.0 / 2);
	for (int i = 1; i <= tot; ++ i) {
		int cnt = 0;
		for (auto u : cc[i]) {
			for (auto [v, _id] : edge[u]) {
				if (belong[u] != belong[v]) {
					// bridge
					cnt ++;
				}
			}
		}
		if (cnt == 1) {
			ans ++;
		}
	}
	ans = ceil(ans * 1.0 / 2);
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}