#include <iostream>
#include <vector>

using namespace std;

vector<int>dad;

int FindDad(int v)
{
    if (dad[v] != v){
        dad[v] = FindDad(dad[v]);
    }
    return dad[v];
}

void UnionDad(int a, int b)
{
    a = FindDad(a);
    b = FindDad(b);
    dad[a] = b;
}

int main()
{
    cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    dad = vector<int>(n + 1);
    for (int i = 0; i <= n; ++ i)
    {
        dad[i] = i;
    }
    while (m --)
    {
        int a, b;
        cin >> a >> b;
        UnionDad(a, b);
    }
    while (p --)
    {
        int a, b;
        cin >> a >> b;
        if (FindDad(a) == FindDad(b)){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}