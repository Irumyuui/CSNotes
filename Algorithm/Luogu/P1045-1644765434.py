import math

p = int(input())
print(int(math.log10(2) * p + 1))
n = int((pow(2, p) - 1) % pow(10, 500))

l = [int(0) for i in range(0, 500)]

m = 0
while n > 0 and m < 500:
    l[m] = n % 10
    n //= 10
    m += 1

m = 499
cnt = 0
while m >= 0:
    print(l[m], end = '')
    m -= 1
    cnt += 1
    if cnt >= 50:
        print()
        cnt = 0