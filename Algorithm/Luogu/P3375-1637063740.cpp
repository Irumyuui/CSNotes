#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

void KMP(const string &text, const string &patten)
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
    for (int i = 0, k = -1; i < text.size(); ++ i)
    {
        while (k > -1 && patten[k + 1] != text[i])
            k = nex[k];
        if (patten[k + 1] == text[i])
            k ++;
        if (k == patten.size() - 1){
            cout << i - k + 1 << endl;
            k = nex[k];
        }
    }
    for (auto it : nex)
    {
        cout << it + 1 << ' ';
    }
}

void solve()
{
    string text, patten;
    cin >> text >> patten;
    KMP(text, patten);
    return;
}

int main()
{
    FAST();
    solve();    
    return 0;
}