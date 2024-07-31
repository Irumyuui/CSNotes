#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define debug(x) std::cerr << #x << " : " << x << std::endl

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

const int INFI = 0x7FFFFFFF;

vector<bool>choose;
vector<LL>prime;
vector<LL>res;

int main()
{
    int n;
    cin >> n;
    choose = vector<bool>(n + 1, false);
    for (int i = 2; i <= n; ++ i)
    {
        if (!choose[i]){
            for (int j = i << 1; j <= n; j += i)
            {
                choose[j] = true;
            }
            prime.push_back(i);
        }
    }
    res = vector<LL>(n + 1, 0);
    res[0] = 1;
    for (auto it : prime)
    {
        for (int i = it; i <= n; ++ i)
        {
            res[i] += res[i - it];
        }
    }
    cout << res[n];
    return 0;
}