#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

struct Node{
    LL size, cnt, rank;
    LL val;
    Node *child[2];
    #define lc child[0]
    #define rc child[1]
    void update(){
        size = cnt + (lc == nullptr ? 0 : lc->size) + (rc == nullptr ? 0 : rc->size);
    }
};

inline void rotate(Node *&o, int d){
    Node *k = o->child[d ^ 1];
    o->child[d ^ 1] = k->child[d];
    k->child[d] = o;
    o->update(); k->update();
    o = k;
}

void Insert(Node *&o, LL x){
    if (o == nullptr){
        o = new Node();
        o->val = x;
        o->lc = o->rc = nullptr;
        o->cnt = o->size = 1;
        o->rank = rand();
        return;
    }
    if (o->val == x){
        o->cnt ++;
    }else{
        int d = x < o->val ? 0 : 1;
        Insert(o->child[d], x);
        if (o->child[d]->rank > o->rank){
            rotate(o, d ^ 1);
        }
    }
    o->update();
}

void Delete(Node *&o, int x){
    if (o == nullptr){
        return;
    }
    if (o->val == x){
        if (o->cnt > 1){
            o->cnt --;
            o->update();
            return;
        }else{
            if (o->lc == nullptr && o->rc == nullptr){
                delete o;
                o = nullptr;
                return;
            }else if (o->lc != nullptr && o->rc != nullptr){
                int d = o->lc->rank > o->rc->rank ? 0 : 1;
                rotate(o, d ^ 1);
                Delete(o->child[d ^ 1], x);
            }else{
                Node *k = o->lc == nullptr ? o->rc : o->lc;
                delete o;
                o = k;
            }
        }
    }else{
        if (x < o->val)
            Delete(o->lc, x);
        else
            Delete(o->rc, x);
    }
    o->update();
}

// 查询整数 x 的排名
int query_xs_rank(Node *o, LL x){
    if (o == nullptr){
        return 1;
    }
    if (o->val == x){
        return (o->lc == nullptr ? 0 : o->lc->size) + 1;
    }else{
        if (x < o->val)
            return query_xs_rank(o->lc, x);
        else
            return (o->lc == nullptr ? 0 : o->lc->size) + o->cnt + query_xs_rank(o->rc, x);
    }
}

// 查询排名为 xx 的数（如果不存在，则认为是排名小于 xx 的最大数。保证 xx 不会超过当前数据结构中数的总数）
LL query_krank_x(Node *o, int rank){
    if (o == nullptr)
        return 1;
    int sl = o->lc == nullptr ? 0 : o->lc->size;
    if (sl >= rank){
        return query_krank_x(o->lc, rank);
    }else if (sl + o->cnt < rank){
        return query_krank_x(o->rc, rank - sl - o->cnt);
    }else{
        return o->val;
    }
}

// 求 x 的前驱（前驱定义为小于 x，且最大的数）。
void query_xs_prex(Node *o, LL x, LL &res){
    if (o == nullptr)
        return;
    if (o->val < x){
        res = o->val;
        query_xs_prex(o->rc, x, res);
    }else{
        query_xs_prex(o->lc, x, res);
    }
}

// 求 xx 的后继（后继定义为大于 xx，且最小的数）。
void query_xs_nextx(Node *o, LL x, LL &res){
    if (o == nullptr)
        return;
    if (o->val > x){
        res = o->val;
        query_xs_nextx(o->lc, x, res);
    }else{
        query_xs_nextx(o->rc, x, res);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    Node *treap = nullptr;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i){
        LL x;
        cin >> x;
        Insert(treap, x);
    }
    LL ans = 0, last = 0;
    while (m --){
        LL opt, x;
        cin >> opt >> x;
        x ^= last;
        if (opt == 1){
            Insert(treap, x);
        }else if (opt == 2){
            Delete(treap, x);
        }else if (opt == 3){
            last = query_xs_rank(treap, x);
            ans ^= last;
        }else if (opt == 4){
            last = query_krank_x(treap, x);
            ans ^= last;
        }else if (opt == 5){
            query_xs_prex(treap, x, last);
            ans ^= last;
        }else{
            query_xs_nextx(treap, x, last);
            ans ^= last;
        }
    }
    cout << ans << '\n';
    return 0;
}