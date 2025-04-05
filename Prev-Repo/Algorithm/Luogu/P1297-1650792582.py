n, A, B, C, _ = map(int, input().split())
a = [0] * (n + 1)
a[1] = _
for i in range(2, n + 1):
    a[i] = (a[i - 1] * A + B) % 100000001
for i in range(1, n + 1):
    a[i] = a[i] % C + 1

a[0] = a[n]
ans = 0.0
for i in range(1, n + 1):
    ans += 1 / max(a[i - 1], a[i])
print("{:.3f}".format(ans))