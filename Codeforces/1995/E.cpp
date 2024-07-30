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
        vt<int> v(2*n);
        F0R(i, 2*n) cin >> v[i];
        if(n%2==0) {
            vt<int> noSwap(n),swap(n);
            F0R(i, n) {
                noSwap[i]=v[2*i]+v[2*i+1];
                swap[i]=v[2*i]+v[(2*i+1+n)%(2*n)];
            }
            // cout << swap << noSwap << endl;
            int mx = 0, mn = inf;
            FOR(i, n/2, n) {
                if(min(swap[i-n/2], swap[i])<min(noSwap[i-n/2], noSwap[i])) {
                    //use noswap
                    mx=max(mx,max(noSwap[i-n/2], noSwap[i]));
                    mn=min(mn, min(noSwap[i-n/2], noSwap[i]));
                } else {
                    mx=max(mx,max(swap[i-n/2], swap[i]));
                    mn=min(mn, min(swap[i-n/2], swap[i]));
                }
            }
            cout << mx-mn << endl;
        } else {

        }
    }
    return 0;
}
/*
1 2 3 4 5 6 7 8
*/