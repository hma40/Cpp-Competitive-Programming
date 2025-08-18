import sys

# It's common for competitive programming to increase recursion limit
# sys.setrecursionlimit(100000)

def solve():
    """
    Main function to read N and compute the sequence.
    You can change N here for testing.
    """
    N = 10 # Calculate f(0) to f(9)

    # --- NTT Boilerplate ---
    MOD = 998244353
    ROOT = 3
    
    def power(a, b):
        res = 1
        a %= MOD
        while b > 0:
            if b % 2 == 1:
                res = (res * a) % MOD
            a = (a * a) % MOD
            b //= 2
        return res

    def inv(n):
        return power(n, MOD - 2)

    def ntt(a, invert):
        n = len(a)
        j = 0
        for i in range(1, n):
            bit = n >> 1
            while j & bit:
                j ^= bit
                bit >>= 1
            j ^= bit
            if i < j:
                a[i], a[j] = a[j], a[i]

        length = 2
        while length <= n:
            wlen = power(ROOT, (MOD - 1) // length)
            if invert:
                wlen = inv(wlen)
            i = 0
            while i < n:
                w = 1
                for j in range(length // 2):
                    u = a[i + j]
                    v = (a[i + j + length // 2] * w) % MOD
                    a[i + j] = (u + v) % MOD
                    a[i + j + length // 2] = (u - v + MOD) % MOD
                    w = (w * wlen) % MOD
                i += length
            length <<= 1
        
        if invert:
            n_inv = inv(n)
            for i in range(n):
                a[i] = (a[i] * n_inv) % MOD
        return a

    def convolution(a, b):
        n = 1
        while n < len(a) + len(b):
            n <<= 1
        
        fa = a[:] + [0] * (n - len(a))
        fb = b[:] + [0] * (n - len(b))

        ntt(fa, False)
        ntt(fb, False)

        for i in range(n):
            fa[i] = (fa[i] * fb[i]) % MOD
        
        ntt(fa, True)
        return fa
    # --- End NTT Boilerplate ---

    f = [0] * (N + 1)
    if N >= 0:
        f[0] = 1
    if N >= 1:
        f[1] = 1

    m = 2
    while m <= N:
        # 1. Define polynomials based on f[0...m-1]
        len_conv = 2 * m
        A = f[:m]
        Ad = [(i * f[i]) % MOD for i in range(m)]

        # 2. Perform convolutions
        C_coeffs = convolution(A, A)[:len_conv]
        D_coeffs = convolution(Ad, A)[:len_conv]

        # 3. Compute prefix sums
        pc = [0] * len_conv
        pd = [0] * len_conv
        pc[0] = C_coeffs[0]
        pd[0] = D_coeffs[0]
        for i in range(1, len_conv):
            pc[i] = (pc[i-1] + C_coeffs[i]) % MOD
            pd[i] = (pd[i-1] + D_coeffs[i]) % MOD

        # 4. Calculate f[m...2m-1]
        for n in range(m, min(2 * m, N + 1)):
            k = n - 1
            half_k = k // 2
            
            # Sums for the first half [0, half_k]
            c_half_sum = pc[half_k]
            d_half_sum = pd[half_k]

            # Sums for the second half [half_k+1, k]
            c_second_half_sum = (pc[k] - c_half_sum + MOD) % MOD
            d_second_half_sum = (pd[k] - d_half_sum + MOD) % MOD
            
            term1_val = (c_half_sum - c_second_half_sum + MOD) % MOD
            term1 = (k * term1_val) % MOD

            term2_val = (d_second_half_sum - d_half_sum + MOD) % MOD
            term2 = (2 * term2_val) % MOD
            
            delta_k = (term1 + term2) % MOD
            f[n] = delta_k

        m *= 2

    # Print results for verification
    print(f"Calculated values of f(n) up to N={N-1}:")
    for i in range(N):
        print(f"f({i}) = {f[i]}")

# Execute the solution
solve()

# Expected output for N=6:
# f(0) = 1
# f(1) = 1
# f(2) = 2
# f(3) = 8
# f(4) = 52
# f(5) = 448