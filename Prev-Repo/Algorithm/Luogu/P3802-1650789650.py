def fact(n : int) -> int:
    return 1 if n <= 1 else fact(n - 1) * n

a = [int(i) for i in input().split()]
s = sum(a); ans = fact(7) * 1.0
for i in a:
    ans *= i
for i in range(6):
    ans /= s; s -= 1
print("{:.3f}".format(ans))