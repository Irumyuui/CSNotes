#include <iostream>
#include <vector>

using namespace std;

class Node{
    public:
    int maxi, mini, sump;
    Node()
    {
        this->Clear();
    }
    void Clear()
    {
        this->maxi = -1;
        this->mini = 0x7FFFFFFF;
        this->sump = 0;
    }
    void Add(const int &x)
    {
        this->mini = min(this->mini, x);
        this->maxi = max(this->maxi, x);
        this->sump += x;
    }
};

int main()
{
    int cnt, m;
    cin >> cnt >> m;
    Node res;
    while (cnt--)
    {
        Node p;
        for (int i = 0; i < m; ++i)
        {
            int x;
            cin >> x;
            p.Add(x);
        }
        res.Add(p.sump - p.maxi - p.mini);
    }
    printf("%.2lf\n", res.maxi * 1.0 / (m - 2));
    return 0;
}