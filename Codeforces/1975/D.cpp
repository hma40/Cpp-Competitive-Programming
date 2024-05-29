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
vt<vt<int>> adj;
vt<int> depth;
vt<int> par;
vt<int> travDist;
vt<int> endAnywhere, endBack;
void dfs(int n, int p) {
    trav(x, adj[n]) {
        if(x!=p) {
            depth[x]=depth[n]+1;
            par[x]=n;
            dfs(x,n);
        }
    }
}
int jump(int n, int am) {
    if(am==0) return n;
    return jump(par[n], am-1);
}
void dfs2(int n, int p) {
    // cout << "dfs2 called for " << n << " " << p << endl;
    trav(x, adj[n]) {
        if(x!=p) {
            dfs2(x, n);
            endBack[n]+=2;
            endBack[n]+=endBack[x];
        }
    }
    int maxDiff = 0;
    trav(x, adj[n]) {
        if(x!=p) {
            maxDiff=max(maxDiff, endBack[x]-endAnywhere[x]);
        }
    }
    if(endBack[n]!=0) {
        endAnywhere[n]=endBack[n]-maxDiff-1;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        adj.clear();
        depth.clear();
        par.clear();
        endAnywhere.clear();
        endBack.clear();
        endAnywhere.resize(n);
        endBack.resize(n);
        par.resize(n);
        depth.resize(n);
        adj.resize(n);
        int a,b;
        cin >> a >> b;
        a--;b--;
        F0R(i, n-1) {
            int x,y;
            cin >> x >> y;
            adj[x-1].add(y-1);
            adj[y-1].add(x-1);
        }
        dfs(a, -1);
        int ans = (depth[b]+1)/2;
        b=jump(b, (depth[b]+1)/2);
        dfs2(b, -1);
        ans+=endAnywhere[b];
        cout << ans << endl;
    }
    return 0;
}
/*
1
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4
*/