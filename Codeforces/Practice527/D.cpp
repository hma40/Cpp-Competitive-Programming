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
        vt<string> v(n);
        F0R(i, n) cin >> v[i];
        bool fail = false;
        vt<vt<char>> ans(n, vt<char>(m, '.'));
        F0R(i, n) {
            int count = 0;
            F0R(j, m) {
                if(v[i][j]=='U') {
                    count++;
                    if(count%2) {
                        ans[i][j]='B';
                        ans[i+1][j]='W';
                    } else {
                        ans[i][j]='W';
                        ans[i+1][j]='B';
                    }
                }
            }
            if(count%2) fail=true;
        }
        F0R(j, m) {
            int count = 0;
            F0R(i, n) {
                if(v[i][j]=='L') {
                    count++;
                    if(count%2) {
                        ans[i][j]='B';
                        ans[i][j+1]='W';
                    } else {
                        ans[i][j]='W';
                        ans[i][j+1]='B';
                    }
                }
            }
            if(count%2) fail=true;
        }
        if(fail) {
            cout << "-1" << endl; 
        } else {
            F0R(i, n) {
                F0R(j, m) cout << ans[i][j];
                cout << endl;
            }
        }
    }
    return 0;
}