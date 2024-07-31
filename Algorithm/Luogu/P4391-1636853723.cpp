#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

int solve(const string &patten)
{
    vector<int>nex(patten.size(), 0);
    int k = nex[0] = -1;
    for (int i = 1; i < patten.size(); ++ i)
    {
        while (k > -1 && patten[k + 1] != patten[i])
            k = nex[k];
        if (patten[k + 1] == patten[i])
            k ++;
        nex[i] = k;
    }
    return patten.size() - 1 - nex[patten.size() - 1];
}

int main()
{
    int n;
    string patten;
    cin >> n >> patten;
    cout << solve(patten);
    return 0;
}