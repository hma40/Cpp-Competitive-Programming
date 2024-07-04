#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
ll mod = 998244353;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vt<vt<int>> dp(n+1, vt<int>(k+1));
    vt<int> sum(k);
    sum[0]++;
    for(int i = 1; i <= n; i++) {
        for(int comp = 1; comp <= k; comp++) {
            dp[i][comp]+=sum[comp-1];
            if(i>2&&i<n) {
                dp[i][comp]-=dp[i-2][comp-1];
                if(comp==k) {
                    dp[i][comp]-=dp[i-2][comp];
                }
            }
            dp[i][comp]%=mod;
            dp[i][comp]+=mod;
            dp[i][comp]%=mod;
        }
        for(int comp = 0; comp < k; comp++) sum[comp]+=dp[i][comp];
        sum[k-1]+=dp[i][k];
        // cout << i << " " << sum << endl;
    }
    // cout << dp << endl;
    cout << dp[n][k] << endl;
    return 0;
}
/*
1 1 1 1
1 3
2 1 1
3 1

1 1 1
2 1
3
2
1 1
1
*/