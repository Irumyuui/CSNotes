#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int ans = 0, x;
    char ch;

    bool allone = true;
    while (cin >> ch) {
        if (ch == '0') {
            allone = false;
            x ++;
        } else {
           x = max(0, x -  1);
        }
        ans = max(x, ans);        
    }

    if (allone) {
        cout << -1;
    } else {
        cout << ans << '\n';
    }

    return 0;
}