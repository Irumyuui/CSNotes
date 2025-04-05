#include <bits/stdc++.h>
using namespace std;

inline int lowbit(int x){
    return x & -x;
}

const int N = 1e5 + 10;
int tr[N];

inline void add(int x, int len, int k){
    while (x <= len){
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
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m --){
        int k;
        cin >> k;

        if (k == 1){
            int l, r;
            cin >> l >> r;
            add(l, n, 1);
            add(r + 1, n, 1);
        }else{
            int pos;
            cin >> pos;
            cout << (query(pos) & 1) << '\n';
        }
    }

    return 0;
}