#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
#define cauto const auto

using ll = long long;
using LL = __int128_t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    stack<int>st;

    ll ans = 0;
    for (int i = 0; i < n; ++ i) {
        int x;
        cin >> x;
        while (!st.empty() && st.top() <= x) {
            st.pop();
        }
        ans += st.size();
        st.push(x);
    }

    cout << ans;

    return 0;
}