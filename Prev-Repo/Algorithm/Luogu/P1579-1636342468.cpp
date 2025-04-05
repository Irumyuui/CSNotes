#include <iostream>
#include <vector>

using namespace std;

vector<bool>vis;
vector<int>prime;
vector<int>res;

int n;
void dfs(int sum)
{
    if (res.size() == 3 && sum != n){
        res.pop_back();
        return;
    }else if (res.size() == 3 && sum == n){
        return;
    }
    for (int i = 0; i < prime.size(); ++ i)
    {
        if (sum + prime[i] <= n){
            res.push_back(prime[i]);
            dfs(sum + prime[i]);
            if (res.size() == 3){
                return;
            }
        }
    }
    res.pop_back();
}

int main()
{
    cin >> n;
    vis = vector<bool>(n + 1, false);
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]){
            prime.push_back(i);
        }
        for (int j = 0; prime[j] <= n / i; ++ j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0){
                break;
            }
        }
    }
    dfs(0);
    for (auto it : res)
    {
        cout << it << " ";
    }
    return 0;
}