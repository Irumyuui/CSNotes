#include <bits/stdc++.h>
#include <execution>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (auto &x : a) std::cin >> x;
    std::sort(std::execution::par_unseq, a.begin(), a.end());
    std::cout << a[k] << '\n';
}