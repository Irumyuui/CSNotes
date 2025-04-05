#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

using i64 = std::int64_t;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Main()
{
    std::string s;
    std::cin >> s;

    for (int i = 0; i < s.size(); i++)
    {
        if ((s[i] - '0') % 2)
        {
            for (int j = i + 1; j < s.size(); j++)
            {
                if ((s[j] - '0') % 2)
                {
                    std::cout << s[i] << s[j] << '\n';
                    return;
                }
            }

            break;
        }
    }

    std::cout << -1 << '\n';
    return;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        Main();
    }
}