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
    while(t-- ){
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i,n) cin >> v[i];
        int ops = 0;
        pair<int,int> last = {-1,-1};
        F0R(i, n) {
            if(last.f==-1) {
                if(v[i]==0) {
                    continue;
                }
                if(v[i]<=2) {
                    ops++;
                    last={0,1};
                } else {
                    ops++;
                    last={-1,-1};
                }
            } else {
                int actual = v[i];
                if(last.f<v[i]) actual--;
                if(last.s<v[i]) actual--;
                if(actual==0) {
                    last={-1,-1};
                    continue;
                } else if(actual<=2) {
                    ops++;
                    if(last.f==0) {
                        last={2,3};
                    } else {
                        last={0,1};
                    }
                } else {
                    ops++;
                    last={-1,-1};
                }
            }
        }
        cout << ops << endl;
    }
    return 0;
}