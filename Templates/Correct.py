import sys
from collections import deque as dq
input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))
###############################################
from collections import Counter
from itertools import product
def get_prime_factors(num):
    prime_factors = [1] * num
    for i in range(2, num):
        if prime_factors[i] > 1:  # i is not prime
            continue
        prime_factors[i]=i
        for j in range(i*i, num, i): # i is prime prime.append(i)
            prime_factors[j] = i
    return prime_factors
pp=get_prime_factors(100001)

def get_divisor(n):
    pf=[]
    while n>1:
        pf.append(pp[n])
        n//=pp[n]
    pfc=Counter(pf)
    powers=[[f**i for i in range(c+1)] for f,c in pfc.items()]
    ret=[]
    for i in product(*powers):
        f=1
        for j in i:f*=j
        ret.append(f)
    return ret

T = sint()
for _ in range(T):
    n,m,q=mint()
    a=aint()
    b=aint()
    sa=sum(a)
    ssa=set()
    for i in a:ssa.add(sa-i)
    sb=sum(b)
    ssb=set()
    for i in b:ssb.add(sb-i)
    for _ in range(q):
        x=sint()
        for i in get_divisor(abs(x)):
            j=x//i
            if (i in ssa and j in ssb) or (-i in ssa and -j in ssb):
                print('YES');break
        else:
            print('NO')
    