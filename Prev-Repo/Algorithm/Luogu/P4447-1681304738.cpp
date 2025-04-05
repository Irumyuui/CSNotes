#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	ranges::sort(a);

	map<int,priority_queue<int,vector<int>,greater<>>> mp;
	for (auto &x : a) {
		if (auto it = mp.find(x - 1); it != mp.end()) {
			if (!it->second.empty()) {
				auto pre = it->second.top();
				it->second.pop();
				mp[x].emplace(pre + 1);
				if (it->second.empty()) {
					mp.erase(it);
				}
			} else {
				mp[x].emplace(1);
			}
		} else {
			mp[x].emplace(1);
		}
	}
	
	int ans = inf<int>;
	for (auto &[a, b] : mp) {
		if (!b.empty()) {
			ans = min(ans, b.top());
		}
	}

	cout << ans << '\n';
}