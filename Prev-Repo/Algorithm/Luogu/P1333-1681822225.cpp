#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n = 0;
	auto GetId = [&, ump{unordered_map<string,int>{}}](const string &s) mutable -> int {
		if (!ump.contains(s)) {
			ump[s] = ump.size();
		}
		n = max(n, ump[s]);
		return ump[s];
	};
	
	vector<pair<int,int>> edge;
	string ta, tb;
	while (cin >> ta >> tb) {
		int u = GetId(ta), v = GetId(tb);
		edge.emplace_back(u, v);
	}
	n ++;

	vector<int> dad(n, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1)
			return x;
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b)
			return false;
		dad[a] = b;
		return true;
	};

	vector<int> deg(n);
	for (auto &[u, v] : edge) {
		deg[u] ++; deg[v] ++;
		Merge(u, v);
	}
	if (auto tmp = ranges::count_if(deg, [](int cnt) { return cnt % 2 != 0; }); ranges::count(dad, -1) != 1 || (tmp != 0 && tmp != 2)) {
		cout << "Impossible\n";
	} else {
		cout << "Possible\n";
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}