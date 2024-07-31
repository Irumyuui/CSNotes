#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

template <int key>
struct hash_map {
	vector<vector<int>> hs;
	hash_map() : hs(key, vector<int>()) {}
	int getkey(int val) {
		return (val % key + key) % key;
	}
	bool add(int val) {
		int p = getkey(val);
		for (auto i : hs[p]) {
			if (i == val) {
				return false;
			}
		}
		hs[p].push_back(val);
		return true;
	}
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	for (; t --; ) {
		hash_map<101197> hst;
		int n;
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			int val;
			cin >> val;
			if (hst.add(val)) {
				cout << val << ' ';
			}
		}
		cout << endl;
	}
}