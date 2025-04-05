#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool>v;

int main()
{
    int n, q;
    cin >> n >> q;
    v = vector<bool>(n + 1, false);
    vector<int>Prime;
    for (int i = 2; i <= n; ++i)
    {
        if (!v[i]){
            Prime.push_back(i);
            for (int j = i * 2; j <= n; j += i)
            {
                v[j] = true;
            }
        }
    }
    while (q--)
    {
        int x;
        scanf("%d", &x);
        cout << Prime[x - 1] << endl;
    }
    return 0;
}