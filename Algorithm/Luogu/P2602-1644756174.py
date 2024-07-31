from ast import IsNot
from numpy import power


c = [int(0) for i in range(0, 20)]
ans = [int(0) for i in range(0, 20)]
power10 = [int(0) for i in range(0, 20)]

def solve(n : int, ratio : int):
    m = 0
    while n:
        m += 1
        c[m] = n % 10
        n //= 10
    i = 1
    j = m
    while i < j:
        c[i], c[j] = c[j], c[i]
        i += 1
        j -= 1
    for i in range(1, m + 1):
        for j in range(1, i):
            ans[c[j]] += ratio * c[i] * power10[m - i]
        for j in range(1, c[i]):
            ans[j] += ratio * power10[m - i]
        if i != 1 and c[i] > 0:
            ans[0] += ratio * power10[m - i]
        if i != m:
            for j in range(1, 10):
                ans[j] += ratio * c[i] * (m - i) * power10[m - i - 1]
            if i != 1:
                ans[0] += ratio * c[i] * (m - i) * power10[m - i - 1]
        if i == 1:
            if m >= 2:
                ans[0] += ratio * (c[i] - 1) * (m - 1) * power10[m - 2]
            for j in range(2, m):
                ans[0] += ratio * 9 * (m - j) * power10[m - j - 1]
    for i in range(1, m + 1):
        ans[c[i]] += ratio

power10[0] = 1
for i in range(1, 20):
    power10[i] = power10[i - 1] * 10
l, r = [int(i) for i in input().split()]
solve(r, 1)
solve(l - 1, -1)
for i in range(0, 10):
    print(ans[i], end = ' ');