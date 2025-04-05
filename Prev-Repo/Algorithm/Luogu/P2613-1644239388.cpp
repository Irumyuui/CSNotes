#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

LL Exgcd(LL a, LL b, LL &x, LL &y){
    if (b == 0){
        x = 1; y = 0;
        return a;
    }
    LL d = Exgcd(b, a % b, x, y);
    LL t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

LL MOD = 19260817;

void inti(LL &a, LL &b){
    string a_, b_;
    cin >> a_ >> b_;
    a = b = 0;
    for (cauto &it : a_){
        a = (a * 10 + LL(it - '0')) % MOD;
    }
    for (cauto &it : b_){
        b = (b * 10 + LL(it - '0')) % MOD;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    LL a, b;
    inti(a, b);
    LL d, x, y;
    d = Exgcd(b, MOD, x, y);
    if (d != 1){
        cout << "Angry!";
    }else{
        cout << (a % MOD) * ((x + MOD) % MOD) % MOD;
    }
    return 0;
}