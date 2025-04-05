f = [[0 for i in range(105)] for j in range(105)]
for n in range(1, 101):
    f[n][1] = 1
for n in range(2, 101):
    for m in range(1, n + 1):
        f[n][m] = f[n - 1][m - 1] + m * f[n - 1][m]
while True:
    try:
        n, m = [int(i) for i in input().split()]
    except:
        break
    print(f[n][m])    