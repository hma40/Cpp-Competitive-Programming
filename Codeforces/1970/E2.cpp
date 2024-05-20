#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
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
vt<vt<int>> mul(vt<vt<int>> a, vt<vt<int>> b) {
    vt<vt<int>> prod(a.size(), vt<int>(b[0].size()));
    F0R(row, a.size()) {
        F0R(col, b[0].size()) {
            F0R(i, b.size()) {
                prod[row][col]+=a[row][i]*b[i][col];
                prod[row][col]%=mod;
            }
        }
    }
    return prod;
}
vt<vt<int>> bexpo(vt<vt<int>> base, int expo) {
    vt<vt<int>> ans(base.size(), vt<int>(base.size()));
    F0R(i, base.size()) ans[i][i]=1;
    while(expo) {
        if(expo%2) {
            ans=mul(ans, base);
        }
        expo/=2;
        base=mul(base, base);
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int m,n;
    cin >> m >> n;
    vt<int> s(m),l(m);
    F0R(i, m) cin >> s[i];
    F0R(i, m) cin >> l[i];
    vt<vt<int>> mt(m, vt<int>(m));
    F0R(i, m) {
        F0R(j, m) {
            mt[i][j]=(s[i]+l[i])*(s[j]+l[j])-l[i]*l[j];
        }
    }
    mt=bexpo(mt, n);
    int ans = 0;
    F0R(i, mt.size()) ans+=mt[0][i];
    ans%=mod;
    cout << ans << endl;
    return 0;
}