#include <bits/stdc++.h>

using Node = int;

constexpr int MAXN = 1e6 + 10;

Node child[MAXN][2];
int rank[MAXN], cnt[MAXN], siz[MAXN], val[MAXN];
int tot = 0;

inline Node Newnode(int v) {
    ++ tot;

    int self = tot;
    child[self][0] = child[self][1] = 0;
    siz[self] = cnt[self] = 1;
    val[self] = v;
    rank[self] = rand();

    return self;
}

inline void update(Node &self) {
    siz[self] = cnt[self] + siz[child[self][0]] + siz[child[self][1]];
}

inline void Rotate(Node &self, int d) {
    Node nex = child[self][d ^ 1];
    child[self][d ^ 1] = child[nex][d];
    child[nex][d] = self;
    
    update(self);
    update(nex);
    
    self = nex;
}

void Insert(Node &self, int x) {
    if (self == 0) {
        self = Newnode(x);
        return;
    }

    if (val[self] == x){
        cnt[self] ++;
    } else {
        int d = x < val[self] ? 0 : 1;

        Insert(child[self][d], x);

        if (rank[self] < rank[child[self][d]]) {
            Rotate(self, d ^ 1);
        }
    }

    update(self);
}

void Delete(Node &self, int x) {
    if (self == 0) {
        return;
    }

    if (val[self] == x) {
        if (cnt[self] > 1) {
            cnt[self] --;
        } else if (child[self][0] || child[self][1]) {
            if (!child[self][1] || rank[child[self][0]] > rank[child[self][1]]) {
                Rotate(self, 1);
                Delete(child[self][1], x);
            } else {
                Rotate(self, 0);
                Delete(child[self][0], x);
            }
        } else {
            self = 0;
            return;
        }
    } else {
        if (x < val[self]) {
            Delete(child[self][0], x);
        } else {
            Delete(child[self][1], x);
        }
    }

    update(self);
}

//查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
int query_x_s_kth(Node &self, int x) {
    if (self == 0) {
        return -1;
    }
    if (val[self] == x) {
        return siz[child[self][0]] + 1;
    } else if (x < val[self]) {
        return query_x_s_kth(child[self][0], x);
    } else {
        return siz[child[self][0]] + cnt[self] + query_x_s_kth(child[self][1], x);
    }
}

//查询排名为 x 的数
int query_xth_num(Node &self, int kth) {
    if (self == 0) {
        return 0;
    }
    if (siz[child[self][0]] >= kth) {
        return query_xth_num(child[self][0], kth);
    } else if (kth <= siz[child[self][0]] + cnt[self]) {
        return val[self];
    } else {
        return query_xth_num(child[self][1], kth - siz[child[self][0]] - cnt[self]);
    }
}

//求 x 的前驱

void query_x_pre(Node &self, int &res, int x) {
    if (self == 0) {
        return;
    }
    if (val[self] < x) {
        res = val[self];
        query_x_pre(child[self][1], res, x);
    } else {
        query_x_pre(child[self][0], res, x);  
    }
}

void query_x_nex(Node &self, int &res, int x) {
    if (self == 0) {
        return;
    }
    if (val[self] > x) {
        res = val[self];
        query_x_nex(child[self][0], res, x);
    } else {
        query_x_nex(child[self][1], res, x);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    Node root = 0;

    while (t --) {
        int c, x;
        std::cin >> c >> x;

        if (c == 1) {
            Insert(root, x);
        } else if (c == 2) {
            Delete(root, x);
        } else if (c == 3) {
            std::cout << query_x_s_kth(root, x) << '\n';
        } else if (c == 4) {
            std::cout << query_xth_num(root, x) << '\n';
        } else if (c == 5) {
            int res;
            query_x_pre(root, res, x);
            std::cout << res << '\n';
        } else {
            int res;
            query_x_nex(root, res, x);
            std::cout << res << '\n';
        }
    }

    return 0;
}