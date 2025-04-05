#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

class medical{
    public:
        int win, lost, spend;
        medical(){
            win = lost = spend = 0;
        }
};

const int len = 1e3 + 115;
int n, x;
LL dp[len];
medical arr[len];

int main()
{
    //std::ios::sync_with_stdio(false);
    cin >> n >> x;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i].lost >> arr[i].win >> arr[i].spend;
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = x; j >= 0; -- j){
            if (arr[i].spend <= j){
                dp[j] = max(dp[j] + arr[i].lost, dp[j - arr[i].spend] + arr[i].win);
            }else{
                dp[j] += arr[i].lost;
            }
        }
    }
    cout << 5 * dp[x] << endl;
    return 0;
}