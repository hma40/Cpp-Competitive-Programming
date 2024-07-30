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
        int n,m;
        cin >> n >> m;
        map<int,int> mp;
        vt<int> c(n);
        F0R(i, n) cin >> c[i];
        F0R(i, n) {
            int ct;
            cin >> ct;
            mp[c[i]]=ct;
        }
        int ans = 0;
        trav(x, mp) {
            int c0 = x.s;
            int c1 = 0;
            if(mp.count(x.f+1)) c1=mp[x.f+1];
            int zh = m/x.f;
            // cout << x << zh << endl;
            if(c0>=zh) {
                // cout << "LINE 79 " << endl;
                int here = zh*x.f;
                int rem = m-x.f*zh;
                rem=min(rem, zh);
                if(c1>=rem) {
                    ans=max(ans, here+rem);
                } else {
                    ans=max(ans, here+c1);
                }
            } else {
                int here = c0*x.f;
                int rem = m-x.f*x.s;
                int cc = rem/(x.f+1);
                // cout << here << " " << rem << " " << cc << " " << endl;
                if(c1>=cc) {
                    here+=cc*(x.f+1);
                    c1-=cc;
                    rem-=cc*(x.f+1);
                    rem=min(rem, x.s);
                    // cout << here << " " << rem << " " << c1 << endl;
                    if(c1>=rem) {
                        ans=max(ans, here+rem);
                    } else {
                        ans=max(ans, here+c1);
                    }
                } else {
                    ans=max(ans, x.f*x.s+(x.f+1)*c1);
                }
            }
            // cout << x << c0 << " " << c1 << " " << ans << endl;
        }
        // assert(ans<=m);
        cout << ans << endl;
    }
    return 0;
}
/*
1
5 93
20 21 35 41 43
3 56 72 78 17
*/