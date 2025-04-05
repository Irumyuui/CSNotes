#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 10;

int f[MAXN] = {1, 2, 3};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    cin >> f[4] >> f[5];
    cout << f[4] + f[5] << '\n';
    
    return 0;
}