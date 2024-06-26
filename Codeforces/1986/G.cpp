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
int gcd(int a, int b) {
    if(a>b) return gcd(b,a);
    if(a==0) return b;
    return gcd(b%a, a);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int MAXN = 5e5+50;
    vt<vt<int>> divis(MAXN);
    for(int i = 1; i < MAXN; i++) {
        for(int j = i; j < MAXN; j+=i) {
            divis[j].add(i);
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        // map<pair<int,int>,int> maps;
        multiset<pair<int,int>> maps;
        ll ans = 0;
        F0R(i, n) {
            pair<int,int> p = {v[i], i+1};
            int g = gcd(p.f, p.s);
            p.f/=g;
            p.s/=g;
            trav(x, divis[p.f]) {
                ans+=maps.count({x,p.s});
                // if(maps.count({x,p.s})) {
                //     ans+=maps[{x,p.s}];
                // }
            }
            trav(x, divis[p.f]) {
                maps.insert({p.s,x});
            }
        }
        cout << ans << endl;
    }
    return 0;
}