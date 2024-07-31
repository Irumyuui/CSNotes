#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
// #include <cdebug>
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 2e5 + 10;
vector<int> edge[N];
void add(int from, int to) {
	debug(from, to);
	edge[from].push_back(to);
}
int dfn[N], low[N], id[N], scc_cnt = 0, stamp = 0;
stack<int> st;
bool vis[N];
void tarjan(int from) {
	dfn[from] = low[from] = ++ scc_cnt;
	st.emplace(from);
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
		++ scc_cnt;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			vis[now] = false;
			id[now] = scc_cnt;
		} while (now != from);
	}
}

void Solution() {
	int n, m;
	cin >> n >> m;
	while (m --) {
		int a, b;
		cin >> a >> b;
		a --;
		b --;
		add(a ^ 1, b);
		add(b ^ 1, a);
	}
	for (int i = 0; i < n * 2; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	#ifndef ONLINE_JUDGE
		for (int i = 0; i < n * 2; ++ i) {
			debug(i, id[i]);
		}
	#endif
	for (int i = 0; i < n; i ++) {
		if (id[i * 2] == id[i * 2 + 1]) {
			cout << "NIE\n";
			return;
		}
	}
	for (int i = 0; i < n; i ++) {
		if (id[i * 2] > id[i * 2 + 1]) {
			cout << i * 2 + 1 << '\n';
		} else {
			cout << i * 2 + 2 << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}