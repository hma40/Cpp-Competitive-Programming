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
    int n;
    cin >> n;
    vt<int> v(n);
    F0R(i, n) cin >> v[i];
    vt<vt<int>> dp(n, vt<int>(n, inf));
    F0R(i, n) dp[i][n-1]=0;
    F0R(i, n) dp[n-1][i]=0;
    ROF(large, 1, n) {
        FOR(small, 1, large) {
            dp[small-1][large]=min(dp[small-1][large], dp[small][large]+abs(v[small-1]+v[small]));
            dp[small][small-1]=min(dp[small][small-1], dp[small][large]+abs(v[small-1]+v[large]));
            
        }
    }
    cout << dp << endl;
    /*
    0 1 5 6 9 13
    */
   F0R(i, n-1) {
    cout << i << " " << dp[i][i+1] << " " << dp[i+1][i] << endl;
   }
    return 0;
}