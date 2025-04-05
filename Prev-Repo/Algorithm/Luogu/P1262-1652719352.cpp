#include <bits/stdc++.h>
using namespace std;

#if defined(LOCAL_JD)
namespace __DE_BUG__N {
template<class T1, class T2>
std::ostream& operator << (std::ostream &os, std::pair<T1, T2> &x) {
	return os << "<" << x.first << ", " << x.second << ">";
}
template<class Tp>
std::ostream& operator << (std::ostream &os, std::vector<Tp> &x) {
	os << "[";
	for (auto it = x.begin(); it != x.end(); ++ it)
		os << (it != x.begin() ? ", " : "") << *it;
	return os << "]";
}
template<class T1, class T2>
std::ostream& operator << (std::ostream& os, std::map<T1, T2> &x) {
	os << "{";
	for (auto it = x.begin(); it != x.end(); ++ it)
		os << (it != x.begin() ? ", ": "") << "(" << it->first << " : " << it->second << ")";
	return os << "}";
}
template<class Tp>
std::ostream& operator << (std::ostream &os, std::set<Tp> &x) {
	os << "(";
	for (auto it = x.begin(); it != x.end(); ++ it)
		os << (it != x.begin() ? ", " : "") << *it;
	return os << ")";
}
template<typename T>
inline void _debug(const char *name, T tag) {
	std::cerr << name << "=" << tag << std::endl;
}
template<class T, class... T_>
inline void _debug(const char *name, T beg, T_... en) {
	while (*name != ',')
		std::cerr << *name ++;
	std::cerr << "=" << beg << ",";
	_debug(name + 1, en...);
}
}
using __DE_BUG__N::_debug;
#define debug(...) std::cerr << __LINE__ << ": ", _debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif
std::istream& operator >> (std::istream &is, __int128_t &x) {
	x = 0;
	std::string s; is >> s;
	bool flag = false;
	for (auto ch : s) 
			if (ch == '-') flag = true;
		else x = x * 10 + (ch ^ 48);
			if (flag) x = -x;
	return is;
}
std::ostream& operator << (std::ostream &os, __int128_t x) {
	if (x == 0) return os << '0';
	bool flag = false;
	if (x < 0) 
		x = -x, flag = true;
	std::string s;
	while (x > 0)
		s += x % 10 + '0', x /= 10;
	if (flag) s += '-';
		std::reverse(s.begin(), s.end());
	return os << s;
}
#define endl '\n'
#define range(...) std::begin(__VA_ARGS__), std::end(__VA_ARGS__)
#define MAX(x) (*std::max_element(range(x)))
#define MIN(x) (*std::min_element(range(x)))
using ll = long long;
using ld = long double;
using ill = __int128_t;

const int inf = 1 << 29;
const int N = 3010;
vector<int> edge[N];
int pay[N], dfn[N], low[N], scc = 0, step = 0, id[N];
int buy[N];
bool inst[N];
stack<int> st;
int din[N];
void trajan(int now) {
	dfn[now] = low[now] = ++ step;
	st.push(now);
	inst[now] = true;
	for (auto nex : edge[now]) {
		if (!dfn[nex]) {
			trajan(nex);
			low[now] = min(low[now], low[nex]);
		} else if (inst[nex]) {
			low[now] = min(low[now], low[nex]);
		}
	}
	if (dfn[now] == low[now]) {
		int tmp = 0;
		++ scc;
		do {
			tmp = st.top();
			st.pop();
			inst[tmp] = false;
			id[tmp] = scc;
			buy[scc] = min(buy[scc], pay[tmp]);
		} while(tmp != now);
	}
} 

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	fill_n(pay, n + 1, inf);
	fill_n(buy, n + 1, inf);
	int p;
	cin >> p;
	for (int i = 0; i < p; ++ i) {
		int a, b;
		cin >> a >> b;
		pay[a] = b;
	}
	cin >> p;
	for (int i = 0; i < p; ++ i) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			trajan(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j : edge[i]) {
			if (id[i] != id[j]) {
				din[id[j]] ++;
			}
		}
	}
	int ans = 0;
	bool ok = true;
	for (int i = 1; i <= scc; ++ i) {
		if (!din[i]) {
			if (buy[i] == inf) {
				if (ok) {
					ok = false;
					ans = inf;
				}
				for (int j = 1; j <= n; ++ j) {
					if (id[j] == i) {
						ans = min(ans, j);
						break;
					}
				}
			} else if (ok) {
				ans += buy[i];
			}
		}
	}

	if (ok)
		cout << "YES" << '\n' << ans << '\n';
	else
		cout << "NO" << '\n' << ans << '\n';
}