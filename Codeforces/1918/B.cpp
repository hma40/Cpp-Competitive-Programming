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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        vt<int> inv(n+1);
        F0R(i, n) {
            inv[a[i]]=i;
        }
        F0R(i, n) {
            int other = inv[i+1];
            inv[i+1]=i;
            inv[a[i]]=other;
            swap(a[i], a[other]);
            swap(b[i], b[other]);
            // cout << a << b << inv << endl;
        }
        // cout << a << b << endl;
        F0R(i, n) {
            cout << a[i] << " ";
        }
        cout << endl;
        F0R(i, n) cout << b[i] << " ";
        cout << endl;
    }
    return 0;
}
/*
6
2 5 6 1 3 4
1 5 3 6 2 4

1 5 6 2 3 4
6 5 3 1 2 4

1 2 6 5 3 4
6 1 3 5 2 4

1 2 3 5 6 4
6 1 2 5 3 4

1 2 3 4 6 5
6 1 2 4 3 5

1 2 3 4 5 6
6 1 2 4 5 3
*/