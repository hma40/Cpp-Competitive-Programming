#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
struct Mint {
    int v;
    Mint(long long val = 0) {
        v = int(val % MOD);
        if (v < 0) v += MOD;
    }
    Mint operator+(const Mint &o) const { return Mint(v + o.v); }
    Mint operator-(const Mint &o) const { return Mint(v - o.v); }
    Mint operator*(const Mint &o) const { return Mint(1LL * v * o.v); }
    Mint operator/(const Mint &o) const { return *this * o.inv(); }
    Mint& operator+=(const Mint &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    Mint& operator-=(const Mint &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    Mint& operator*=(const Mint &o) { v = int(1LL * v * o.v % MOD); return *this; }
    Mint pow(long long p) const {
        Mint a = *this, res = 1;
        while (p > 0) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }
    Mint inv() const { return pow(MOD - 2); }
    friend ostream& operator<<(ostream& os, const Mint& m) {
        os << m.v;
        return os;
    }
};
void solve() {
    int N, K;
    cin >> N >> K;

    vector<vector<bool>> banned(N, vector<bool>(N));
    for (int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        banned[x - 1][y - 1] = true;
    }

    vector<Mint> tot(N + 1);
    tot[N] = 1;
    vector<vector<Mint>> dp(N + 1, vector<Mint>(N + 1));
    vector<vector<int>> chain(N + 1, vector<int>(N + 1));

    for (int i = N - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) {
            chain[i][j] = 1 + chain[i + 1][j + 1];
            if (banned[i][j]) chain[i][j] = 0;
        }
    }

    vector<vector<Mint>> ssum(N + 2, vector<Mint>(N + 1));

    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j <= N - i; ++j) {
            if (j == 0) {
                for (int len = 1; len <= N - i; ++len) {
                    bool ok = chain[i][0] >= len;
                    if (!ok) break;
                    dp[i][j] += tot[i + len];
                    if (j == 0) dp[i][j] -= dp[i + len][j + len];
                }
            } else {
                if (chain[i][j]) {
                    dp[i][j] += ssum[i + 1][j];
                    if (i + 1 + chain[i][j] <= N) {
                        dp[i][j] -= ssum[i + 1 + chain[i][j]][j];
                    }
                }
            }
            tot[i] += dp[i][j];
        }

        for (int j = 1; j < N; ++j) {
            ssum[i][j] = ssum[i + 1][j];
            if (chain[i][0] >= j) {
                ssum[i][j] += tot[i + j];
            }
        }
    }
    cout << tot[0].v << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}
/*
4
3 0
3 3
1 1
2 1
3 1
3 2
1 1
2 1
100 0
*/