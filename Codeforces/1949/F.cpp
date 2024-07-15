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
    int n,m;
    cin >> n >> m;
    vt<set<int>> v(n);
    F0R(i, n) {
        int k;
        cin >> k;
        while(k--) {
            int x;
            cin >> x;
            v[i].insert(x);
        }
    }
    vt<pair<int,int>> w;
    F0R(i, n) w.add({-v[i].size(), i});
    sort(begin(w),end(w));
    vt<int> lastSeen(m+1, -1);
    trav(x, w) {
        // cout << x << lastSeen << endl;
        set<pair<int,int>> ancestors;
        trav(y, v[x.s]) {
            if(lastSeen[y]==-1) ancestors.insert({-1,-1});
            else ancestors.insert({v[lastSeen[y]].size(), lastSeen[y]});
        }
        if(ancestors.size()>1) {
            if((*ancestors.begin()).f==-1) {
                ancestors.erase({-1,-1});
                cout << "YES" << endl << x.s+1 << " " << (*ancestors.begin()).s+1 << endl;
                return 0;
            } else {
                cout << "YES" << endl << x.s+1 << " " << (*ancestors.begin()).s+1 << endl;
                return 0;
            }
        } else {
            trav(y, v[x.s]) lastSeen[y]=x.s;
        }
    }
    cout << "NO" << endl;
    return 0;
}