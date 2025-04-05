#include <iostream>
#include <vector>

using namespace std;

vector<int>arr;
vector<int>add;

int main()
{
    int n;
    cin >> n;
    arr = vector<int>(n);
    add = vector<int>(n);
    int res = -0x7fffffff;
    for (int i = 0; i < n; ++ i)
    {
        cin >> arr[i];
        if (i){
            add[i] = max(add[i - 1] + arr[i], arr[i]);
        }else{
            add[i] = arr[i];
        }
        res = max(add[i], res);
    }
    // int res = -0x7fffffff;
    // for (int i = 0; i < n; ++ i)
    // {
    //     res = max(add[i], res);
    //     for (int j = i + 1; j < n; ++ j)
    //     {
    //         res = max(add[j] - add[i], res);
    //     }
    // }
    cout << res;
    // cout << add[n - 1];
    return 0;
}