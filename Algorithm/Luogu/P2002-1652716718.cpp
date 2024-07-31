#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> edge[N];
int din[N], dfn[N], low[N], id[N], scc, step;
bool inst[N];
stack<int> st;
void tarjan(int now) {
	dfn[now] = low[now] = ++ step;
	st.push(now);
	inst[now] = true;
	for (auto nex : edge[now]) {
		if (!dfn[nex]) {
			tarjan(nex);
			low[now] = min(low[now], low[nex]);
		} else if (inst[nex]) {
			low[now] = min(low[now], low[nex]);
		}
	}
	if (dfn[now] == low[now]) {
		int tmp = 0;
		++ scc;
		do {
			tmp = st.top();
			st.pop();
			inst[tmp] = false;
			id[tmp] = scc;
		} while (tmp != now);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
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
		for (auto j : edge[i]) {
			if (id[i] != id[j]) {
				din[id[j]] ++;
			}
		}
	}
	cout << count(din + 1, din + 1 + scc, 0) << '\n';
}