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

const int mod = 1e8;
const int N = 2e3 + 10;
ll n, f;
ll dp[N][N];
ll p[N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> f;
	for (int i = 1; i <= n; ++ i) {
		cin >> p[i];
	}
	for (int i = 1; i <= n; ++ i) {
		dp[i][p[i] % f] = 1;
		for (int j = 0; j < f; ++ j) {
			dp[i][j] = (dp[i][j] + dp[i - 1][j] + dp[i - 1][((j - p[i]) % f + f) % f]) % mod;
		}
	}
	cout << dp[n][0];
}