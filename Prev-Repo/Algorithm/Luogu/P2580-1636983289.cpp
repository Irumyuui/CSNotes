#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

class Trie
{
    public:
        Trie *nex[26];
        int vis;
        Trie()
        {
            for (int i = 0; i < 26; ++ i)
                this->nex[i] = nullptr;
            this->vis = 0;
        }
};

Trie treeRoot;

void Insert(const string &str)
{
    Trie *p = &treeRoot;
    for (int i = 0; i < str.size(); ++ i)
    {
        if (p->nex[str[i] - 'a'] == nullptr){
            p->nex[str[i] - 'a'] = new Trie;
        }
        p = p->nex[str[i] - 'a'];
    }
}

const char* Serch(const string &str)
{
    Trie *p = &treeRoot;
    for (int i = 0; i < str.size(); ++ i)
    {
        if (p->nex[str[i] - 'a'] == nullptr){
            return "WRONG";
        }
        p = p->nex[str[i] - 'a'];
        p->vis ++;
    }
    if (p->vis == 1){
        return "OK";
    }else{
        return "REPEAT";
    }
}

void solve()
{
    int n;
    cin >> n;
    string name;
    while (n --)
    {
        cin >> name;
        Insert(name);
    }
    cin >> n;
    while (n --)
    {
        cin >> name;
        cout << Serch(name) << endl;
    }
}

int main()
{
    solve();
    return 0;
}