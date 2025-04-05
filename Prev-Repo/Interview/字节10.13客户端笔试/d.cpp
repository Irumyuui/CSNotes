#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using i64 = std::int64_t;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

constexpr i64 Pow(i64 a, i64 i, i64 MOD)
{
    i64 ret = a % MOD;
    while (i > 0)
    {
        if (i & 1)
        {
            (ret *= a) %= MOD;
        }
        (a *= ret) %= MOD;
        i >>= 1;
    }
    return ret;
}

template <i64 N> struct ModInt
{
    i64 val;

    constexpr ModInt() : val(0)
    {
    }

    constexpr ModInt(i64 val) : val(val)
    {
    }

    constexpr ModInt operator+(const ModInt &other) const
    {
        return (val + other.val) % N;
    }

    constexpr ModInt operator-(const ModInt &other) const
    {
        return ((val - other.val) % N + N) % N;
    }

    constexpr ModInt operator*(const ModInt &other) const
    {
        return (val * other.val) % N;
    }

    constexpr ModInt operator/(const ModInt &other) const
    {
        return val * other.Inv();
    }

    constexpr i64 Inv() const
    {
        return Pow(val, N - 2, N);
    }

    bool operator==(const ModInt &o) const
    {
        return val == o.val;
    }

    bool operator!=(const ModInt &o) const
    {
        return val != o.val;
    }
};

constexpr i64 MOD[2] = {static_cast<i64>(1e9 + 9), static_cast<i64>(1e7 + 9)};

// struct Pair
// {
//     std::pair<ModInt<MOD[0]>, ModInt<MOD[1]>> p;

//     constexpr Pair operator+(const Pair &o) const
//     {
//         return {{p.first + o.p.first, p.second + o.p.second}};
//     }

//     constexpr Pair operator-(const Pair &o) const
//     {
//         return {{p.first - o.p.first, p.second - o.p.second}};
//     }

//     constexpr Pair operator*(const Pair &o) const
//     {
//         return {{p.first * o.p.first, p.second * o.p.second}};
//     }

//     constexpr Pair operator/(const Pair &o) const
//     {
//         return {{p.first / o.p.first, p.second / o.p.second}};
//     }
// };

// using P = std::pair<ModInt<MOD[0]>, ModInt<MOD[1]>>;

// constexpr P BS = {11114, 123};

using M1 = ModInt<MOD[0]>;
using M2 = ModInt<MOD[1]>;

constexpr std::pair<M1, M2> BS{114513, 19263};

void Main()
{
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    for (auto &x : s)
    {
        if (x != 'a' && x != 'e' && x != 'i' && x != 'o' && x != 'u')
        {
            x = 'z';
        }
    }

    std::vector<std::pair<M1, M2>> base(n + 2, {1, 1});
    for (int i = 1; i <= n; i++)
    {
        base[i].first = base[i - 1].first * BS.first;
        base[i].second = base[i - 1].second * BS.second;
    }

    std::vector<std::pair<M1, M2>> pre(n + 2), rep(n + 2);
    for (int i = 1; i <= n; i++)
    {
        pre[i].first = pre[i - 1].first * BS.first + s[i - 1];
        pre[i].second = pre[i - 1].second * BS.second + s[i - 1];
    }
    for (int i = n; i >= 1; i--)
    {
        rep[i].first = rep[i + 1].first * BS.first + s[i - 1];
        rep[i].second = rep[i + 1].second * BS.second + s[i - 1];
    }

    auto get_range_p = [&](int l, int r) -> std::pair<M1, M2> {
        return {
            pre[r].first - pre[l - 1].first * base[r - l + 1].first,
            pre[r].second - pre[l - 1].second * base[r - l + 1].second,
        };
    };

    auto get_range_r = [&](int l, int r) -> std::pair<M1, M2> {
        return {
            rep[l].first - rep[r + 1].first * base[r - l + 1].first,
            rep[l].second - rep[r + 1].second * base[r - l + 1].second,
        };
    };

    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        {
            int l = 1, r = std::min(i, n - i + 1), ret = 1;
            while (l <= r)
            {
                auto mid = l + (r - l) / 2;
                if (get_range_p(i - mid + 1, i) == get_range_r(i, i + mid - 1))
                {
                    ret = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            ans = std::max(ans, ret * 2 - 1);
        }
        {
            int l = 1, r = std::min(i, n - i), ret = 1;
            while (l <= r)
            {
                auto mid = l + (r - l) / 2;
                if (get_range_p(i - mid + 1, i) == get_range_r(i + 1, i + mid))
                {
                    ret = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            ans = std::max(ans, ret * 2);
        }
    }

    std::cout << ans << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    for (int tt = 1; tt <= t; tt++)
    {
        // std::cerr << "tt = " << tt << '\n';
        Main();
    }
}