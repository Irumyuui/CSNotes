#include <bits/stdc++.h>

int main(){
    int n, ans = 0;
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++ i){
        int x;
        scanf("%d", &x);
        ans ^= x;    
    }
    
    printf("%d", ans);
    
    return 0;
}