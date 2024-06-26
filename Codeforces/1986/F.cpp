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
    GraphAlgs(vt<vt<int>> adj): adj(adj), n(adj.size()) {};
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
};
vt<int> val;
vt<vt<int>> newadj;
void dfs(int node=0, int par=-1) {
    trav(x, newadj[node]) {
        if(x!=par) {
            dfs(x, node);
            val[node]+=val[x];
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<vt<int>> adj(n);
        F0R(i, m) {
            int x,y;
            cin >> x >> y;
            adj[x-1].add(y-1);
            adj[y-1].add(x-1);
        }
        // cout << adj << endl;
        GraphAlgs g(adj);
        // assert(false);
        g.getBridges();
        int ans = n*(n-1)/2;
        int nodes = 0;

        vt<bool> vis(n);
        vt<int> which(n, -1);
        vt<vt<int>> clumps;
        F0R(i, n) {
            if(vis[i]) continue;
            vis[i]=true;
            // cout << i << endl;
            which[i]=nodes;
            vt<int> clump;
            clump.add(i);
            deque<int> dq;
            dq.push_back(i);
            while(dq.size()) {
                int fr = dq.front();
                dq.pop_front();
                trav(x, adj[fr]) {
                    if(vis[x]) continue;
                    if(!g.bridges.count({x, fr})) {
                        vis[x]=true;
                        which[x]=nodes;
                        clump.add(x);
                        dq.push_back(x);
                    }
                }
            }
            clumps.add(clump);
            nodes++;
        }
        newadj.assign(nodes, {});
        // cout << clumps << which << endl;
        while(g.bridges.size()) {
            auto first = *g.bridges.begin();
            // cout << first << endl;
            g.bridges.erase(first);
            g.bridges.erase({first.s, first.f});
            newadj[which[first.f]].add(which[first.s]);
            newadj[which[first.s]].add(which[first.f]);
        }
        // cout << newadj << endl;
        val.assign(nodes, 0);
        F0R(i, nodes) val[i]=clumps[i].size();
        dfs();
        trav(x, val) {
            ans=min(ans, x*(x-1)/2+(n-x)*(n-x-1)/2);
        }
        cout << ans << endl;
    }
    return 0;
}