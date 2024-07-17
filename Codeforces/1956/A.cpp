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
ll mod = 1000000007;
ll inf = 1e15;
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
    int t;
    cin >> t;
    while(t--) {
        int k,q;
        cin >> k >> q;
        vector<int> a(k), ans(q);
        F0R(i, k) cin >> a[i];
        F0R(i, k) a[i]--;
        reverse(begin(a),end(a));
        F0R(j, q) {
            int x;
            cin >> x;
            vector<int> exist(x);
            while(true) {
                int del = 0;
                trav(y, a) {
                    if(exist.size()>y) {
                        del++;
                        exist.erase(exist.begin()+y);
                    }
                }
                if(del==0) break;
            }
            ans[j]=exist.size();
        }
        cout << ans[0];
        FOR(i, 1, q) cout << " " << ans[i];
        cout << endl;
    }
    return 0;
}