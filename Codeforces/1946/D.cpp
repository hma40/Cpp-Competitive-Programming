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
vt<int> v;
int solve(vt<int> reqs) {
    int ans = 0;
    int curX = 0;
    R0F(i, v.size()) {
        curX^=v[i];
        bool good = true;
        trav(x, reqs) {
            if(curX&(1<<x)) {
                good=false;
            }
        }
        if(good) {
            ans++;
            curX=0;
        }
    }
    if(curX==0) return ans;
    else return -1;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,x;
        cin >> n >> x;
        v.assign(n,0);
        F0R(i, n) cin >>v[i];
        vt<int> reqs;
        int ans = -1;
        R0F(i, 31) {
            if(x&(1<<i)) {
                reqs.add(i);
                ans=max(ans, solve(reqs));
                reqs.pop_back();
            } else {
                reqs.add(i);
            }
        }
        ans=max(ans, solve(reqs));
        cout << ans << endl;
    }
    return 0;
}