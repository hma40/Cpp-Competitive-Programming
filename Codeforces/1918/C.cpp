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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int solve(int decided, int a, int b, int mx) {
    // int ans = 0;
    if(mx<0) {
        return abs((a^decided)-(b^decided));
    }
    int diff = 0;
    ROF(i, mx+1, 62) {
        if(decided&(1LL<<i)) {
            if((a&(1LL<<i))==0) {
                diff+=(1LL<<i);
            }
            if((b&(1LL<<i))==0) {
                diff-=(1LL<<i);
            }
        } else {
            if(a&(1LL<<i)) {
                diff+=(1LL<<i);
            }
            if(b&(1LL<<i)) {
                diff-=(1LL<<i);
            }
        }
    }
    R0F(i, mx+1) {
        if((a&(1LL<<i))!=(b&(1LL<<i))) {
            if(diff<0) {
                diff+=(1LL<<i);
            } else {
                diff-=(1LL<<i);
            }
        }
    }
    return abs(diff);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int a,b,r;
        cin >> a >> b >> r;
        int decided = 0;
        int ans = abs((a^r)-(b^r));
        R0F(i, 62) {
            if(r&(1LL<<i)) {
                ans=min(ans, solve(decided, a, b, i-1));
                decided|=(1LL<<i);
            }
        }
        cout << ans << endl;
    }
    return 0;
}