#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
const int INF = 0x7FFFFFFF;

int main()
{
    int maxsize, cnt;
    cin >> maxsize >> cnt;
    vector<int>v(cnt);
    for (auto &it : v)
    {
        cin >> it;
    }
    sort(v.begin(), v.end());
    int res = 0, sum = 0;
    for (vector<int>::iterator it1 = v.begin(), it2 = v.end() - 1;
    it1 != v.end() && it2 != v.begin() - 1 && it1 <= it2;)
    {
        if (*it1 + *it2 <= maxsize){
            it1++, it2--;
            res++;
        }else{
            it2--;
            res++;
        }
    }
    cout << res;
    return 0;
}