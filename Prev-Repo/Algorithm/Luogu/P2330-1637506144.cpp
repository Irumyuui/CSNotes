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
        int a, b, w;
        edge() = default;
        edge(const int &a, const int &b, const int &w){
            this->a = a, this->b = b, this->w = w;
        }
        bool operator<(const edge &a) const{
            return this->w < a.w;
        }
};

vector<int>dad;
// vector<vector<PII>>g;
vector<edge>ve;

int Find(int v){
    if (dad[v] != -1){
        return dad[v] = Find(dad[v]);
    }
    return v;
}

bool Union(int a, int b){
    a = Find(a);
    b = Find(b);
    if (a == b)
        return false;
    else
        dad[a] = b;
    return true;
}

void solve(){
    int n, m;
    cin >> n >> m;
    dad = vector<int>(n + 1, -1);
    for (int i = 0; i < m; ++ i){
        int a, b, w;
        cin >> a >> b >> w;
        ve.push_back(edge(a, b, w));
    }
    sort(ve.begin(), ve.end(), less<edge>());
    int ans = -1, cnt = 0;
    for (auto it : ve){
        if (Union(it.a, it.b)){
            ans = max(ans, it.w);
            cnt ++;
        }
        if (cnt == n - 1){
            break;
        }
    }
    cout << cnt << ' ' << ans << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}