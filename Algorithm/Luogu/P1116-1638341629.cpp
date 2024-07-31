#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
typedef long long LL;

const int LEN = 1e5 + 5;
int arr[LEN], t[LEN];
LL cnt = 0;

void mergesort(int ll, int rr){
    if (rr - ll <= 1) return;
    int mid = ll + ((rr - ll) >> 1);
    mergesort(ll, mid); mergesort(mid, rr);
    int tpos = ll, apos = ll, bpos = mid;
    while (apos < mid && bpos < rr){
        if (arr[apos] > arr[bpos]){
            t[tpos ++] = arr[bpos ++];
            cnt += mid - apos;
        }else{
            t[tpos ++] = arr[apos ++];
        }
    }
    while (apos < mid) t[tpos ++] = arr[apos ++];
    while (bpos < rr) t[tpos ++] = arr[bpos ++];
    for (int i = ll; i < rr; ++ i) arr[i] = t[i];
}

void solve(){
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> arr[i];
    mergesort(0, n);
    cout << cnt << endl;
}

int main(){
    FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}