#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N = 110;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int n;

int low[N], dfn[N], step, scc, id[N];
bool inst[N];
stack<int> st;
int ind[N], outd[N];

void tarjan(int u) {
	dfn[u] = low[u] = ++ step;
	st.push(u);
	inst[u] = true;
	for (auto v : edge[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[v], low[u]);
		} else if (inst[v]) {
			low[u] = min(low[v], low[u]);
		}
	}
	if (dfn[u] == low[u]) {
		int v = 0;
		++ scc;
		do {
			v = st.top();
			st.pop();
			inst[v] = false;
			id[v] = scc;
		} while (v != u);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		int v;
		while (cin >> v && v) {
			add(i, v);
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
				outd[id[i]] ++;
			}
		}
	}

	if (scc == 1) {
		cout << 1 << endl;
		cout << 0 << endl;
		return 0;
	}

	int in = 0, out = 0;
	for (int i = 1; i <= scc; ++ i) {
		in += ind[i] == 0;
		out += outd[i] == 0;
	}
	cout << in << endl;
	cout << max(in, out) << endl;
}