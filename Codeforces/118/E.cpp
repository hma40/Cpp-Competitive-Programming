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
// #define endl "\n"
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
struct GraphAlgs {
    int n;
    vt<vt<int>> adj;
    vt<int> timer, lowestTimer;
    vt<bool> vis;
    int time;
    set<pair<int,int>> bridges;
    vt<int> eulerPath;
    GraphAlgs(vt<vt<int>> aj) {
        adj=aj;
        n=aj.size();
    };
    void bridge_dfs(int v, int p=-1) {
        timer[v]=lowestTimer[v]=time++;
        vis[v]=true;
        trav(x, adj[v]) {
            if(x==p) continue;
            if(vis[x]) {
                lowestTimer[v]=min(lowestTimer[v], timer[x]);
            } else {
                bridge_dfs(x, v);
                lowestTimer[v]=min(lowestTimer[v], lowestTimer[x]);
                if(lowestTimer[x]>timer[v]) {
                    bridges.insert({x,v});
                    bridges.insert({v,x});
                }
            }
        }
    }   
    void getBridges() {
        time=0;
        timer.assign(n, -1);
        lowestTimer.assign(n, -1);
        vis.assign(n, false);
        bridges.clear();
        F0R(i, n) {
            if(!vis[i]) {
                bridge_dfs(i, -1);
            }
        }
    }
    void getEulerPath(int start) {
        vt<set<int>> edges(n);
        F0R(i, n) {
            trav(x, adj[i]) {
                edges[i].insert(x);
            }
        }
        deque<int> dq;
        dq.push_back(start);
        eulerPath.clear();
        while(dq.size()) {
            int z = dq.front();
            if(edges[z].size()) {
                int next = *(edges[z].begin());
                edges[z].erase(next);
                edges[next].erase(z);
                dq.push_front(next);
            } else {
                eulerPath.add(z);
                dq.pop_front();
            }
        }
    }
};
vt<bool> vis;
set<pair<int,int>> used;
set<pair<int,int>> forw,back;
void dfs(int node, int par, vt<vt<int>> &adj) {
    // cout << node << endl;
    vis[node]=true;
    trav(x, adj[node]) {
        if(used.count({min(x,node),max(x,node)})) continue;
        used.insert({min(x,node),max(x,node)});
        if(x==par) continue;
        if(vis[x]) {
            back.insert({node,x});
            continue;
        }   
        forw.insert({node,x});
        dfs(x,node,adj);
    }
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vt<vt<int>> adj(n);
    vis.resize(n);
    // cout << vis << endl;
    F0R(i, m) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].add(b);
        adj[b].add(a);
    }
    GraphAlgs g(adj);
    g.getBridges();
    if(g.bridges.size()) {
        cout << "0" << endl;
        return 0;
    }
    
    // trav(x, forw) {
        // back.erase({x.f,x.s});
    // }
    dfs(0,-1,adj);
    // cout << forw << back << endl;
    trav(x, forw) cout << 1+x.f << " " << 1+x.s << endl;
    trav(x, back) cout << 1+x.f << " " << 1+x.s << endl;
    return 0;
}