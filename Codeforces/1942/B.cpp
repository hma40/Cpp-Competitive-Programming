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
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        F0R(i, n) cin >> a[i];
        set<int> unused;
        F0R(i, n) unused.insert(i);
        vector<int> orig(n);
        F0R(i, n-1) {
            int start = *unused.begin();
            int second = *(++unused.begin());
            if(a[i]<0) {
                orig[i]=start-a[i];
                unused.erase(orig[i]);
            } else {
                orig[i]=start;
                unused.erase(start);
            }
        }
        orig.back()=*unused.begin();
        cout << orig[0];
        FOR(i, 1, n) cout << " " << orig[i];
        cout << endl;
    }
    return 0;
}