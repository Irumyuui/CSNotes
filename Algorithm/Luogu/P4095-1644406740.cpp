#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct toy{
    int id;
    ll a, b, c;
}toys[100010];
int tot = 1;

const int N = 1e3 + 10;
ll dp1[100010][N], dp2[100010][N];
int pos[100010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++ i){
        ll a, b, c;
        cin >> a >> b >> c;

        pos[i] = tot;

        ll k = 1;
        while (k <= c){
            toys[tot].a = a * k;
            toys[tot].b = b * k;
            toys[tot].c = k;
            toys[tot].id = i;
            tot ++;
            
            c -= k;
            k <<= 1;
        }
        if (c > 0){
            toys[tot].a = a * c;
            toys[tot].b = b * c;
            toys[tot].c = c;
            toys[tot].id = i;
            tot ++;
        }
    }
    pos[n] = tot;

    for (int i = 1; i < tot; ++ i){
        for (int j = 1e3; j >= 0; -- j){
            if (j >= toys[i].a){
                dp1[i][j] = max(dp1[i - 1][j], dp1[i - 1][j - toys[i].a] + toys[i].b);
            }else{
                dp1[i][j] = dp1[i - 1][j];
            }
        }
    }

    for (int i = tot - 1; i >= 1; -- i){
        for (int j = 1e3; j >= 0; -- j){
            if (j >= toys[i].a){
                dp2[i][j] = max(dp2[i + 1][j], dp2[i + 1][j - toys[i].a] + toys[i].b);
            }else{
                dp2[i][j] = dp2[i + 1][j];
            }
        }
    }

    toys[0].id = -1;

    int t;
    cin >> t;
    while (t --){
        int no, W;
        cin >> no >> W;
        
        int l = 0, r = 0;
        while (toys[l + 1].id < no && l < tot){
            l ++;
        }
        r = l;
        while (toys[r + 1].id <= no && r < tot){
            r ++;
        }
        r ++;
        
        ll ans = 0;
        for (int i = W; i >= 0; -- i){
            ans = max(ans, dp1[l][i] + dp2[r][W - i]);
        }

        cout << ans << '\n';
    }

    return 0;
}