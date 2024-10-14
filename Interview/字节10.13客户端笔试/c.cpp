#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>

using i64 = std::int64_t;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Main()
{
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    if (s.size() == 2)
    {

        if (k % 2)
        {
            std::swap(s[0], s[1]);
        }
        std::cout << s << '\n';

        return;
    }

    for (int l = 0, r = n - 1; l < r && k > 0;)
    {
        while (l < r && s[l] == '0')
        {
            l++;
        }
        while (l < r && s[r] == '1')
        {
            r--;
        }
        if (l < r)
        {
            std::swap(s[l], s[r]);
            k--;
        }
        else
        {
        }
    }

    std::cout << s << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    for (int tt = 1; tt <= t; tt++)
    {
        // std::cerr << "tt = " << tt << '\n';
        Main();
    }
}