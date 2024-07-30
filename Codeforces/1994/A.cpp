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
        int n,m;
        cin >> n >> m;
        vt<vt<int>> v(n,vt<int>(m));
        F0R(i,n){
            F0R(j,m) cin >> v[i][j];
        }
        if(n*m==1) cout << -1 << endl;
        else {
            if(m!=1) {
            F0R(i, n) {
                int x = v[i][0];
                F0R(j, m-1) {
                    v[i][j]=v[i][j+1];
                }
                v[i].back()=x;
            }
            F0R(i, n) {
                F0R(j, m) cout << v[i][j] << " ";
                cout << endl;
            }
            } else {
                F0R(i, m) {
                    int x = v[0][i];
                    F0R(j, n-1) {
                        v[j][i]=v[j+1][i];
                    }
                    v.back()[i]=x;
                }
                F0R(i, n) {
                    F0R(j, m) cout << v[i][j] << " ";
                    cout << endl;
                } 
            }
        }
    }
    return 0;
}