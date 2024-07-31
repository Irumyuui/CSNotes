def g(n):
    return n ^ (n >> 1)

n, k = map(int, input().split())
ans = g(k)
for i in range(n - 1, -1, -1):
    print((ans >> i) & 1, end = '')