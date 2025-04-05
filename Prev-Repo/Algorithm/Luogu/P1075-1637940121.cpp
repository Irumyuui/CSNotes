#include <bits/stdc++.h>
int main(){
    std::ios::sync_with_stdio(false);
    int n, i;
    std::cin >> n;
    for (i = 2; i <= sqrt(n); ++ i)
        if (!(n % i)) break;
    std::cout << n / i;
    return 0;
}