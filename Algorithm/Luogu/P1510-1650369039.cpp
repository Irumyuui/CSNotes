/**
 * @file P1510 精卫填海.cpp
 * @author Cieru
 * @date 2022-04-19
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int sv, sc, n;
    cin >> sv >> n >> sc;

    vector<int> v(n), c(n);
    for (int i = 0; i < n; ++ i) {
        cin >> v[i] >> c[i];
    }

    vector<int> dp(sc + 1, 0);
    for (int i = 0; i < n; ++ i) {
        for (int j = sc; j >= c[i]; -- j) {
            dp[j] = max(dp[j], dp[j - c[i]] + v[i]);
        }
    }

    for (int i = 0; i <= sc; ++ i) {
        if (dp[i] >= sv) {
            cout << sc - i << '\n';
            return 0;
        }
    }
    cout << "Impossible" << '\n';

    return 0;
}