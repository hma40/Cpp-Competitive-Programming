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
    int n;
    cin >> n;
    vt<int> a(n);
    int mxx = 0;
    F0R(i, n) cin >> a[i];
    int MAXA = 2e5;
    F0R(i, n) mxx=max(mxx, a[i]);
    vt<int> mult(n);
    mult[0]=1;
    F0R(i, n-1) {
        if(a[i]<a[i+1]) {
            mult[i]--;
            mult[i+1]++;
        } 
    }
    // cout << mult << endl;
    vt<int> totalMult(MAXA);
    // assert(false);
    F0R(i, n) totalMult[a[i]]+=mult[i];
    // assert(false);
    vt<int> pref(MAXA+2);
    F0R(i, MAXA-1) pref[i+1]=pref[i]+totalMult[i];
    // assert(false);
    // cout << totalMult << endl;
    // cout << pref << endl;
    vt<int> ans(mxx+1);
    FOR(i, 1, mxx+1) {
        for(int j = i; j<mxx+i; j+=i) {
            int beg = j-i+1, end = j;
            ans[i]+=j/i*(pref[end+1]-pref[beg]);
            // cout << i << " " << j << " " << ans[i] << endl;
        }
    }
    // cout << ans << endl;
    F0R(i, mxx) cout << ans[i+1] << " ";
    cout << endl;
    return 0;
}