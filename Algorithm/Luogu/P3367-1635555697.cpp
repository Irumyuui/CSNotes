#include <iostream>
#include <vector>

using namespace std;

vector<int>dad;

int FindDad(int child)
{
    if (dad[child] != child){
        dad[child] = FindDad(dad[child]);
    }
    return dad[child];
}

void Union(int a, int b)
{
    a = FindDad(a);
    b = FindDad(b);
    dad[a] = b;
}

int main()
{
    int n, m;
    cin >> n >> m;
    dad = vector<int>(n + 1);
    for (int i = 0; i <= n; ++i)
    {
        dad[i] = i;
    }
    while (m--)
    {
        int com, a, b;
        cin >> com >> a >> b;
        if (com == 1){
            Union(a, b);
        }else{
            if (FindDad(a) == FindDad(b)){
                cout << "Y" << endl;
            }else{
                cout << "N" << endl;
            }
        }
    }
    return 0;
}