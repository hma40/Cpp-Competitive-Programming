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
    vt<int> oneLess;
    oneLess.add(0);
    FOR(i, 1, 33) {
        oneLess.add(oneLess.back()*2+1);
    }
    // cout << oneLess << endl;
    while(t--) {
        int n,m;
        cin >> n >> m;
        int ans = 0;
        F0R(i, 35) {
            int moves;
            if(n&(1LL<<i)) {
                ans^=(1LL<<i);
                continue;
            } else if(n<(1LL<<i)) {
                moves = (1LL<<i)-n;
            } else {
                int last = n&oneLess[i];
                moves=min((1LL<<i)-last, last+1);
            }
            // cout << i << " " << moves << endl;
            if(moves<=m) {
                ans^=(1LL<<i);
            }
        }
        cout << ans << endl;
    }
    return 0;
}