#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using i128 = __int128_t;
using ULL = unsigned long long;

struct wood{
    i128 H, A;
};

bool check(i128 month, i128 S, i128 L, vector<wood>&v){
    i128 sum = 0;
    
    for (const auto &it : v){
        i128 temp = it.H + it.A * month;
        if (temp >= L){
            sum += temp;
            if (sum >= S){
                return true;
            }
        }
    }

    return sum >= S;
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ULL n, s_, l_;
    cin >> n >> s_ >> l_;
    i128 S = s_, L = l_;

    vector<wood>v(n);
    for (auto &it : v){
        ULL h;
        cin >> h;
        it.H = h;
    }
    for (auto &it : v){
        ULL a;
        cin >> a;
        it.A = a;
    }

    LL l = 0, r = 1ll << 62, ans = 0;
    while (l <= r){
        LL mid = l + ((r - l) >> 1);
        if (check(mid, S, L, v)){
            r = mid - 1;
        }else{
            l = mid + 1;
            ans = l;
        }
    }

    cout << ans;

    return 0;
}