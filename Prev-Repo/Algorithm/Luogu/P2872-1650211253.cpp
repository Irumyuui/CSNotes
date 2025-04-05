#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)
namespace __IO_int128 {
    std::istream& operator >> (std::istream &is, __int128_t &x) {
        x = 0;
        std::string s;
        is >> s;
        bool flag = false;
        for (auto ch : s) 
            if (ch == '-')
                flag = true;
            else
                x = x * 10 + (ch ^ 48);
        if (flag) x = -x;
        return is;
    }
    std::ostream& operator << (std::ostream &os, __int128_t x) {
        if (x == 0) return os << '0';
        bool flag = false;
        if (x < 0) {
            x = -x; flag = true;
        }
        std::string s;
        while (x > 0) {
            s += x % 10 + '0'; x /= 10;
        }
        if (flag) s += '-';
        std::reverse(s.begin(), s.end());
        return os << s;
    }
}
namespace __IO_FAST {
    template <class T> inline void read(T &val) {
        T x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -1;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48);
            ch = getchar();
        }
        val = x * f;
    }
    template <class T> void write(T x) {
        static char a[100];
        if (x == 0) {
            putchar('0');
            return;
        }
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        int cnt = 0;
        while (x) {
            a[++ cnt] = x % 10 + '0';
            x /= 10;
        }
        while (cnt)
            putchar(a[cnt --]);
    }
}
using namespace __IO_int128;

using ill = __int128_t;
using ld = long double;

struct point {
    int x, y;
};
struct edge {
    int u, v;
    ld len;
};

class DST {
    private:
        std::vector<int> dad;
        int cnt;
    public:
        DST(int size) {
            dad.assign(size + 1, -1);
            cnt = size;
        }
        void init(int size) {
            dad.assign(size + 1, -1);
            cnt = size;
        }
        int& operator [] (int i) {
            return dad[i];
        }
        int Find(int now) {
            if (dad[now] > 0)
                return dad[now] = Find(dad[now]);
            return now;
        }
        bool Union(int a, int b) {
            a = Find(a); b = Find(b);
            if (a == b)
                return false;
            dad[a] += dad[b];
            dad[b] = a;
            cnt --;
            return true;
        }
        const int count() const {
            return cnt;
        }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    vector<point> v(n + 1);
    for (int i = 1; i <= n; ++ i) {
        cin >> v[i].x >> v[i].y;
    }

    DST dst(n + 1);
    for (int i = 1; i <= m; ++ i) {
        int u, v;
        cin >> u >> v;
        dst.Union(u, v);
    }

    vector<edge> eds;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            eds.push_back({i, j, hypot<ld>(v[i].x - v[j].x, v[i].y - v[j].y)});
        }
    }
    sort(all(eds), [](const auto &a, const auto &b) {
        return a.len < b.len;
    });

    ld ans = 0;
    for (auto &[a, b, w] : eds) {
        if (dst.Union(a, b)) {
            ans += w;
        }
    }
    cout << fixed << setprecision(2) << ans;
    
    return 0;
}