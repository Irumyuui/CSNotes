#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

ILL c[60][60];



int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    c[1][1] = c[1][0] = 1;
    for (int i = 2; i <= 55; ++ i){
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++ j){
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    int n, a, b;
    cin >> n >> a >> b;
    ILL ans = 0;
    for (int i = 0; i <= a; ++ i){
        for (int j = 0; j <= b; ++ j){
            ans += c[i - 1 + n][n - 1] * c[j - 1 + n][n - 1];
        }
    }
    stack<int>s;
    while (ans){
        s.push(ans % 10);
        ans /= 10;
    }
    while (!s.empty()){
        cout << s.top();
        s.pop();
    }
    return 0;
}