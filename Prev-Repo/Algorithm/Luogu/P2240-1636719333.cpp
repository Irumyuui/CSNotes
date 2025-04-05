#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Goods
{
    public:
        double w, v;
};

bool cmp(const Goods &a, const Goods &b)
{
    return a.v / a.w > b.v / b.w;
}

int main()
{
    int n, w;
    cin >> n >> w;
    vector<Goods>v(n);
    for (int i = 0; i < n; ++ i)
    {
        cin >> v[i].w >> v[i].v;
    }
    sort(v.begin(), v.end(), cmp);
    double res = 0;
    for (auto it : v)
    {
        if (it.w <= w){
            w -= it.w;
            res += it.v;
        }else{
            res += (it.v * (w / it.w));
            break;
        }
    }
    cout << fixed << setprecision(2) << res << endl;
    return 0;
}