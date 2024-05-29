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
    vt<int> a(n), b(n);
    vt<int> indeg(n);
    F0R(i, n) {
        cin >> a[i];
    }
    F0R(i, n) {
        cin >> b[i];
        b[i]--;
        indeg[b[i]]++;
    }
    // cout << indeg << endl;
    vt<int> topo;
    vt<bool> vis(n);
    deque<int> q;
    F0R(i, n) {
        if(indeg[i]==0) {
            topo.add(i);
            vis[i]=true;
            q.push_back(i);
        }
    }
    while(q.size()) {
        int x = q.front();
        // cout << x << " " << b[x] << endl;
        q.pop_front();
        if(b[x]>=0) {
            indeg[b[x]]--;
            if(indeg[b[x]]==0&&!vis[b[x]]) {
                vis[b[x]]=true;
                // cout << "ADDING " << b[x] << endl;
                topo.add(b[x]);
                q.push_back(b[x]);
            }
        }
    }
    // cout << topo << endl;
    deque<int> bad;
    vt<int> order;
    int ans = 0;
    trav(x, topo) {
        ans+=a[x];
        if(a[x]>=0) {
            order.add(x);
            a[b[x]]+=a[x];
        } else {
            bad.push_front(x);
        }
    }
    while(bad.size()) {
        order.add(bad.front());
        bad.pop_front();
    }
    cout << ans << endl << 1+order[0];
    FOR(i, 1, n) cout << " " << 1+order[i];
    cout << endl;
    return 0;
}