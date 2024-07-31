#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

#define debug(x) std::cerr << #x << " : " << x << std::endl

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

const int INFI = 0x7FFFFFFF;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cout << i << " ";
    }
    for (int i = 1; i <= n; i += 2)
    {
        cout << i << " ";
    }
    for (int i = 2; i <= n; i += 2)
    {
        cout << i << " ";
    }
    return 0;
}