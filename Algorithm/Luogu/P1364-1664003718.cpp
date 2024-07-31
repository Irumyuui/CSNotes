/* P1364 医院设置 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;
using ld = long double;

const int N = 1e5 + 10;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

#define int long long

int vw[N], siz[N], f[N], ff[N], ssiz[N];
int n;

void down(int from, int dad) {
	siz[from] = vw[from];
	for (auto to : edge[from]) {
		if (to != dad) {
			down(to, from);
			f[from] += f[to] + siz[to];
			siz[from] += siz[to];
		}
	}
}

void rise(int from, int dad) {
	for (auto to : edge[from]) {
		if (to != dad) {
			ssiz[to] = siz[from] - siz[to] + ssiz[from];
			ff[to] = f[from] - f[to] - siz[to] + (siz[from] - siz[to]) + ff[from] + ssiz[from];
			rise(to, from);
		}
	}
}

void Solution() {
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		int a, b;
		cin >> vw[i] >> a >> b;
		if (a) add_edge(i, a);
		if (b) add_edge(i, b);
	}
	down(1, 0);
	rise(1, 0);

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; i ++) {
			debug(i, f[i], ff[i], siz[i], ssiz[i]);
		}
	#endif
	
	int ans = inf<int>;
	for (int i = 1; i <= n; i ++) {
		ans = min(ans, f[i] + ff[i]);
		debug(ans);
	}
	cout << ans << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}