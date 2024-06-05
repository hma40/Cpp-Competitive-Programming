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
    int n,m;
    cin >> n >> m;
    vt<vt<int>> z(n, vt<int>(m)), y(n, vt<int>(m));
    int nextNum = 1;
    bool backwards = true;
    R0F(i, n) {
        if(backwards) {
            R0F(j, m) {
                z[i][j]=nextNum++;
            }
        } else {
            F0R(j, m) {
                z[i][j]=nextNum++;
            }
        }
        backwards=!backwards;
    }
    nextNum=1;
    backwards=false;
    F0R(i, m) {
        if(backwards) {
            R0F(j, n) {
                y[j][i]=nextNum++;
            }
        } else {
            F0R(j, n) {
                y[j][i]=nextNum++;
            }
        }
        backwards=!backwards;
    }
    set<int> all;
    F0R(i, n) {
        F0R(j, m) {
            if(z[i][j]==y[i][j]) all.insert(z[i][j]);
        }
    }
    cout << all.size() << endl;
    while(all.size()) {
        cout << *all.begin() << endl;
        all.erase(*all.begin());
    }
    return 0;
}