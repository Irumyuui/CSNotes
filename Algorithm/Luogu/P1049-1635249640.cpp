#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int>thing;

int box, maxt = 0;
void findless(int v, int sum)
{
    // if (sum > box){
    //     return;
    // }
    for (int i = v + 1; i < thing.size(); ++i)
    {
        if (sum + thing[i] <= box){
            findless(i, sum + thing[i]);
        }
    }
    maxt = max(maxt, sum);
}

int main()
{
    cin >> box;
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        thing.push_back(x);
    }
    //sort(thing.begin(), thing.end());
    findless(-1, 0);
    cout << box - maxt << endl;
    return 0;
}