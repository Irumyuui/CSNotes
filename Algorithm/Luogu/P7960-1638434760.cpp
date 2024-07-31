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

const int LEN = 1e7 + 5;

bool arr[LEN];
vector<int>ans;

bool isnum7(int num){
    while (num){
        if (num % 10 == 7)
            return true;
        num /= 10;
    }
    return false;
}

void getans(){
    memset(arr, false, sizeof(arr));
    for (int i = 1; i < LEN; ++ i){
        if (!arr[i] && isnum7(i)){
            for (int j = i; j < LEN; j += i){
                arr[j] = true;
            }
        }else if (!arr[i]){
            ans.push_back(i);
        }
    }
}

void solve(){
    int x;
    cin >> x;
    if (arr[x]){
        cout << -1 << endl;
    }else{
        vector<int>::iterator it = upper_bound(ans.begin(), ans.end(), x);
        cout << *it << endl;
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    getans();
    int t;
    cin >> t;
    while (t --)
        solve();
    return 0;
}