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
vector<vector<int>> adj;
vector<int> par, sz;
int n,m,c;
int dfs(int node=0) {
    int ans = inf;
    trav(x, adj[node]) {
        if(x!=par[node]) {
            par[x]=node;
            ans=min(ans, dfs(x));
            sz[node]+=sz[x];
        }
    }
    if(node!=0) {
        ans=min(ans, sz[node]*sz[node]+(n-sz[node])*(n-sz[node]));
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> m >> c;
        adj.clear();
        par.clear();
        sz.clear();
        adj.resize(n);
        par.resize(n);
        sz.resize(n, 1);
        FOR(i, 1, n) {
            int a,b;
            cin >> a >> b;
            adj[--a].add(--b);
            adj[b].add(a);
        }
        par[0]=-1;
        cout << dfs() << endl;
    }
    return 0;
}
