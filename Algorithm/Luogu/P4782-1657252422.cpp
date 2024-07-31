#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
struct Edge {
	int to, next;
} edge[N << 2];
int head[N], tt = -1;
void add(int from, int to) {
	edge[++ tt].to = to; edge[tt].next = head[from]; head[from] = tt;
}
int dfn[N], low[N], stamp = 0, id[N], scc_cnt = 0;
stack<int> st;
bool inst[N];
void tarjan(int from) {
	dfn[from] = low[from] = ++ stamp;
	st.push(from);
	inst[from] = true;
	for (int ed = head[from]; ~ed; ed = edge[ed].next) {
		int to = edge[ed].to;
		if (!dfn[to]) {
			tarjan(to);
			low[from] = min(low[to], low[from]);
		} else if (inst[to]) {
			low[from] = min(low[from], low[to]);
		}
	}
	if (dfn[from] == low[from]) {
		++ scc_cnt;
		int now = from;
		do {
			now = st.top();
			st.pop();
			inst[now] = false;
			id[now] = scc_cnt;
		} while (now != from);
	}
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	while (m --) {
		int i, a, j, b;
		cin >> i >> a >> j >> b;
		i --; j --;
		add(i * 2 + !a, j * 2 + b);
		add(j * 2 + !b, i * 2 + a);
	}
	for (int i = 0; i < n * 2; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] == id[i * 2 + 1]) {
			cout << "IMPOSSIBLE";
			return;
		}
	}
	cout << "POSSIBLE\n";
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] < id[i * 2 + 1]) {
			cout << 0 << ' ';
		} else {
			cout << 1 << ' ';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}