import math

class Frac:
    def __init__(self, n, d):
        self.n = n
        self.d = d

    def simplify(self):
        g = math.gcd(self.n, self.d)
        self.n //= g
        self.d //= g

def gcd(a, b):
    a, b = abs(a), abs(b)
    return math.gcd(a, b)

def add(a, b):
    g = a.d * b.d // gcd(a.d, b.d)
    num = a.n * (g // a.d) + b.n * (g // b.d)
    common_divisor = gcd(num, g)
    num //= common_divisor
    g //= common_divisor
    return Frac(num, g)

def divide(frac, x):
    g = gcd(x, frac.n)
    frac.n //= g
    frac.d *= (x // g)
    frac.simplify()
    return frac

def test(num, times):
    for _ in range(times):
        if num % 2 == 0:
            num //= 2
        else:
            num = num * 3 + 1
    return num

def main():
    s = input().strip()
    n = len(s)
    pr = (Frac(1, 1), Frac(0, 1))
    
    for i in range(n - 1, -1, -1):
        if s[i] == 'O':
            pr = (divide(pr[0], 3), divide(add(pr[1], Frac(-1, 1)), 3))
        else:
            pr[0].n *= 2
            pr[1].n *= 2
            pr[0].simplify()
            pr[1].simplify()

    i = 1
    comp = 1
    for i in range(48):
        comp*=2
    for i in range(250):
        i*=2
        fra = Frac(pr[0].n * i, pr[0].d)
        fra = add(fra, pr[1])
        g = gcd(fra.d, fra.n)
        
        if g == fra.d:
            ans = fra.n // fra.d
            if test(ans, n) == i and ans<=comp:
                print(ans)
                return

    print("INVALID")

main()
