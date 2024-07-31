#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)

inline int lowbit(int x){
    return x & -x;
}

const int N = 1e5 + 10;
int tr[N];

int a[N], b[N];
int L[N], R[N];

inline void add(int x, int limit, int k = 1){
    while (x <= limit){
        tr[x] += k;
        x += lowbit(x);
    }
}

inline int query(int x){
    int res = 0;
    while (x){
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++ i){
        cin >> a[i];
    }
    
    copy(a + 1, a + 1 + n, b + 1);

    sort(b + 1, b + 1 + n);

    int len = unique(b + 1, b + 1 + n) - b - 1;

    for (int i = 1; i <= n; ++ i){
        int x = lower_bound(b + 1, b + 1 + len, a[i]) - b;
        add(x, len);
        L[i] = query(x - 1);

        a[i] = x;
    }
    
    fill(all(tr), 0);

    for (int i = n; i >= 1; -- i){
        int x = a[i];
        add(x, len);
        R[i] = n - i - query(x) + 1;
    }

    long long ans = 0;
    
    for (int i = 2; i < n; ++ i){
        ans += L[i] * R[i];
    }

    cout << ans << '\n';

    return 0;
}