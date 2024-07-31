from math import factorial as fact

def Solve():
    a = [int(i) for i in input().split()]
    tot = sum(a) * 1.0
    ans = fact(7) * (tot - 6)
    for i in range(7):
        ans *= a[i] / max(tot - i, 1)
    print("{:.3f}".format(ans))
    return None

if __name__ == '__main__':
	Solve()