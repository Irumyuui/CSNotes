#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

class edge{
    public:
        int a, b;
        double len;
        edge() = default;
        edge(const int &a, const int &b, const double &len){
            this->a = a, this->b = b, this->len = len;
        }
        bool operator<(const edge &a) const{
            return this->len < a.len;
        }
};

vector<int>dad;
vector<PII>v;
vector<edge>ed;

int Find(int v){
    if (dad[v] != v)
        dad[v] = Find(dad[v]);
    return dad[v];
}

bool Union(int a, int b){
    a = Find(a);
    b = Find(b);
    if (a == b)
        return false;
    else
        dad[b] = a;
    return true;
}

inline double getlen(const PII &a, const PII &b){
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

inline void getedge(){
    for (int i = 0; i < v.size() - 1; ++ i)
        for (int j = i + 1; j < v.size(); ++ j)
            ed.push_back(edge(i, j, getlen(v[i], v[j])));
    sort(ed.begin(), ed.end(), less<edge>());
}

double kurskal(){
    getedge();
    double ans = -1, cnt = v.size();
    for (auto it : ed){
        if (Union(it.a, it.b))
            ans = max(ans, it.len);
        if (cnt == 1)
            break;
    }
    return ans;
}

void solve(){
    int m;
    cin >> m;
    vector<int>monkey(m);
    for (auto &it : monkey) cin >> it;
    int n;
    cin >> n;
    dad = vector<int>(n);
    v = vector<PII>(n);
    for (int i = 0; i < n; ++ i){
        cin >> v[i].first >> v[i].second;
        dad[i] = i;
    }
    int ans = 0;
    double len = kurskal();
    for (auto it : monkey)
        if (it >= len)
            ans ++;
    cout << ans;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}