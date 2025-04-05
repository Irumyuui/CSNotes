#include <bits/stdc++.h>
using namespace std;
const int INFI = 0x7FFFFFFF;
const long long INFLL = 0x7FFFFFFFFFFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

struct posision{
    double x, y, z;
}arr[50000];

bool operator<(const posision &a, const posision &b){
    return a.z < b.z;
}

inline double getlen(const posision &a, const posision &b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

void solve(){
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i){
        cin >> arr[i].x >> arr[i].y >> arr[i].z;
    }
    sort(arr, arr + n, less<posision>());
    double res = 0;
    for (int i = 1; i < n; ++ i){
        res += getlen(arr[i - 1], arr[i]);
    }
    cout << fixed << setprecision(3) << res << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}