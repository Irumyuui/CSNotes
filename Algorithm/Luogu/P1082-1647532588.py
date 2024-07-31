def Exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = Exgcd(b, a % b)
    return d, y, x - a // b * y

a, b = map(int, input().split())
d, x, y = Exgcd(a, b)
print(((x % b) + b) % b)