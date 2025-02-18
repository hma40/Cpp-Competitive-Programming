MOD = 998244353

def precompute_factorials(max_n):
    fact = [1] * (max_n + 1)
    inv_fact = [1] * (max_n + 1)
    for i in range(1, max_n + 1):
        fact[i] = fact[i-1] * i % MOD
    inv_fact[max_n] = pow(fact[max_n], MOD-2, MOD)
    for i in range(max_n-1, -1, -1):
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD
    return fact, inv_fact

max_n_fact = 3000
fact, inv_fact = precompute_factorials(max_n_fact)

def comb(n, k, fact, inv_fact):
    if k < 0 or k > n:
        return 0
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    # Compute C(n + k -1, n) mod MOD
    numerator = 1
    a = k % MOD
    for i in range(n):
        term = (a + i) % MOD
        numerator = numerator * term % MOD
    denominator = fact[n]
    c = numerator * pow(denominator, MOD-2, MOD) % MOD
    
    # Compute (n+1)^(n-1) mod MOD
    p = pow(n + 1, n - 1, MOD)
    
    ans = (c * p) % MOD
    print(ans)