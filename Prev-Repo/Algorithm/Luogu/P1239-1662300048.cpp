#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	array<ll, 10> ans{};
	array<array<ll, 21>, 21> f{};
	auto work = [&](ll x) {
		vector<int> digit;
		do {
			digit.push_back(x % 10);
			x /= 10;
		} while (x);
		function<ll(int,int,int,bool,bool)> dfs = [&](int id, int cnt, int tag, bool lead, bool limit) -> ll {
			if (id == -1) return cnt;
			if (!lead && !limit && f[id][cnt] != -1) return f[id][cnt];
			int LIMIT = limit ? digit[id] : 9;
			ll ret = 0;
			for (int i = 0; i <= LIMIT; ++ i) {
				ret += dfs(id - 1, cnt + ((!tag && !i && !lead) || (tag && tag == i)), tag, lead && i == 0, limit && i == LIMIT);				
			}
			if (!lead && !limit) {
				f[id][cnt] = ret;
			}
			return ret;
		};
		for (int i = 0; i <= 9; ++ i) {
			for (auto &&i : f) {
				ranges::fill(i, -1);
			}
			ans[i] += dfs(int(digit.size()) - 1, 0, i, true, true);
		}
	};	

	ll n;
	cin >> n;
	work(n);
	for (auto i : ans) {
		cout << i << '\n';
	}
}