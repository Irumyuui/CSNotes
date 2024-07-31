#include<iostream>
using namespace std;
typedef long long LL;
const int len = 5e5 + 10;
LL arr[len], t[len];
LL ans = 0;
void mergesort(int ll, int rr){
    if (rr - ll <= 1) return;
    int mid = ll + ((rr - ll) >> 1);
    mergesort(ll, mid); mergesort(mid, rr);
    int p = ll, q = ll, r = mid;
    while (q < rr){
        if (p >= mid || (r < rr && arr[p] > arr[r])){
            t[q ++] = arr[r ++];
            ans += mid - p;
        }else{
            t[q ++] = arr[p ++];
        }
    }
    for (int i = ll; i < rr; ++ i)
        arr[i] = t[i];
}
int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> arr[i];
    mergesort(0, n);
    cout << ans << endl;
    return 0;
}