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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    vt<vt<int>> factors(500005);
    FOR(i, 1, 500005) {
        for(int j = i; j < 500005; j+=i) factors[j].add(i);
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> a(n+1), b(n+1);
        ll ans = 0;
        FOR(i, 1, n+1) {
            int x;
            cin >> x;
            int g = gcd(i,x);
            x/=g;
            int j = i/g;
            b[x].add(j);
            a[j].add(x);
            if(i==g) ans--;
        }
        // cout << a << endl << b << endl;
        vt<int> c(n+1);
        FOR(i, 1, n+1) {
            for(int j = i; j <= n; j+=i) {
                trav(x, b[j]) c[x]++;
            }
            for(int x: a[i]) {
                trav(y, factors[x]) ans+=c[y];
            }
            for(int j = i; j <= n; j+=i) {
                trav(x, b[j]) c[x]--;
            }
        }
        cout << ans/2 << endl;
    }
    return 0;
}//