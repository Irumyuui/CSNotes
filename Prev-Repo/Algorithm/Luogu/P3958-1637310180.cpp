#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

LL QuickPow(LL a, LL i){
    LL res = 1;
    while (i){
        if (i & 1)
            res *= a;
        a *= a;
        i >>= 1;
    }
    return res;
}

class posision{
    public:
        int x, y, z;
        posision() = default;
        posision(const int &x, const int &y, const int &z){
            this->x = x, this->y = y, this->z = z;
        }
};

bool operator<(const posision &a, const posision &b){
    return a.z < b.z;
}

int n, h, r;
vector<posision>v;
vector<bool>vis;

inline double zdist(const int &z, const posision &a){
    return abs(z - a.z);
}

inline double posdist(const posision &a, const posision &b){
    return sqrt(QuickPow(a.x - b.x, 2) + QuickPow(a.y - b.y, 2) + QuickPow(a.z - b.z, 2));
}

bool dfs(const int &p){
    if (zdist(h, v[p]) <= r){
        return true;
    }
    vis[p] = true;
    for (int i = 0; i < n; ++ i){
        if (!vis[i] && posdist(v[p], v[i]) <= (r << 1)){
            if (dfs(i)){
                return true;
            }
        }
    }
    return false;
}

bool stadfs(){
    for (int i = 0; i < n; ++ i){
        if (zdist(0, v[i]) <= r){
            if (dfs(i)){
                return true;
            }
        }
    }
    return false;
}

void solve(){
    v.clear();
    vis.clear();
    cin >> n >> h >> r;
    v = vector<posision>(n);
    vis = vector<bool>(n, false);
    for (auto &it : v)
        cin >> it.x >> it.y >> it.z;
    //sort(v.begin(), v.end(), less<posision>());
    if (stadfs())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    int cnt;
    cin >> cnt;
    while (cnt --)
        solve();
    return 0;
}