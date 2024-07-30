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
struct GraphAlgs {
    int n;
    vt<vt<int>> adj;
    vt<int> timer, lowestTimer;
    vt<bool> vis;
    int time;
    set<pair<int,int>> bridges;
    vt<vt<int>> dfs_tree_edges;
    vt<int> eulerPath;
    vt<pair<int,int>> weNeed;
    vt<int> deg;
    GraphAlgs(vt<vt<int>> aj) {
        adj=aj;
        n=aj.size();
    }
    void dfs(int node, int par) {   
        // cout << node << endl;
        // int ans = deg[node];
        vis[node]=true;
        // if(par==-1&&adj[node].size()) ans++;
        trav(x, adj[node]) {
            if(x==par) continue;
            if(vis[x]) continue;
            dfs_tree_edges[node].add(x);
            dfs_tree_edges[x].add(node);
            deg[node]++;
            deg[x]++;
            dfs(x,node);
        }
        // return ans;
    }
    int dfs3(int node, int par) {
        int ans = deg[node];
        trav(x, dfs_tree_edges[node]) {
            if(x==par) continue;
            ans+=dfs3(x, node);
        }
        return ans;
    }
    void dfs2(int node, int par) {
        // cout << "LINE 85 " << node << " " << par << endl;
        trav(x, dfs_tree_edges[node]) {
            // cout << node << " " << x << endl;
            if(x==par) continue;
            dfs2(x,node);
        }
        // cout << "LINE 91 " << node << " " << par << endl;
        if(par==-1) return;
        if(deg[node]%2==0) {
            weNeed.add({node,par});
        } else {
            deg[node]--;
            deg[par]--;
        }
    }
    void getDFSTree(int node) {
        vis.assign(n, false);
        dfs_tree_edges.assign(n, vt<int>());
        dfs(node,-1);
    }
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
        vt<multiset<int>> edges(n);
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
                edges[z].erase(edges[z].find(next));
                edges[next].erase(edges[next].find(z));
                dq.push_front(next);
            } else {
                eulerPath.add(z);
                dq.pop_front();
            }
        }
    }
};
// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<int> deg(n);
        int edges = 0;
        vt<vt<int>> npc(n),adj(n);
        F0R(i, m) {
            int u,v,x;
            cin >> u >> v >> x;
            u--;
            v--;
            // cout << u << " " <<endl;
            if(x==0) {
                adj[u].add(v);
                adj[v].add(u);
            } else {
                edges++;
                deg[u]++;
                deg[v]++;
                npc[u].add(v);
                npc[v].add(u);
            }
        }
        GraphAlgs g(adj);
        g.dfs_tree_edges.assign(n, vt<int>());
        // cout << g.adj << endl;
        g.vis.assign(n,false);
        g.deg=deg;
        bool fail = false;
        F0R(i, n) {
            if(!g.vis[i]) {
                g.dfs(i,-1);
                int sum = g.dfs3(i,-1);
                // cout << i << " " << sum << endl;
                if(sum%2) {
                    fail=true;
                    break;
                }
                g.dfs2(i,-1);
                // cout << g.weNeed << endl;
                trav(x, g.weNeed) {
                    npc[x.f].add(x.s);
                    npc[x.s].add(x.f);
                    edges++;
                }
                g.weNeed.clear();
            }
        }
        // assert(edges<=m);
        if(fail) cout << "NO" << endl;
        else {
            g.adj=npc;
            g.getEulerPath(0);
            // cout << g.eulerPath << endl;
            cout << "YES" << endl << g.eulerPath.size()-1 << endl;
            trav(x, g.eulerPath) cout << x+1 << " ";
            cout << endl;
        }
    }
    return 0;
}
/*
1
3 5
3 1 1
2 1 0
2 1 1
1 2 1
2 3 1
*/