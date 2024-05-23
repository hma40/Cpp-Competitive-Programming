#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
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
ll mod = 1000000007;
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
    int t;
    cin >> t;
    while(t--) {
        int m,x;
        cin >> m >> x;
        vt<int> v(m);
        F0R(i, m) cin >> v[i];
        vt<vt<int>> dp(m+1, vt<int>(m+1, -inf)); //max money after x days and at least y happiness
        // cout << dp << endl;
        dp[0][0]=0;
        FOR(i, 1, m+1) {
            F0R(j, dp[i-1].size()) {
                dp[i][j]=dp[i-1][j];
            }
            R0F(j, dp[i].size()-1) {
                // if(j>=dp[i-1].size()) continue;
                if(dp[i-1][j]>=v[i-1]) {
                    // cout << "LINE 70: " << i << " " << j << endl;
                    // if(j+v[i-1].s<dp[i].size()&&j<dp[i-1].size()) {
                    dp[i][j+1]=max(dp[i][j+1], dp[i-1][j]-v[i-1]);
                    // }
                    // cout << i << " " << j+v[i-1].s << " " << dp[i][j+v[i-1].s] << endl;
                    // cout << dp[1][10] << endl;.
                }
            }
            F0R(j, dp[i].size()) {
                dp[i][j]+=x;
            }
        }
        int ans = -inf;
        F0R(i, dp[m].size()) {
            if(dp[m][i]>=0) {
                ans=i;
            }
        }
        cout << dp.back() << endl;
        cout << ans << endl;
    }
    return 0;
}
/*
1
10 258
504 13 899 872 992 868 74 723 823 667
*/