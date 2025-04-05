#include <iostream>
#include <vector>

using namespace std;

const int N = 1e6 + 1;

vector<int>A(N, -1);
vector<int>B(N, -1);

int FindDad(vector<int> &dad, int v)
{
    if (dad[v] > 0){
        return dad[v] = FindDad(dad, dad[v]);
    }
    return v;
}

void Union(vector<int> &dad, int a, int b)
{
    a = FindDad(dad, a);
    b = FindDad(dad, b);
    if (a == b){
        return;
    }
    dad[a] += dad[b];
    dad[b] = a;
}

int main()
{
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    while (p --)
    {
        int a, b;
        cin >> a >> b;
        Union(A, a, b);
    }
    while (q --)
    {
        int a, b;
        cin >> a >> b;
        Union(B, -a, -b);
    }
    int ac = FindDad(A, 1);
    int bc = FindDad(B, 1);
    cout << -max(A[ac], B[bc]);
    return 0;
}