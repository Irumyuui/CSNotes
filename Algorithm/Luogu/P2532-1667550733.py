from math import factorial as fact

def solve():
	n = int(input())
	print(fact(2 * n) // (fact(n) * fact(n + 1)))

if __name__ == '__main__':
	solve()