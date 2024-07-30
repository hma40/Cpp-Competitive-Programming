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
        int n,c,k;
        cin >> n >> c >> k;
        string s;
        cin >> s;
        multiset<int> window;
        F0R(i, k) {
            window.insert(s[i]-'A');
        }
        // cout << window << endl;
        vt<bool> poss(1<<c, true);
        int mask = (1<<c)-1;
        F0R(i, c) {
            // cout << i << " " << window.count(i) << endl;
            if(window.count(i)) mask^=(1<<i);
        }
        // cout << mask << endl;
        poss[mask]=false;
        FOR(i, k, n) {
            // cout << window << endl;
            // cout << s[i-k]-'A' << endl;
            window.erase(window.find(s[i-k]-'A'));
            window.insert(s[i]-'A');
            mask=(1<<c)-1;
            F0R(j, c) {
                if(window.count(j)) mask^=(1<<j);
            }
            // cout << mask << endl;
            poss[mask]=false;
        }
        // cout << poss << endl;
        vt<pair<int,int>> v;
        F0R(i, 1<<c) v.add({__builtin_popcount(i), i});
        sort(begin(v),end(v));
        // cout << poss.size() << endl;
        R0F(i, v.size()) {
            F0R(j, c) {
                poss[v[i].s]=poss[v[i].s]&&poss[v[i].s|(1<<j)];
            }
        }
        // cout << poss << endl;
        int ans = inf;
        F0R(i, 1<<c) {
            if(!poss[i]) continue;
            ans=min(ans, (int)__builtin_popcount(i|(1<<(s[n-1]-'A'))));
        }
        cout << ans << endl;
    }
    return 0;
}