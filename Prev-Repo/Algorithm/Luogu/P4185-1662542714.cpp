/* P4185 [USACO18JAN]MooTube G */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

struct Edge {
	int k, a, b;
	friend auto operator <=> (const Edge &a, const Edge &b) = default;
};
struct Que {
	int k, v, id;
	friend auto operator <=> (const Que &a, const Que &b) = default;
};

vector<int> dad;
int Find(int i) {
	if (dad[i] < 0) {
		return i;
	}
	return dad[i] = Find(dad[i]); 
}
bool Merge(int a, int b) {
	a = Find(a); b = Find(b);
	if (a == b) return false;
	dad[b] += dad[a];
	dad[a] = b;
	return true;
}

void Solution() {
	int n, q;
	cin >> n >> q;
	vector<Edge> ed(n - 1);
	for (auto &&x : ed) {
		cin >> x.a >> x.b >> x.k;
	}	
	sort(begin(ed), end(ed), [](const auto &a, const auto &b) {
		return a.k > b.k;
	});
	vector<Que> Q(q);
	for (int i = 0; i < q; ++ i) {
		cin >> Q[i].k >> Q[i].v;
		Q[i].id = i;
	}
	sort(begin(Q), end(Q), [](const auto &a, const auto &b) {
		return a.k > b.k;
	});
	dad.assign(n + 1, -1);
	vector<int> ans(q);
	for (int i = 0, j = 0; i < q; ++ i) {
		while (j < n - 1 && Q[i].k <= ed[j].k) {
			Merge(ed[j].a, ed[j].b);
			j ++;
		}
		ans[Q[i].id] = dad[Find(Q[i].v)];
	}
	for (auto x : ans) {
		cout << -(x + 1) << '\n';
	}	
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}