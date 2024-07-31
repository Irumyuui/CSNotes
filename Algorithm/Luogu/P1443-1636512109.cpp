#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

const int INF = 0x7fffffff;
int nx[401], ny[401];
int xl, yl;
int place[][2] = {
    {-2, 1},
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
};
vector<vector<int>>arr(401, vector<int>(401, INF));

void bfs(int x, int y)
{
    queue<pair<int, int>>q;
    arr[x][y] = 0;
    q.push({x, y});
    while (q.size())
    {
        int vx = q.front().first;
        int vy = q.front().second;
        q.pop();
        for (int i = 0; i < 8; ++ i)
        {
            int x1 = vx + place[i][0];
            int y1 = vy + place[i][1];
            if (x1 > 0 && x1 <= xl
            && y1 > 0 && y1 <= yl
            && arr[x1][y1] == INF){
                arr[x1][y1] = min(arr[x1][y1], arr[vx][vy] + 1);
                q.push({x1, y1});
            }
        }
    }
}

int main()
{
    int x, y;
    cin >> xl >> yl >> x >> y;
    bfs(x, y);
    for (int i = 1; i <= xl; ++ i)
    {
        for (int j = 1; j <= yl; ++ j)
        {
            if (arr[i][j] == INF){
                printf("%-5d", -1);
            }else{
                printf("%-5d", arr[i][j]);
            }
        }
        cout << endl;
    }
    return 0;
}