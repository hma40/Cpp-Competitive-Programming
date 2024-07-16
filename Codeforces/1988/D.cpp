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
int n;
vt<int> v;
// vt<int> depth;
vt<vt<int>> dp;
vt<vt<int>> adj;
void reset() {
    v.assign(n, 0);
    // depth.assign(n,0);
    // dp.assign(n,0);
    dp.assign(n,vt<int>(25));
    adj.assign(n, vt<int>());
}
void calc(int node, int par) {
    trav(x, adj[node]) {
        if(x==par) continue;
        calc(x, node);
    } 
    for(int i = 1; i < 25; i++) {
        dp[node][i]=v[node]*i;
    }
    FOR(i, 1, 25) {
        trav(x, adj[node]) {
            if(x==par) continue;
            int mn = inf;
            FOR(j, 1, 25) {
                if(i==j) continue;
                mn=min(mn, dp[x][j]);
            }
            // cout << x << " " << mn << endl;
            dp[node][i]+=mn;
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        reset();
        F0R(i, n) cin >> v[i];
        F0R(i, n-1) {
            int a,b;
            cin >> a >> b;
            adj[--a].add(--b);
            adj[b].add(a);
        }
        calc(0, -1);
        // cout << dp << dp2 << endl;
        // cout << ans << endl;
        // cout << min(dp[0], dp2[0]) << endl;
        int ans = inf;
        // cout << dp << endl;
        FOR(i, 1, 25) ans=min(ans, dp[0][i]);
        cout << ans << endl;
    }
    return 0;
}