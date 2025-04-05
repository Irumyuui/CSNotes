def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = exgcd(b, a % b)
    return d, y, x - a // b * y

def inv(a, p):
    d, x, y = exgcd(a, p)
    return (x % p + p) % p

def CRT(n, a : list, r : list):
    m = 1; ans = 0
    for i in range(n):
        m = m * r[i]
    for i in range(n):
        mk = m // r[i]
        ans = (ans + a[i] * mk * inv(mk, r[i])) % m
    return ans

n = int(input())
a = [0] * n
r = [0] * n
for i in range(n):
    r[i], a[i] = map(int, input().split())
print(CRT(n, a, r))