#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int dfn[N], low[N], id[N], stamp = 0, scc_cnt = 0;
stack<int> st;
bool inst[N];
int n, m;
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
		scc_cnt ++;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			inst[now] = false;
			id[now] = scc_cnt;
		} while (now != from);
	}
}

void Solution() {
	cin >> n >> m;
	while (m --) {
		int i, a, j, b;
		cin >> i >> a >> j >> b;
		i --; j --;
		// add(i * 2 + 1, )
		if (a && b) {
			add(i * 2 + 1, j * 2);
			add(j * 2 + 1, i * 2);
		} else if (a && !b) {
			add(i * 2 + 1, j * 2 + 1);
			add(j * 2, i * 2);
		} else if (!a && b) {
			add(i * 2, j * 2);
			add(j * 2 + 1, i * 2 + 1);
		} else {
			add(i * 2, j * 2 + 1);
			add(j * 2, i * 2 + 1);
		}
	}
	for (int i = 0; i < 2 * n; ++ i) if (!dfn[i])
		tarjan(i);
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] == id[i * 2 + 1]) {
			cout << "IMPOSSIBLE\n";
			return;
		}
	}
	cout << "POSSIBLE\n";
	for (int i = 0; i < n; ++ i) {
		cout << (id[i * 2] < id[i * 2 + 1]) << ' ';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}