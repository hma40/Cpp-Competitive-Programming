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
int n,m,c;
vt<vt<int>> adj;
int solve(int i, int j) {
    int pathsAdded = 0;
    vector<bool> hasp(n);
    trav(x, adj[i]) hasp[x]=true;
    if(!hasp[j]) {
        pathsAdded=1;
    }
    deque<int> q;
    q.add(j);
    vector<bool> vis(n);
    vis[j]=true;
    int compj = 0;
    int compi = 0;
    while(q.size()) {
        auto x = q.front();
        q.pop_front();
        compj++;
        trav(y, adj[x]) {
            if(x==j) {
                if(y!=i) {
                    vis[y]=true;
                    q.add(x);
                }
            } else {
                if(y==i) return inf;
                if(vis[y]) continue;
                vis[y]=true;
                q.add(y);
            }
        }
    }
    trav(x, adj[i]) {
        if(x!=j) q.add(x);
    }
    while(q.size()) {
        int x = q.front();
        q.pop_front();
        compi++;
        trav(y, adj[x]) {
            if(vis[y]) continue;
            vis[y]=true;
            q.add(y);
        }
    }
    
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> m >> c;
        adj.clear();
        adj.resize(n);
        F0R(i, m) {
            int a,b;
            cin >> a >> b;
            adj[--a].add(--b);
            adj[b].add(a);
        }
        int ans = inf;
        F0R(i, n) {
            FOR(j, i+1, n) {
                ans=min(ans, solve(i,j));
            }
        }
    }
    return 0;
}