#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int>v(n);
    for (auto &it : v) cin >> it;
    if (prev_permutation(all(v)))
        for (auto it : v) cout << it << ' ';
    else
        cout << "ERROR";
    return 0;
}