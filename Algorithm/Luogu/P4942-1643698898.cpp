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
    int t;
    cin >> t;
    while (t --){
        LL ll, rr;
        cin >> ll >> rr;
        ILL l = ll, r = rr;
        LL ans = ((r - l + 1) & 1 ? (l + r) / 2 * (r - l + 1) : (r - l + 1) / 2 * (l + r)) % 9;
        cout << ans << '\n';
    }
    return 0;
}