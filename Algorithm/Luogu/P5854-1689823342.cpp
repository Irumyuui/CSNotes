#include <bits/stdc++.h>

struct Fread {
	char *p1, *p2, buf[100000];
	constexpr char nextchar() noexcept {
		return (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++);
	}
	template <class T> constexpr void read(T &val) noexcept {
		val = 0;
		int f = 1;
		char ch = nextchar();
		while (ch < 48 || ch > 57) {
			if (ch == '-') {
				f = -1;
			}
			ch = nextchar();
		}
		while (ch >= 48 && ch <= 57) {
			val = val * 10 + ch - 48, ch = nextchar();
		}
		val *= f;
	}
	template <class T> constexpr Fread& operator >> (T &val) noexcept {
		this->read(val);
		return *this;
	}
} fin;

struct Fwrite {
	template <class T> constexpr void write(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
	constexpr void write(char x) { putchar(x); }
	constexpr void write(const char *x) { puts(x); }
	// constexpr void write(const std::string &str) { puts(str.c_str()); }
	template <class T> constexpr Fwrite& operator << (const T &x) {
		this->write(x);
		return *this;
	}
} fout;

using i64 = int64_t;

struct CartesianTree {
    struct Node {
        std::pair<int,int> val;
        int lc, rc;
        Node(const std::pair<int,int> &o = {}, int lc = -1, int rc = -1) : val{o}, lc{lc}, rc{rc} {}
    };
    std::vector<Node> tr;
    int root;
    
    void Build() {
        // std::ranges::stable_sort(tr, [](const auto &a, const auto &b) {
        //     return a.val.first < b.val.first;
        // });
        std::vector<int> stk(tr.size());
        int top = 0;
        for (int i = 0; i < tr.size(); i ++) {
            int k = top - 1;
            while (k >= 0 && tr[i].val.second <= tr[stk[k]].val.second)
                -- k;
            if (k >= 0)
                tr[stk[k]].rc = i;
            if (k + 1 < top) 
                tr[i].lc = stk[k + 1];
            stk[++ k] = i;
            top = k + 1;
        }
        root = stk[0];
    }

    auto& operator [] (int idx) {
        return tr[idx];
    }
    const auto& operator [] (int idx) const {
        return tr[idx];
    }

    CartesianTree() = default;
    explicit CartesianTree(int size) : tr(size), root(-1) {};
};

void Main() {
    int n;
    // std::cin >> n;
    fin >> n;
    std::vector<int> w(n);
    for (auto &x : w)
        fin >> x;
        // std::cin >> x;

    CartesianTree ctr(n);
    for (int i = 0; i < n; i ++) {
        ctr[i].val = {i, w[i]};
    }
    ctr.Build();

    i64 lc = 0, rc = 0;
    for (i64 i = 0; i < n; i ++) {
        lc ^= (i + 1) * (ctr[i].lc + 2);
        rc ^= (i + 1) * (ctr[i].rc + 2);
    }
    
    // std::cout << lc << ' ' << rc << '\n';
    fout << lc << ' ' << rc << '\n';
}

int main() {
    // std::cin.tie(nullptr)->sync_with_stdio(false);
    Main();
}