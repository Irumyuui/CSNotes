#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	for (; t --; ) {
		unordered_set<int> ht;
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++ i) {
			int x;
			cin >> x;
			if (!ht.count(x)) {
				cout << x << ' ';
				ht.insert(x);
			}
		}
		cout << '\n';
	}
}