import sys
from collections import defaultdict
from itertools import product

# Input read optimization
def input():
    return sys.stdin.readline().strip()

def main():
    sys.setrecursionlimit(10**6)
    n, q = map(int, input().split())

    suma = sumb = sumc = 0
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    c = list(map(int, input().split()))

    suma = sum(a)
    sumb = sum(b)
    sumc = sum(c)

    limit = 1000000
    possa = [False] * (limit + 1)
    possb = [False] * (limit + 1)
    possc = [False] * (limit + 1)
    nega = [False] * (limit + 1)
    negb = [False] * (limit + 1)
    negc = [False] * (limit + 1)
    possab = [False] * (limit + 1)
    negab = [False] * (limit + 1)
    possabc = [False] * (limit + 1)
    negabc = [False] * (limit + 1)

    for x in a:
        diff = suma - x
        if abs(diff) <= limit:
            if diff >= 0:
                possa[diff] = True
            else:
                nega[-diff] = True

    for x in b:
        diff = sumb - x
        if abs(diff) <= limit:
            if diff >= 0:
                possb[diff] = True
            else:
                negb[-diff] = True

    for x in c:
        diff = sumc - x
        if abs(diff) <= limit:
            if diff >= 0:
                possc[diff] = True
            else:
                negc[-diff] = True

    for i in range(limit + 1):
        for j in range(limit // i + 1):
            if i * j > limit:
                break
            if possa[i] and possb[j]:
                possab[i * j] = True
            if possa[i] and negb[j]:
                negab[i * j] = True
            if nega[i] and possb[j]:
                negab[i * j] = True
            if nega[i] and negb[j]:
                possab[i * j] = True

    for i in range(limit + 1):
        for j in range(limit // i + 1):
            if i * j > limit:
                break
            if possab[i] and possc[j]:
                possabc[i * j] = True
            if possab[i] and negc[j]:
                negabc[i * j] = True
            if negab[i] and possc[j]:
                negabc[i * j] = True
            if negab[i] and negc[j]:
                possabc[i * j] = True

    results = []
    for _ in range(q):
        x = int(input())
        if x >= 0:
            if possabc[x]:
                results.append("YES")
            else:
                results.append("NO")
        else:
            if negabc[-x]:
                results.append("YES")
            else:
                results.append("NO")

    sys.stdout.write("\n".join(results) + "\n")

if __name__ == "__main__":
    main()
