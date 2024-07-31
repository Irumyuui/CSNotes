#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    vector<int> c(n, 0);
    int l = 0, r = 0;
    for (int i = 0; i < n; ++ i) {
        cin >> c[i];
        l = max(c[i], l);
        r += c[i];
    }

    auto check = [&](int ans) -> bool {
        int cnt = 1, sum = 0;
        for (int i = 0; i < n; ++ i) {
            if (sum + c[i] > ans) {
                sum = 0;
                cnt ++;
            }
            sum += c[i];
        }
        return cnt <= m;
    }; 

    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << '\n';
    
    return 0;
}