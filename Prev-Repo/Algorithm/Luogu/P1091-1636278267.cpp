#include <iostream>
#include <vector>

using namespace std;

const int N = 101;
vector<int>rise(N, 1);
vector<int>decline(N, 1);

int main()
{
    int n;
    cin >> n;
    vector<int>team(n + 1);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> team[i];
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = i; j >= 1; -- j)
        {
            if (team[i] > team[j]){
                rise[i] = max(rise[j] + 1, rise[i]);
            }
        }
    }
    for (int i = n; i >= 1; -- i)
    {
        for (int j = i; j <= n; ++ j)
        {
            if (team[i] > team[j]){
                decline[i] = max(decline[i], decline[j] + 1);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++ i)
    {
        res = max(rise[i] + decline[i], res);
    }
    cout << n - res + 1;
    return 0;
}
