#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
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
#define debug(...) std::cerr << __LINE__ << ": ", _debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif

#define all(x) std::begin(x), std::end(x)
#define pback(val) push_back(val)
#define pfront(val) push_front(val)

using ll = long long;
using ill = __int128_t;

constexpr int INF = 1 << 30;
constexpr double eps = 1e-8;

inline int sgn(double x) {
    if (std::abs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
inline int dcmp(double x, double y) {
    if (std::abs(x - y) < eps)
        return 0;
    return x < y ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

inline double lengh(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<Point>v(n);
    for (auto &[x, y] : v) {
        cin >> x >> y;
    }
    double ans = INF;
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            ans = min(ans, lengh(v[i], v[j]));
        }
    }
    cout << fixed << setprecision(4) << ans;

    return 0;
}