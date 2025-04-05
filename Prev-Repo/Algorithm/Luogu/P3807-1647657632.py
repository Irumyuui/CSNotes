def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = exgcd(b, a % b)
    return d, y, x - a // b * y

def inv(a, p):
    d, x, y = exgcd(a, p)
    return (x % p + p) % p

fact = lambda n : 1 if n <= 1 else n * fact(n - 1)

def C(n, m, p):
    a = 1
    for i in range(n, n - m, -1):
        a = a * i % p
    b = 1
    for i in range(1, m + 1):
        b = b * i % p
    return a * inv(b, p) % p

def lucas(n, m, p):
    if n == 0:
        return 1
    return lucas(n // p, m // p, p) * C(n % p, m % p, p) % p

for i in range(int(input())):
    n, m, p = map(int, input().split())
    print(lucas(n + m, m, p))