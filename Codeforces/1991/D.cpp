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
        int n;
        cin >> n;
        if(n==1) {
            cout << 1 << endl << 1 << endl;
            continue;
        } else if(n==2) {
            cout << 2 << endl << "1 2" << endl;
        } else if(n==3) {
            cout << 2 << endl << "1 2 2" << endl;
        } else if(n==4) {
            cout << 3 << endl << "1 2 2 3" << endl;
        } else if(n==5) {
            cout << 3 << endl << "1 2 2 3 3" << endl;
        } else {
            cout << 4 << endl;
            vt<int> colors(n+1);
            FOR(i, 1, n+1) {
                int av = i^2;
                if(av>i) {
                    if(i%2==0) {
                        colors[i]=1;
                    } else {
                        colors[i]=3;
                    }
                    continue;
                }
                if(i%2==0) {
                    if(colors[av]==1) colors[i]=2;
                    else colors[i]=1;
                } else {
                    if(colors[av]==3) colors[i]=4;
                    else colors[i]=3;
                }
            }
            FOR(i, 1, n+1) cout << colors[i] << " ";
            cout << endl;
        }
    }
    return 0;
}