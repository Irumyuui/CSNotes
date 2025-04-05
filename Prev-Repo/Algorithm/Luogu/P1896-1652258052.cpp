#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 11;
int n, k;
ll f[N][N * N][1 << N];
vector<int> mode, premode[1 << N], cnt(1 << N);

bool ok(int x) {
	return !(x & (x >> 1));
}
int Count(int x) {
	int cnt = 0;
	for (int i = 0; i < n; ++ i) cnt += x >> i & 1;
	return cnt; 
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < (1 << n); ++ i) 
		if (ok(i)) mode.push_back(i);
	for (auto now : mode) {
		cnt[now] = Count(now);
		for (auto pre : mode) {
			if (!(now & pre) && ok(now | pre)) premode[now].push_back(pre);
		}
	}
	f[0][0][0] = 1;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 0; j <= k; ++ j) {
			for (auto now : mode) {
				for (auto pre : premode[now]) {
					if (j >= cnt[now]) {
						f[i][j][now] += f[i - 1][j - cnt[now]][pre];
					}
				}
			}
		}
	}
	ll ans = 0;
	for (auto now : mode) ans += f[n][k][now];
	cout << ans << '\n';
}