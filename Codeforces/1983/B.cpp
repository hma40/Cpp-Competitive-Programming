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
        int n,m;
        cin >> n >> m;
        // cout << n << " " << m << endl;
        // cout.flush();
        vt<string> a(n),b(n);
        int asum = 0;
        F0R(i,n) {
            cin >> a[i];
        }

        F0R(i, n) {
            cin >> b[i];
        }
        vt<vt<int>> aa(n, vt<int>(m)), bb(n, vt<int>(m));
        F0R(i, n) {
            F0R(j, m) {
                aa[i][j]=a[i][j]-'0';
                bb[i][j]=b[i][j]-'0';
            }
        }
        bool fail = false;
        F0R(i, n) {
            F0R(j, m) {
                int changes = bb[i][j]-aa[i][j];
                if(changes<0) changes+=3;
                if(i==n-1||j==m-1) {
                    if(changes!=0) {
                        fail=true;
                        continue;
                    } else {
                        continue;
                    }
                }
                aa[i][j]+=changes;
                aa[i+1][j+1]+=changes;
                aa[i+1][j]+=2*changes;
                aa[i][j+1]+=2*changes;
                aa[i][j]%=3;
                aa[i+1][j+1]%=3;
                aa[i+1][j]%=3;
                aa[i][j+1]%=3;
            }
        }
        if(fail) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}