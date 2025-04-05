#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 110 * 2;
vector<int> edge[N];
int dfn[N], low[N], id[N], stamp = 0, scc_cnt = 0;
bool vis[N];
stack<int> st;
void add(int from, int to) {
	edge[from].emplace_back(to);
}
void tarjan(int from) {
	dfn[from] = low[from] = ++ stamp;
	st.emplace(from);
	vis[from] = true;
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			tarjan(to);
			low[from] = std::min(low[from], low[to]);
		} else if (vis[to]) {
			low[from] = std::min(low[from], low[to]);
		}
	}
	if (dfn[from] == low[from]) {
		scc_cnt ++;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			id[now] = scc_cnt;
			vis[now] = false;
		} while (now != from);
	}
}

void Solution() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n * 2; ++ i) {
		edge[i].clear();
	}
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(id, 0, sizeof id);
	stamp = 0;
	scc_cnt = 0;
	while (m --) {
		char k1, k2;
		int from, to;
		cin >> k1 >> from >> k2 >> to;
		from --;
		to --;
		add(from * 2 + (k1 == 'm'), to * 2 + !(k2 == 'm'));
		add(to * 2 + (k2 == 'm'), from * 2 + !(k1 == 'm'));
	}
	for (int i = 0; i < n * 2; ++ i) if (!dfn[i]) tarjan(i);
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] == id[i * 2 + 1]) {
			cout << "BAD\n";
			return;
		}
	}
	#ifndef ONLINE_JUDGE
		for (int i = 0; i < n * 2; ++ i) {
			debug(i, id[i * 2], id[i * 2] + 1);
		}
		cerr << '\n';
	#endif
	cout << "GOOD\n";
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		Solution();
	}
}