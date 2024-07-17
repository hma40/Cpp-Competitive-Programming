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
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> f(n),s(n);
        F0R(i, n) cin >> f[i];
        F0R(j, n) cin >> s[j];
        F0R(i,n) {
            f[i]--;
            s[i]--;
        }
        vt<int> fc(n),sc(n);
        F0R(i, n) fc[f[i]]++;
        F0R(i, n) sc[s[i]]++;
        vt<int> ansf,anss;
        int more0 = 2*k, more1 = 2*k;
        vt<int> fr,sr;
        // cout << fc << sc << endl;
        F0R(i, n) {
            if(fc[i]==2&&more0>=2) {
                more0-=2;
                fr.add(i+1);
                fr.add(i+1);
            } 
        }
        F0R(i, n) {
            if(fc[i]==1&&more0>=1) {
                // cout << "LINE 83 " << i << endl;
                more0--;
                more1--;
                fr.add(i+1);
                sr.add(i+1);
            }
        }
        F0R(i, n) {
            if(sc[i]==2&&more1>=2) {
                sr.add(i+1);
                sr.add(i+1);
                more1-=2;
            }
        }
        F0R(i, 2*k) {
            cout << fr[i] << " ";
        }
        cout << endl;
        F0R(i, 2*k) cout << sr[i] << " ";
        cout << endl;
    }
    return 0;
}