#include <bits/stdc++.h>

const int LEN = 1e5 + 10;
int arr[LEN], t[LEN];

void mergesort(int ll, int rr){
    if (rr - ll <= 1) return;
    int mid = ll + ((rr - ll) >> 1);
    mergesort(ll, mid); mergesort(mid, rr);
    int tp = ll, lp = ll, rp = mid;
    while (lp < mid && rp < rr)
        if (arr[lp] > arr[rp]) t[tp ++] = arr[rp ++];
        else t[tp ++] = arr[lp ++];
    while (lp < mid) t[tp ++] = arr[lp ++];
    while (rp < rr) t[tp ++] = arr[rp ++];
    for (int i = ll; i < rr; ++ i)
        arr[i] = t[i];
}

void solve(){
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++ i) std::cin >> arr[i];
    mergesort(0, n);
    for (int i = 0; i < n; ++ i) std::cout << arr[i] << ' ';
}

int main(){
    std::ios::sync_with_stdio(false);
    solve();
    return 0;
}