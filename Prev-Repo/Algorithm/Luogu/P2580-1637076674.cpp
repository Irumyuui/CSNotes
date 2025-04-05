#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

namespace TrieT
{
    struct TrieNode
    {
        TrieNode *nex[26];
        int cnt;
        TrieNode()
        {
            cnt = 0;
            for (auto &it : this->nex)
                it = nullptr;    
        }
        ~TrieNode()
        {
            for (auto &it : this->nex)
                delete it;
        }
    };
    class Trie
    {
        public:
            TrieNode root;
            void Insert(const string &str)
            {
                TrieNode *p = &(this->root);
                for (auto it : str)
                {
                    if (p->nex[it - 'a'] == nullptr)
                        p->nex[it - 'a'] = new TrieNode; 
                    p = p->nex[it - 'a'];
                }
            }
            const char *Serch(const string &str)
            {
                TrieNode *p = &(this->root);
                for (auto it : str)
                {
                    if (p->nex[it - 'a'] == nullptr)
                        return "WRONG";
                    else
                        p = p->nex[it - 'a'];
                        p->cnt ++;
                }
                if (p->cnt != 1)
                    return "REPEAT";
                else
                    return "OK";
            }
    };
}

using namespace TrieT;

void solve()
{
    int n;
    cin >> n;
    getchar();
    string str;
    Trie tree;
    while (n --)
    {
        cin >> str;
        tree.Insert(str);
    }
    cin >> n;
    getchar();
    while (n --)
    {
        cin >> str;
        cout << tree.Serch(str) << endl;
    }
    return;
}

int main()
{
    solve();
    return 0;
}