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
    int n,m;
    cin >> n >> m;
    map<int,int> mp;
    vt<pair<int,int>> v(n);
    F0R(i, n) cin >> v[i].f;
    F0R(i, n) cin >> v[i].s;
    F0R(i, n) mp[v[i].f]=max(mp[v[i].f], v[i].s);
    // cout << mp << endl;
    // cout.flush();

    vt<int> dp(1000001);
    mp[inf]=inf;
    int bestChange = inf;
    auto sob = mp.begin();
    F0R(i, 1000001) {
        while((*sob).f<=i) {
            bestChange=min(bestChange, (*sob).f-(*sob).s);
            sob++;
        }
        // cout << i << " " << bestChange << endl;
        // cout.flush();
        if(bestChange!=inf) {
            dp[i]=dp[i-bestChange]+2;
        }
    }
    int ans = 0;
    F0R(i, m) {
        int x;
        cin >> x;
        if(x>1000000) {
            int moves = (bestChange+x-1000001)/bestChange;
            ans+=2*moves;
            x-=bestChange*moves;
        }
        ans+=dp[x];
    }
    cout << ans << endl;
    return 0;
}