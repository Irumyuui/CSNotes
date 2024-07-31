#include <iostream>
#include <string>
using namespace std;

const int LEN = 105;

typedef pair<int, int> PII;

int n, m;
char g[LEN][LEN];
int res[LEN][LEN];

PII togo[] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};

bool error(const PII &p){
    if (!(p.first >= 0 && p.first < n)){
        return true;
    }else if (!(p.second >= 0 && p.second < m)){
        return true;
    }
    return false;
}

void serch(){
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            if (g[i][j] == '*'){
                res[i][j] = -1;
                continue;
            }
            int maxe = 0, cnt = 0;
            for (auto it : togo){
                PII p = {i + it.first, j + it.second};
                if (!error(p)){
                    //maxe = max(res[p.first][p.second], maxe);
                    if (g[p.first][p.second] == '*'){
                        cnt ++;
                    }
                }
            }
            res[i][j] = cnt;
        }
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; ++ i){
        cin >> g[i];
    }
    serch();
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            if (res[i][j] == -1){
                cout << '*';
            }else{
                cout << res[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}