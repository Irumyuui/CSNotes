#include <bits/stdc++.h>
using namespace std;

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

const int N = 1e4 + 10;
vector<int> edge[N];
int col[N];
int n, m;
void add(int from, int to) {
	edge[from].push_back(to);
}
int cnt1, cnt2;
bool dfs(int now) {
	if (col[now] == 1) {
		cnt1 ++;
	} else {
		cnt2 ++;
	}
	for (auto nex : edge[now]) {
		if (!col[nex]) {
			col[nex] = 3 - col[now];
			if (!dfs(nex)) {
				return false;
			}
		} else if (col[nex] == col[now]) {
			return false;
		}
	}
	return true;
}

int main() {
	read(n, m);
	for (int i = 1; i <= m; ++ i) {
		int from, to;
		read(from, to);
		add(from, to);
		add(to, from);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i) {
		if (!col[i]) {
			cnt1 = 0, cnt2 = 0;
			col[i] = 1;
			if (!dfs(i)) {
				printf("Impossible");
				return 0;
			}
			ans += min(cnt1, cnt2);
		}
	}
	write(ans);
}