#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

inline void SFAST(const char *text){FREIN(text);FAST();}

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

unordered_map<int, int>unm;
vector<int>B;

inline void read(){
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i){
        int x;
        cin >> x;
        unm[x] = i;
    }
    for (int i = 0; i < n; ++ i){
        int x;
        cin >> x;
        if (unm.find(x) != unm.end())
            B.push_back(unm[x]);
    }
    return;
}

int getrise(){
    vector<int>rise;
    rise.push_back(B[0]);
    for (int i = 1; i < B.size(); ++ i){
        if (rise.back() < B[i]){
            rise.push_back(B[i]);
        }else{
            vector<int>::iterator it = lower_bound(rise.begin(), rise.end(), B[i], less<int>());
            *it = B[i];
        }
    }
    return rise.size();
}

void solve(){
    read();
    cout << getrise() << endl;
    return;
}

int main(){
    // SFAST("in.in");
    FAST();
    solve();
    return 0;
}