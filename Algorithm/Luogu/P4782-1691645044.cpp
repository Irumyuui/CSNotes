#include <bits/stdc++.h>
using namespace std;

#pragma region
template <class T> inline void read(T &val) {
	T x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	val = x * f;
}
template <class T, class... Args> inline void read(T &val, Args&... args) {
	read(val); read(args...);
}
template <class T> inline void write(T x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
template <> inline void write<char> (char x) {
	putchar(x);
}
template <class T, class... Args> inline void write(T val, Args... args) {
	write(val); putchar(' '); write(args...);
}
#pragma endregion

const int N = 2e6 + 10;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int dfn[N], low[N], stamp = 0, id[N], scc_cnt = 0;
// stack<int> st;
int st[N], tt = 0;
bool inst[N];
void tarjan(int from) {
	dfn[from] = low[from] = ++ stamp;
	st[++ tt] = from;
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
		++ scc_cnt;
		int now = 0;
		do {
			now = st[tt --];
			inst[now] = false;
			id[now] = scc_cnt;
		} while (now != from);
	}
}
int n, m;

auto Solution() {
	read(n, m);
	while (m --) {
		int i, a, j, b;
		read(i, a, j, b);
		i --; j --;
		add(i * 2 + !a, j * 2 + b);
		add(j * 2 + !b, i * 2 + a);
	}
	for (int i = 0; i < 2 * n; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] == id[i * 2 + 1]) {
			puts("IMPOSSIBLE");
			return;
		}
	}
	puts("POSSIBLE");
	for (int i = 0; i < n; ++ i) {
		if (id[i * 2] < id[i * 2 + 1]) {
			printf("0 ");
		} else {
			printf("1 ");
		}
	}
}

int main() {
	Solution();
}