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
    //1110
    //110 1010 1100 1110
    //10111
    //111 10011 10101 10110 10111
    //11
    //11 10 1
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        if(n==1) {
            cout << "1\n1\n";
            continue;
        }
        vt<int> backwards;
        backwards.add(n);
        F0R(i, 62) {
            if(n&(1LL<<i)) {
                backwards.add(n^(1LL<<i));
            }
        }
        if(backwards.back()==0) backwards.pop_back();
        // cout << backwards << endl;
        cout << backwards.size() << endl;
        R0F(i, backwards.size()) {
            cout << backwards[i] << " ";
            if(i!=backwards.size()-1) {
                assert((backwards[i]|backwards[i+1])==n);
            }
        }
        cout << endl;
    }
    return 0;
}