#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f[22][22];
ll digit[22];
ll ans[10];
int len = 0;

void Solution() {
	function<ll(int,int,int,bool,bool)> dfs = [&](int id, int cnt, int tag, bool lead, bool limit) -> ll {
		if (!id) return cnt;
		if (!lead && !limit && f[id][cnt] != -1) {
			return f[id][cnt];
		}
		ll ret = 0;
		int LIMIT = limit ? digit[id] : 9;
		for (int i = 0; i <= LIMIT; ++ i) {
			ret += dfs(id - 1, cnt + ((!i && !tag && !lead) || (tag && i == tag)), tag, lead && i == 0, limit && i == LIMIT);
		}
		if (!lead && !limit) {
			f[id][cnt] = ret;
		}
		return ret;
	};
	auto work = [&](ll x, int d) {
		len = 0;
		do {
			digit[++ len] = x % 10;
			x /= 10;
		} while (x);
		for (int i = 0; i <= 9; ++ i) {
			memset(f, -1, sizeof f);
			ans[i] += d * dfs(len, 0, i, true, true);
		}
	};

	ll a, b;
	cin >> a >> b;
	work(a - 1, -1);
	// #ifndef ONLINE_JUDGE
	// 	for (int i = 0; i <= 9; ++ i) {
	// 		cout << ans[i] << ' ';
	// 	}
	// #endif
	work(b, 1);
	for (int i = 0; i <= 9; ++ i) {
		cout << ans[i] << ' ';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}