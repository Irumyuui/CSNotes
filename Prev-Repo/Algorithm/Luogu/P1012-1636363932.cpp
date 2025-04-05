#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool cmp(const string &a, const string &b)
{
    return a + b > b + a;
}

int main()
{
    int n;
    cin >> n;
    getchar();
    vector<string>v;
    while (n --)
    {
        string s;
        cin >> s;
        v.push_back(s);
    }
    sort(v.begin(), v.end(), cmp);
    for (auto it : v)
        cout << it;
    return 0;
}