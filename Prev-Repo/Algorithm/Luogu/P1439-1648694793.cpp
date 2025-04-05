#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    
    std::map<int, int> a;
    for (int i = 1; i <= n; ++ i) {
        int x;
        std::cin >> x;
        a[x] = i;
    }
    std::vector<int> b(n);
    for (auto & x : b) {
        std::cin >> x;
        x = a[x];
    }
    std::vector<int> lcs;
    for (int i = 0; i < n; ++ i)
        if (lcs.empty() || lcs.back() < b[i]) {
            lcs.push_back(b[i]);
        } else {
            auto it = std::lower_bound(lcs.begin(), lcs.end(), b[i]);
            *it = b[i];
        }
    std::cout << lcs.size() << '\n';

    return 0;
}