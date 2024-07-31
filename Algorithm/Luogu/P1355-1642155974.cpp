#include <bits/stdc++.h>

using namespace std;


struct point
{
    long double x, y;
    bool operator==(const point &x) const
    {
        return this->x == x.x && this->y == x.y;
    }
};

long double edge(point &a, point &b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

double area(point a, point b, point c)
{
    long double p = edge(a, b) + edge(a, c) + edge(b, c);
    p /= 2;
    return sqrtl(p * (p - edge(a, b)) * (p - edge(a, c)) * (p - edge(b, c)));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    point a, b, c, d;
    char ch;
    cin >> ch >> a.x >> ch >> a.y >> ch;
    cin >> ch >> b.x >> ch >> b.y >> ch;
    cin >> ch >> c.x >> ch >> c.y >> ch;
    cin >> ch >> d.x >> ch >> d.y >> ch;
    if (a == d || b == d || c == d){
        cout << 4;
        return 0;
    }
    long double s1, s2, s3, s;
    s = area(a, b, c);
    s1 = area(a, b, d);
    s2 = area(a, c, d);
    s3 = area(b, c, d);
    if (s1 + s2 + s3 > s){
        cout << 2;
    }else{
        if (s1 == 0 || s2 == 0 || s3 == 0){
            cout << 3;
        }else{
            cout << 1;
        }
    }
    return 0;
}