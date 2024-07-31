#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define debug(x) std::cerr << #x << " : " << x << std::endl

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

const int INFI = 0x7FFFFFFF;

vector<bool>num(100000, false);

int main()
{
    int res = 0, cnt = 0, maxn;
    cin >> maxn;
    for (int i = 2; res <= maxn && i < num.size(); ++ i)
    {
        if (!num[i]){
            res += i;
            if (res > maxn){
                break;
            }
            for (int j = i * 2; j < num.size(); j += i)
            {
                num[j] = true;
            }
            cnt++;
            
            cout << i << endl;
        }
    }
    cout << cnt << endl;
    return 0;
}