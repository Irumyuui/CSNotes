#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

deque<int>minans, maxans;

void printMin(const vector<int>&v, const int &k)
{
    int ll = 0, rr = 1;
    // minans.push_back(1);
    while (rr <= k)
    {
        while (minans.size() && v[minans.back()] > v[rr])
        {
            minans.pop_back();
        }
        minans.push_back(rr);
        rr ++;
    }
    cout << v[minans.front()] << ' ';
    while (ll <= rr && rr < v.size())
    {
        ll ++;
        while (minans.size() && v[minans.back()] > v[rr])
        {
            minans.pop_back();
        }
        minans.push_back(rr);
        while (minans.front() <= ll){
            minans.pop_front();
        }
        cout << v[minans.front()] << ' ';
        rr ++;
    }
    cout << endl;
}

void printMax(const vector<int> &v, const int &k)
{
    int ll = 0, rr = 1;
    while (rr <= k)
    {
        while (maxans.size() && v[maxans.front()] < v[rr])
        {
            maxans.pop_front();
        }
        maxans.push_front(rr);
        rr ++;
    }
    cout << v[maxans.back()] << ' ';
    while (ll <= rr && rr < v.size())
    {
        ll ++;
        while (maxans.size() && v[maxans.front()] < v[rr])
        {
            maxans.pop_front();
        }
        maxans.push_front(rr);
        while (maxans.back() <= ll)
        {
            maxans.pop_back();
        }
        cout << v[maxans.back()] << ' ';
        rr ++;
    }
    cout << endl;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>v(n + 1, 0);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> v[i];
    }
    printMin(v, k);
    printMax(v, k);
}

int main()
{
    // FAST();
    solve();
    return 0;
}