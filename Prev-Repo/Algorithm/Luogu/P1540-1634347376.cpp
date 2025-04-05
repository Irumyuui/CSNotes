#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int maxsize, n;
    cin >> maxsize >> n;
    int cnt = 0;
    deque<int>q;
    while (n--)
    {
        int x;
        cin >> x;
        if (find(q.begin(), q.end(), x) == q.end()){
            if (q.size() == maxsize){
                q.pop_front();
            }
            q.push_back(x);
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}