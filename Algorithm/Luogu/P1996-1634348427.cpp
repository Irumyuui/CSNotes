#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int>v(n);
    for (int i = 0; i < n; ++i)
    {
        v[i] = i + 1;
    }
    int cnt = 1, i = 0, space = 0;
    while (!v.empty())
    {
        if (i == v.size()){
            i = 0;
        }
        if (cnt == m){
            if (space == 1){
                cout << " ";
            }else{
                space = 1;
            }
            cout << v[i];
            v.erase(v.begin() + i);
            cnt = 1;
            continue;
        }
        i++;
        cnt++;
    }
    return 0;
}