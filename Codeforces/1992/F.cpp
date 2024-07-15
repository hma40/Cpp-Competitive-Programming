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
    int t;
    cin >> t;
    while(t--) {
        int n,x;
        cin >> n >> x;
        set<int> factors;
        for(int i = 1; i*i<=x; i++) {
            if(x%i==0) {
                factors.insert(i);
                factors.insert(x/i);
            }
        }
        // cout << factors << endl;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        set<int> cur;
        int ans = 1;
        cur.insert(1);
        F0R(i, n) {
            vt<int> here;
            trav(y, cur) {
                // vt<int> here;
                if(y*v[i]==x) {
                    cur.clear();
                    cur.insert(1);
                    ans++;
                    here.clear();
                    cur.insert(v[i]);
                    break;
                }
                if(factors.count(y*v[i])) {
                    here.add(v[i]*y);
                }
            }
            trav(y, here) cur.insert(y);
            // cout << i << cur << ans << endl;
        }
        cout << ans << endl;
    }
    return 0;
}