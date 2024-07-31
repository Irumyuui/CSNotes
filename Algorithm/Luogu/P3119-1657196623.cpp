#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
struct Edge {
	int to, next;
} edge[N << 4];
int head[N], tt = 1;
void add(int from, int to) {
	edge[++ tt] = {to, head[from]}; head[from] = tt;
}
int dfn[N], low[N], stamp = 0, scc_cnt = 0, id[N], cnt[N], dis[N];
stack<int> st;
bool vis[N];
int n, m;
void dfs(int from) {
	dfn[from] = low[from] = ++ stamp;
	st.push(from);
	vis[from] = true;
	for (int ed = head[from]; ed; ed = edge[ed].next) {
		int to = edge[ed].to;
		if (!dfn[to]) {
			dfs(to);
			low[from] = min(low[from], low[to]);
		} else if (vis[to]) {
			low[from] = min(low[from], low[to]);
		}
	}
	if (dfn[from] == low[from]) {
		scc_cnt ++;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			vis[now] = false;
			id[now] = scc_cnt;
			cnt[id[now]] ++;
		} while (now != from);
	}
}
void spfa(int sta) {
	queue<int> q;
	q.push(sta);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		vis[from] = false;
		for (int ed = head[from]; ed; ed = edge[ed].next) {
			int to = edge[ed].to;
			if (dis[to] < dis[from] + cnt[to]) {
				dis[to] = dis[from] + cnt[to];
				if (!vis[to]) {
					q.push(to);
					vis[to] = true;
				}
			}
		}
	}
}
void Solution() {
	cin >> n >> m;
	while (m --) {
		int from, to;
		cin >> from >> to;
		add(from, to);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int ed = head[i]; ed; ed = edge[ed].next) {
			int j = edge[ed].to, from = id[i], to = id[j];
			if (id[from] != id[to]) {
				add(from + n, to + n);
				add(from + n + scc_cnt, to + n + scc_cnt);
				add(to + n, from + n + scc_cnt);
				cnt[from + n + scc_cnt] = cnt[from + n] = cnt[from];
				cnt[to + n + scc_cnt] = cnt[to + n] = cnt[to];
			}
		}
	}
	spfa(id[1] + n);
	cout << dis[id[1] + n + scc_cnt];
}
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}