#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    LL a, b;
    cin >> a >> b;
    cout << a * b - (a + b);
    return 0;
}