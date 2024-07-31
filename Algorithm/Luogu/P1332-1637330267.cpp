#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

PII dulr[] = {
    {1, 0},
    {0, -1},
    {0, 1},
    {-1, 0},
};

int n, m;
vector<vector<int>>g;
queue<PII>q;
vector<PII>king;

bool isRight(const PII &it){
    if (it.first < 0 || it.first > n)
        return false;
    if (it.second < 0 || it.second > m)
        return false;
    return true;
}

void BFS(){
    while (!q.empty()){
        PII p = q.front();
        q.pop();
        for (auto it : dulr){
            PII i = {p.first + it.first, p.second + it.second};
            if (isRight(i)){
                if (g[i.first][i.second] == INFI)
                    q.push(i);
                g[i.first][i.second] = min(g[p.first][p.second] + 1, g[i.first][i.second]);
            }
        }
    }
    return;
}

void solve(){
    int a, b;
    cin >> n >> m >> a >> b;
    g = vector<vector<int>>(n + 1, vector<int>(m + 1, INFI));
    while (a --){
        int x, y;
        cin >> x >> y;
        q.push({x, y});
        g[x][y] = 0;
    }
    while (b --){
        int x, y;
        cin >> x >> y;
        king.push_back({x, y});
    }
    BFS();
    for (auto it : king){
        cout << g[it.first][it.second] << endl;
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}