def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = exgcd(b, a % b)
    return d, y, x - a // b * y

def excrt(a, b, c, d):
    g, t0, no = exgcd(b, d)
    if (c - a) % g != 0:
        return False, -1, -1
    d //= g
    t = (c - a) // g * t0 % d
    if t < 0:
        t += d
    return True, b * t + a, b * d

if __name__ == "__main__":
    a, b, ok = 0, 1, True
    for t in range(int(input())):
        d, c = map(int, input().split())
        if ok:
            ok, a, b = excrt(a, b, c, d)
    print(a)
