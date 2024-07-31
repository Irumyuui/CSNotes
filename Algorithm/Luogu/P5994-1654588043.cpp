#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

struct info {
	int u, v;
	ll w;
};

const int N = 1e5 + 10;
int dad[N];
int Find(int id) {
	if (dad[id] != -1) {
		return dad[id] = Find(dad[id]);
	}
	return id;
}
bool Union(int a, int b) {
	a = Find(a); b = Find(b);
	if (a == b) {
		return false;
	}
	dad[a] = b;
	return true;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<info> edge;
	for (int i = 1; i <= n; ++ i) {
		for (int j = i; j <= n; ++ j) {
			ll w;
			cin >> w;
			edge.push_back(info{i, j, w});
		}
	}
	sort(edge.begin(), edge.end(), [](const auto &a, const auto &b) {
		return a.w < b.w;
	});
	ll ans = 0;
	memset(dad, -1, sizeof dad);
	for (auto [l, r, w] : edge) {
		if (Union(l - 1, r)) {
			ans += w;
		}
	}
	cout << ans;
}