#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e6 + 10;

struct date{
    int val, id, i;
};

date a[N];
int b[N];

ll tr[N];

inline int lowbit(int x){
    return x & -x;
}

inline void add(int x, int n, int k){
    while (x <= n){
        tr[x] += k;
        x += lowbit(x);
    }
}

inline ll query(int x){
    ll res = 0;
    while (x){
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i){
        cin >> a[i].val;
        a[i].id = i;
        b[i] = a[i].val;
    }

    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b;

    ll ans = 0;
    for (int i = 1; i <= n; ++ i){
        a[i].i = lower_bound(b + 1, b + len, a[i].val) - b;
        add(a[i].i, n, 1);
        ans += i - query(a[i].i);
    }

    cout << ans << '\n';

    return 0;
}