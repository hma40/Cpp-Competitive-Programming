#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 1'000'000'007;

int64 modpow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

struct BIT {
    int n;
    vector<int64> t;
    BIT(int n=0): n(n), t(n+1, 0) {}
    void add(int i, int64 v) {
        for (; i <= n; i += i & -i) {
            t[i] += v;
            if (t[i] >= MOD) t[i] -= MOD;
        }
    }
    int64 sum(int i) const {
        int64 r = 0;
        for (; i > 0; i -= i & -i) {
            r += t[i];
            if (r >= MOD) r -= MOD;
        }
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> c(n+1, 0);
    for (int v : a) ++c[v];

    // Find K0 = largest k with all c[1..k] > 0
    int K0 = 0;
    for (int v = 1; v <= n; ++v) {
        if (c[v] == 0) break;
        K0 = v;
    }

    vector<int64> invc(K0+1, 0);
    for (int v = 1; v <= K0; ++v) invc[v] = modpow(c[v], MOD-2);

    vector<int64> B(K0+1, 0);
    BIT bit(K0);

    // Right-to-left scan to build B[x]
    for (int i = n-1; i >= 0; --i) {
        int v = a[i];
        if (v <= K0) {
            int64 s = bit.sum(v-1);
            B[v] += s;
            if (B[v] >= MOD) B[v] -= MOD;
            bit.add(v, invc[v]);
        }
    }

    vector<int64> ans(n, 0);
    int64 C = 1;     // product of c[1..k]
    int64 T = 0;     // sum_{x=1..k} inv(c[x]) * B[x]
    for (int k = 1; k <= n; ++k) {
        C = (C * c[k]) % MOD;
        if (k <= K0) {
            T += (B[k] * invc[k]) % MOD;
            if (T >= MOD) T -= MOD;
            ans[k-1] = (C * T) % MOD;
        } else {
            ans[k-1] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}