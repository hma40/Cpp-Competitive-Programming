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
#define endl '\n'
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
    vt<int> ans(11);
    FOR(N, 11, 12) {
        cout << N << endl;
        cout.flush();
        vt<vt<int>> all;
        all.add({});
        F0R(i, N) {
            vt<vt<int>> here;
            trav(x, all) {
                vt<bool> exists(N);
                trav(y, x) exists[y]=true;
                F0R(j, N) {
                    if(!exists[j]) {
                        auto tmp = x;
                        tmp.add(j);
                        here.add(tmp);
                    }
                }
            }
            swap(here, all);
        }
        int count = 0;
        set<int> uniq;
        trav(x, all) {
            int val = x[x[0]];
            // cout << x << val << endl;
            bool fail = false;
            // cout << x << " " << val << endl;
            F0R(i, N) {
                // cout << i << " " << (i^x[x[i]]) << endl;
                if((i^x[x[i]])!=val) fail=true; 
            }
            if(!fail) {
                ans[N]++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}