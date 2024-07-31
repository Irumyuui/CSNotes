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

int number;
vector<int>Primer;
vector<bool>num(202, false);
vector<int>numb(201, 0);

int main()
{
    for (int i = 2; i < num.size(); ++ i)
    {
        if (!num[i])
        {
            Primer.push_back(i);
            for (int j = i * 2; j < num.size(); j += i)
            {
                num[j] = true;
            }
        }
    }
    numb[0] = 1;
    for (auto it : Primer)
    {
        for (int j = it; j < numb.size(); ++ j)
        {
            numb[j] += numb[j - it];
        }
    }
    while (cin >> number)
    {
        cout << numb[number] << endl;
    }
    return 0;
}