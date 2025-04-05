#include <bits/stdc++.h>
using namespace std;

namespace EMIO {
	struct ENDL {
		//By ProtectEMmm
	}endl;
	class IStream {
	public:
		IStream &operator >> (int &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')
					flag = true;
				c = GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c = GetChar();
			}
			temp = flag ? -temp : temp;
			return *this;
		}
		IStream &operator >>(char &temp) {
			temp = ' '; char c = GetChar();
			while (!ischar(c))
				c = GetChar();
			temp = c; return *this;
		}
		IStream &operator >>(double &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')flag = true; c =
					GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c = GetChar();
			}
			if (c == '.') {
				c = GetChar();
				double point = 0.1;
				while (isdigit(c)) {
					temp += point * (c - '0');
					point *= 0.1; c = GetChar();
				}
			}
			temp = flag ? -temp : temp;
			return *this;
		}
		IStream &operator >>(long long &temp) {
			temp = 0; char c = GetChar(); bool flag = false;
			while (!isdigit(c)) {
				if (c == '-')flag = true; c =
					GetChar();
			}
			while (isdigit(c)) {
				temp = temp * 10 + c - '0', c =
					GetChar();
			}
			temp = flag ? -temp : temp; return *this;
		}
		IStream &operator >>(std::string &temp) {
			temp.clear(); char c = GetChar();
			while (!ischar(c))c = GetChar();
			while (ischar(c))temp += c, c = GetChar();
			return *this;
		}
	private:
		char BUF[1 << 20] = { 0 };
		char *POS = BUF, *END = BUF;
		inline char GetChar() {
			if (POS == END) {
				END = (POS = BUF) + fread(BUF, 1, 1 << 20, stdin);
			}
			return POS == END ? EOF : *POS++;
		}
		inline bool ischar(const char &c) {
			return c != ' ' && c != '\n';
		}
		inline bool isdigit(const char &c) {
			return '0' <= c && c <= '9';
		}
	} fin;

	class OStream {
	public:
		~OStream() {
			Flush();
		}
		inline void Flush() {
			fwrite(BUF, 1, POS - BUF, stdout); POS = BUF;
		}
		inline void SetPoint(int x) {
			point = x;
		}
		OStream &operator << (int temp) {
			int Top = 0; static int Stack[64];
			if (temp < 0) { PutChar('-'); temp = -temp; }
			do { Stack[Top++] = temp % 10; temp /= 10; } while (temp);
			while (Top) { PutChar(Stack[--Top] + '0'); } return *this;
		}
		OStream &operator << (char temp) {
			PutChar(temp); return *this;
		}
		OStream &operator << ([[maybe_unused]] ENDL temp) {
			PutChar('\n'); Flush(); return *this;
		}
		OStream &operator << (double temp) {
			if (temp < 0) {
				PutChar('-');
				temp = -temp;
			}
			long long integer = temp;
			*this << integer;
			temp -= integer;
			PutChar('.');
			for (int i = 1; i <= point; ++i) {
				temp *= 10;
				PutChar(int(temp) + '0');
				temp -= int(temp);
			}
			return *this;
		}
		OStream &operator << (long long temp) {
			int Top = 0; static int Stack[64];
			if (temp < 0) { PutChar('-'); temp = -temp; }
			do { Stack[Top++] = temp % 10; temp /= 10; } while (temp);
			while (Top) { PutChar(Stack[--Top] + '0'); } return *this;
		}
		OStream &operator <<(const std::string &temp) {
			for (auto c : temp)
			{
				PutChar(c);
			}
			return *this;
		}
		OStream &operator << (const char temp[]) {
			int p = 0;
			while (temp[p] != '\0') {
				PutChar(temp[p++]);
			}
			return *this;
		}
	private:
		int point = 6; char BUF[1 << 20] = { 0 };
		char *POS = BUF, *END = BUF + (1 << 20);
		inline void PutChar(char temp) {
			if (POS == END)
			{
				Flush();
			}
			*POS++ = temp;
		}
	} fout;
}
using EMIO::fin, EMIO::fout;

#define cin fin
#define cout fout

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = int64_t;

void Main() {
	int n;
	cin >> n;

	vector adj(n + 1, vector<tuple<int,int,int>>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		u ++; v ++;
		adj[u].emplace_back(v, w, i);
		adj[v].emplace_back(u, w, i);
	}

	vector<int> dep(n + 1, -1), fa(dep), top(dep), siz(dep), son(dep), dfn(dep), rnk(dep);
	vector<int> vw(n + 1), evid(n + 1);  // edge to v id
	[&](int root) -> void {
		auto dfs1 = [&](auto &&dfs, int from, int ew, int eid) -> void {
			evid[eid] = from;
			vw[from] = ew;
			son[from] = -1;
			siz[from] = 1;
			for (auto [to, ew, eid] : adj[from]) {
				if (dep[to] == -1) {
					dep[to] = dep[from] + 1;
					fa[to] = from;
					dfs(dfs, to, ew, eid);
					siz[from] += siz[to];
					if (son[from] == -1 || siz[to] > siz[son[from]])
						son[from] = to;
				}
			}
		};
		auto dfs2 = [&, stamp{0}](auto &&dfs, int from, int root) mutable -> void {
			top[from] = root;
			dfn[from] = ++ stamp;
			rnk[stamp] = from;
			if (son[from] == -1) {
				return;
			}
			dfs(dfs, son[from], root);
			for (auto [to, _, __] : adj[from]) {
				if (to != son[from] && to != fa[from]) {
					dfs(dfs, to, to);
				}
			}
		};
		dep[root] = 0;
		dfs1(dfs1, root, 0, 0);
		dfs2(dfs2, root, root);
	} (1);

	struct Info {
		int val, mx, mi;
		Info(int val = {}, int mx = -inf<int>, int mi = inf<int>)
			: val{val}, mx{mx}, mi{mi} {}
		Info operator + (const Info &x) const {
			return Info {
				val + x.val,
				max(mx, x.mx),
				min(mi, x.mi),
			};
		}
	};
	struct Node {
		Info val, rval;
		int rev;
	};
	vector<Node> seg((n + 1) * 4);
	
	auto rise = [&](int id) {
		seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
		seg[id].rval = seg[id * 2].rval + seg[id * 2 + 1].rval;
	};
	auto updatec = [&](int id, int d) {
		seg[id].val = {
			d, d, d,
		};
		seg[id].rval = {
			-d, -d, -d,
		};
	};
	auto updater = [&](int id) {
		swap(seg[id].val, seg[id].rval);
		seg[id].rev ^= 1;
	};

	auto down = [&](int id) {
		if (seg[id].rev) {
			updater(id * 2);
			updater(id * 2 + 1);
			seg[id].rev = 0;
		}
	};

	auto build = [&](auto &&self, int l, int r, int id) -> void {
		seg[id].rev = 0;
		if (l == r) {
			updatec(id, vw[rnk[l]]);
		} else {
			int mid = l + ((r - l) >> 1);
			self(self, l, mid, id * 2);
			self(self, mid + 1, r, id * 2 + 1);
			rise(id);
		}
	};

	auto change = [&](auto &&self, int l, int r, int id, int tag, int d) -> void {
		if (l == r) {
			updatec(id, d);
		} else {
			int mid = l + ((r - l) >> 1);
			down(id);
			if (tag <= mid) {
				self(self, l, mid, id * 2, tag, d);
			} else {
				self(self, mid + 1, r, id * 2 + 1, tag, d);
			}
			rise(id);
		}
	};

	auto modify = [&](auto &&self, int l, int r, int id, int ml, int mr) -> void {
		if (l == ml && r == mr) {
			updater(id);
		} else {
			int mid = l + ((r - l) >> 1);
			down(id);
			if (mr <= mid) {
				self(self, l, mid, id * 2, ml, mr);
			} else if (ml > mid) {
				self(self, mid + 1, r, id * 2 + 1, ml, mr);
			} else {
				self(self, l, mid, id * 2, ml, mid);
				self(self, mid + 1, r, id * 2 + 1, mid + 1, mr);
			}
			rise(id);
		}
	};

	auto query = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
		if (l == ql && r == qr) {
			return seg[id].val;
		} else {
			int mid = l + ((r - l) >> 1);
			down(id);
			if (qr <= mid) {
				return self(self, l, mid, id * 2, ql, qr);
			} else if (ql > mid) {
				return self(self, mid + 1, r, id * 2 + 1, ql, qr);
			} else {
				return self(self, l, mid, id * 2, ql, mid) + self(self, mid + 1, r, id * 2 + 1, mid + 1, qr);
			}
		}
	};

	auto Modify = [&](int a, int b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			modify(modify, 1, n, 1, dfn[top[a]], dfn[a]);
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		if (dep[a] < dep[b]) {
			modify(modify, 1, n, 1, dfn[a] + 1, dfn[b]);
		}
	};
	auto Query = [&](int a, int b) {
		Info ret;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			ret = ret + query(query, 1, n, 1, dfn[top[a]], dfn[a]);
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		if (dep[a] < dep[b]) {
			ret = ret + query(query, 1, n, 1, dfn[a] + 1, dfn[b]);
		}
		return ret;
	};

	build(build, 1, n, 1);

	int q;
	cin >> q;
	for (int _ = 1; _ <= q; _ ++) {
		string opt;
		cin >> opt;

		if (opt == "C") {
			int eid, w;
			cin >> eid >> w;
			change(change, 1, n, 1, dfn[evid[eid]], w);
		} else if (opt == "N") {
			int u, v;
			cin >> u >> v;
			u ++; v ++;
			Modify(u, v);
		} else if (opt == "SUM") {
			int u, v;
			cin >> u >> v;
			u ++; v ++;
			auto ret = Query(u, v);			
			cout << ret.val << '\n';
		} else if (opt == "MAX") {
			int u, v;
			cin >> u >> v;
			u ++; v ++;
			auto ret = Query(u, v);			
			cout << ret.mx << '\n';
		} else if (opt == "MIN") {
			int u, v;
			cin >> u >> v;
			u ++; v ++;
			auto ret = Query(u, v);			
			cout << ret.mi << '\n';
		}
	}
}

int main() {
	// std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}