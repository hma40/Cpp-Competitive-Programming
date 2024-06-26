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
int gcd(int x, int y) {
    if(x>y) return gcd(y,x);
    if(x==0) return y;
    return gcd(y%x, x);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m,k;
        cin >> n >> m >> k;
        vt<vt<int>> height(n,vt<int>(m));
        int zS=0, oS=0;
        F0R(i, n) {
            F0R(j, m) cin >> height[i][j];
        }
        vt<string> type(n);
        F0R(i, n) cin >> type[i];
        vt<vt<int>> pref(n+1, vt<int>(m+1));
        F0R(i, n) {
            F0R(j, m) {
                if(type[i][j]=='1') {
                    pref[i+1][j+1]=pref[i][j+1]+pref[i+1][j]-pref[i][j]+1;
                } else {
                    pref[i+1][j+1]=pref[i][j+1]+pref[i+1][j]-pref[i][j];
                }
            }
        }
        F0R(i, n) {
            F0R(j, m) {
                if(type[i][j]=='1') {
                    oS+=height[i][j]; 
                } else {
                    zS+=height[i][j];
                }
            }
        }
        int g = 0;
        FOR(i, k, n+1) {
            FOR(j, k, m+1) {
                int oc = pref[i][j]-pref[i-k][j]-pref[i][j-k]+pref[i-k][j-k];
                int zc = k*k-oc;
                g=gcd(g, abs(oc-zc));
            }
        }
        if(g==0) {
            if(abs(oS-zS)!=0) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        } else {
            if(abs(oS-zS)%g==0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}