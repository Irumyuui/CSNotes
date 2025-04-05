#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    cin >> n;

    int cnt5 = 0, cnt0 = 0;
    for (int i = 0; i < n; ++ i) {
        int x;
        cin >> x;

        if (x == 5) {
            cnt5 ++;
        } else if (x == 0) {
            cnt0 ++;
        }
    }

    if (cnt0 == 0) {
        cout << -1;
    } else if (cnt5 < 9) {
        cout << 0;
    } else {
        while (cnt5 >= 9) {
            for (int i = 0; i < 9; ++ i) {
                cout << 5;
            }
            cnt5 -= 9;
        }
        for (int i = 0; i < cnt0; ++ i) {
            cout << 0;
        }
    }
    
    return 0;
}