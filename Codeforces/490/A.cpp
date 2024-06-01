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
    int n;
    cin >> n;
    set<int> z,o,t;
    F0R(i, n) {
        int x;
        cin >> x;
        if(x==2) z.insert(1+i);
        else if(x==1) o.insert(1+i);
        else t.insert(i+1);
    }
    // cout << z << o << t << endl;
    cout << min(min(z.size(), o.size()), t.size()) << endl;
    while(z.size()&&o.size()&&t.size()) {
        cout << *z.rbegin() << " " <<*o.rbegin() << " " << *t.rbegin() << endl;
        z.erase(*z.rbegin());
        o.erase(*o.rbegin());
        t.erase(*t.rbegin());
    }
    return 0;
}