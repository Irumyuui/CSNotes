#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

#define lc child[0]
#define rc child[1]

struct Node{
    int rank, size, cnt, val;
    Node *child[2];
    void update(){
        size = cnt;
        if (lc != nullptr) size += lc->size;
        if (rc != nullptr) size += rc->size;
    }
};

// directiron 0 左旋，与右孩子交换  1 右旋 与左孩子交换
void rotate(Node *&o, int d){
    Node *c = o->child[d ^ 1];
    o->child[d ^ 1] = c->child[d];
    c->child[d] = o;
    o->update(); c->update();
    o = c;
}

// 插入
void insert(Node *&o, int x){
    if (o == nullptr){
        o = new Node();
        o->rank = rand();
        o->lc = o->rc = nullptr;
        o->val = x;
        o->size = o->cnt = 1;
        return;
    }
    if (o->val == x){
        o->cnt ++;
    }else{
        int d = x < o->val ? 0 : 1;
        insert(o->child[d], x);
        if (o->rank < o->child[d]->rank){
            rotate(o, d ^ 1);
        }
    }
    o->update();
}

// 删除
void del(Node *&o, int x){
    if (o == nullptr)
        return;
    if (o->val == x){
        if (o->cnt > 1){
            o->cnt --;
            o->update();
            return;
        }else if (o->lc == nullptr && o->rc == nullptr){
            delete o;
            o = nullptr;
            return;
        }else{
            if (o->lc != nullptr && o->rc != nullptr){
                int d = o->lc->rank > o->rc->rank ? 0 : 1;
                rotate(o, d ^ 1);
                del(o->child[d ^ 1], x);
            }else if (o->lc != nullptr){
                Node *k = o->lc;
                delete o;
                o = k;
            }else{
                Node *k = o->rc;
                delete o;
                o = k;
            }
        }
    }else{
        if (x < o->val)
            del(o->lc, x);
        else
            del(o->rc, x);
    }
    o->update();
}

// 查询x的排名
// int queryxkth(Node *&o, int x){
//     if (o == nullptr)
//         return 1;
//     if (x > o->val)
//         return (o->lc == nullptr ? 1 : o->lc->size + 1) +  queryxkth(o->rc, x);
//     else
//         return  queryxkth(o->lc, x);
// }
int queryxkth(Node *&o, int x){
    if (o == nullptr)
        return 0;
    if (o->val == x)
        return (o->lc == nullptr ? 0 : o->lc->size) + 1;
    if (o->val > x)
        return queryxkth(o->lc, x);
    return (o->lc == nullptr ? 0 : o->lc->size) + o->cnt + queryxkth(o->rc, x);
}


// 查询第k小的数
int queryth(Node *&o, int kth){
    if (o == nullptr || kth <= 0 || kth > o->size)
        return -1;
    int sl = o->lc == nullptr ? 0 : o->lc->size;
    if (sl >= kth)
        return queryth(o->lc, kth);
    else if (kth <= sl + o->cnt)
        return o->val;
    else
        return queryth(o->rc, kth - sl - o->cnt);
}

// 查询前驱
void queryprex(Node *&o, int x, int &res){
    if (o == nullptr)
        return;
    if (o->val < x){
        res = o->val;
        queryprex(o->rc, x, res);
    }else{
        queryprex(o->lc, x, res);
    }
}

// 查询后驱
void querynext(Node *&o, int x, int &res){
    if (o == nullptr)
        return;
    if (o->val > x){
        res = o->val;
        querynext(o->lc, x, res);
    }else{
        querynext(o->rc, x, res);
    }
}

#undef lc
#undef rc

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    Node *root = nullptr;
    while (t --){
        int opt, x, res;
        cin >> opt >> x;
        switch (opt){
            case 1:
                insert(root, x);
                break;
            case 2:
                del(root, x);
                break;
            case 3:
                cout << queryxkth(root, x) << '\n';
                break;
            case 4:
                cout << queryth(root, x) << '\n';
                break;
            case 5:
                queryprex(root, x, res);
                cout << res << '\n';
                break;
            case 6:
                querynext(root, x, res);
                cout << res << '\n';
                break;
        }
    }
    return 0;
}