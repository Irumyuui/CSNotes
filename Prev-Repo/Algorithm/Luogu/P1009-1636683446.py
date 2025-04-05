n = int(input())
res = int(1)
res2 = int(1)
for i in range(2, n + 1):
    res2 *= i
    res += res2
print(res)