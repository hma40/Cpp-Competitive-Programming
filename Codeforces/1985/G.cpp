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
int binExp(int base, int pow) {
    int ans = 1;
    while(pow) {
        if(pow%2) {ans*=base;ans%=mod;}
        base*=base;
        base%=mod;
        pow/=2;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    int inv6 = binExp(6, mod-2);
    int inv2 = binExp(2, mod-2);
    while(t--) {
        int l,r,k;
        cin >> l >> r >> k;
        if(k>=10) {
            cout << 0 << endl;
            continue;
        }
        // int ans = 0;
        int numPer = 9/k;
        int ans = binExp(numPer+1, r)-binExp(numPer+1, l);
        ans%=mod;
        ans+=mod;
        ans%=mod;
        cout << ans << endl;
    }
    return 0;
}