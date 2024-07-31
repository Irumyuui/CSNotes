from math import factorial as fact

def binom(n : int, m : int) -> int:
    return fact(n) // (fact(m) * fact(n - m))

def catalan(n : int) -> int:
    return binom(2 * n, n) // (n + 1)

print(catalan(int(input())))