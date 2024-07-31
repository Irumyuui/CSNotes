#include <cstdint>
#include <iostream>
#include <array>
#include <string>
#include <numeric>

using std::cin, std::cout, std::array, std::string;

namespace RoyalGuard::Integer {
#if __cplusplus >= 202002L
    template <int _P> requires (_P >= 1)
#else
    template <int _P, std::enable_if<(_P >= 1)>* = nullptr>
#endif
    struct ModInt32 {
        using i64 = std::int64_t;
        static constexpr int P = _P;
        int v;
        ModInt32() : v(0) {}
        ModInt32(i64 _v) { v = _v % P; if (v < 0)v += P; }
        explicit operator int() const { return v; }
        explicit operator long long() const { return v; }
        explicit operator bool() const { return v > 0; }
        bool operator == (const ModInt32 &o) const { return v == o.v; }
        bool operator != (const ModInt32 &o) const { return v != o.v; }
        ModInt32 operator - () const { return ModInt32(v ? P - v : 0); }
        ModInt32 operator + () const { return *this; }
        ModInt32 & operator ++ () { v++; if (v == P)v = 0; return *this; }
        ModInt32 & operator -- () { if (v == 0)v = P; v--; return *this; }
        ModInt32 operator ++ (int) { ModInt32 r = *this; ++*this; return r; }
        ModInt32 operator -- (int) { ModInt32 r = *this; --*this; return r; }
        ModInt32 & operator += (const ModInt32 &o) { v += o.v; if (v >= P)v -= P; return *this; }
        ModInt32 operator + (const ModInt32 & o)const { return ModInt32(*this) += o; }
        ModInt32 & operator -= (const ModInt32 & o) { v -= o.v; if (v < 0)v += P; return *this; }
        ModInt32 operator - (const ModInt32 &o)const { return ModInt32(*this) -= o; }
        ModInt32 & operator *=(const ModInt32 & o) { v = (int)(((i64)v)*o.v%P); return *this; }
        ModInt32 operator * (const ModInt32 & o)const { return ModInt32(*this) *= o; }
        ModInt32 & operator /= (const ModInt32 & o) { return (*this) *= o.Inv(); }
        ModInt32 operator / (const ModInt32 & o)const { return ModInt32(*this) /= o; }
        friend ModInt32 operator + (const ModInt32 &x, const i64 &o) { return x + (ModInt32)o; }
        friend ModInt32 operator + (const i64 &o, const ModInt32 &x) { return x + (ModInt32)o; }
        friend ModInt32 operator - (const ModInt32 &x, const i64 &o) { return x - (ModInt32)o; }
        friend ModInt32 operator - (const i64 &o, const ModInt32 &x) { return (ModInt32)o - x; }
        friend ModInt32 operator * (const ModInt32 &x, const i64 &o) { return x * (ModInt32)o; }
        friend ModInt32 operator * (const i64 &o, const ModInt32 &x) { return x * (ModInt32)o; }
        friend ModInt32 operator / (const ModInt32 &x, const i64 &o) { ModInt32 c = o; return x * c.Inv(); }
        friend ModInt32 operator / (const i64 &o, const ModInt32 &x) { ModInt32 c = o; return c * x.Inv(); }
        ModInt32 operator ^ (i64 o)const { ModInt32 r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
        ModInt32 operator ~ () { return (*this) ^ (P - 2); }
        ModInt32 Inv() const { return (*this) ^ (P - 2); }
        friend std::istream & operator >> (std::istream &in, ModInt32 &x) { i64 d; in >> d; x = d; return in; }
        friend std::ostream & operator << (std::ostream &out, const ModInt32 &x) { out << x.v; return out; }
    };
}
// using mint = RoyalGuard::Integer::ModInt32<int(1e9 + 7)>;
using mint = RoyalGuard::Integer::ModInt32<int(998244353)>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::string s;
    cin >> n >> s;

    constexpr int M = 26 + 26 + 10 + 1;

    using Info = array<array<mint,M>, (1 << 3)>;
    
    auto To = [](auto x) {
        if (std::isdigit(x)) {
            return x - '0' + 1;
        } else if (std::islower(x)) {
            return x - 'a' + 10 + 1;
        } else {
            return x - 'A' + 26 + 10 + 1;
        }
    };

    Info dp{};
    dp[0][0] = 1;
    for (int i = 0; i < n; i ++) {
        auto x = s[i];
        Info ndp{};

        for (int mask = 0; mask < (1 << 3); mask ++) {
            if (x == '?') {
                array<mint, M> cnt{};
                mint sum = 0;
                for (int pre = 0; pre < M; pre ++) {
                    cnt[pre] += dp[mask][pre];
                    sum += dp[mask][pre];
                }
                for (int now = 1; now <= 10; now ++) {
                    ndp[mask | 1][now] += sum - cnt[now];     
                }
                for (int now = 11; now <= 36; now ++) {
                    ndp[mask | 2][now] += sum - cnt[now];     
                }
                for (int now = 37; now <= 62; now ++) {
                    ndp[mask | 4][now] += sum - cnt[now];     
                }
                continue;
            }
            
            if (std::isdigit(x)) {
                for (int pre = 0; pre < M; pre ++) {
                    if (To(x) == pre) continue;
                    ndp[mask | 1][To(x)] += dp[mask][pre];     
                }
                continue;
            }

            if (std::islower(x)) {
                for (int pre = 0; pre < M; pre ++) {
                    if (To(x) != pre) {
                        ndp[mask | 2][To(x)] += dp[mask][pre];     
                    }
                    if (To(std::toupper(x)) != pre) {
                        ndp[mask | 4][To(std::toupper(x))] += dp[mask][pre];     
                    }
                }
                continue;
            }

            if (std::isupper(x)) {
                for (int pre = 0; pre < M; pre ++) {
                    if (To(x) == pre) continue;
                    ndp[mask | 4][To(x)] += dp[mask][pre];     
                }
                continue;
            }
        }

        std::swap(dp, ndp);
    }

    auto ans = std::reduce(dp[7].begin(), dp[7].end());
    cout << ans << '\n';
}
