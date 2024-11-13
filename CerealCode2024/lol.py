# Source: https://usaco.guide/general/io

def gcd(a, b):
    if a==0:
        return b
    if b==0:
        return a
    return gcd(b, a%b)

def add(a, b):
    num = a[0]*b[1]+a[1]*b[0]
    den = a[1]*b[1]
    g = gcd(num, den)
    print(den)
    return [num//g, den//g]

def mul(a, b):
    num = a[0]*b[0]
    den = a[1]*b[1]
    g = gcd(num, den)
    print(den)
    return [num//g, den//g]

def solve(n, m, p):
    print(n,m,p)
    if n==0:
        if p==0:
            print("1/1")
        else:
            print("0/1")
        return
    if p==0:
        print("0/1")
        return
    unused = m-2*n
    dp = [[0 for _ in range(100)] for j in range(100)]
    dp[0][0]=[1,1]
    for i in range(1,n+1):
        dp[0][i]=[0,1]
    for i in range(1, p):
        dp[i][0]=mul(dp[i-1][0], [unused-i+1, m-i+1])

    for i in range(1, p):
        for j in range(1, n+1):
            totUnused = j*2+unused;
            totUnused=max(0, totUnused-i+1);
            tot = m-i+1;
            dp[i][j]=mul(dp[i-1][j], [totUnused, tot]);
            squaresLeft = max(0, n-j+1);
            totUnused = 2*squaresLeft;
            dp[i][j]=add(dp[i][j], mul(dp[i-1][j-1], [totUnused, tot]));
    ans = mul(dp[p-1][n-1], [2, m-p+1])
    print(str(ans[0])+"/"+str(ans[1]))


l = input().split()
# m = int(l[0])
# n = int(l[1])
# p = int(l[2])
for m in range(2, 34):
    for n in range(0, m//2+1):
        for p in range(0, m+1):
            solve(n,m,p)

