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
template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
struct DirectedGraph {
    vt<vt<int>> adj;
    int n;
    vt<vt<int>> invAdj;
    vt<int> topo;
    // vt<vt<int>> scc;
    stack<int> order;
    vt<bool> vis;
    vt<int> comp;
    vt<vt<int>> components;
    void dfs1(int x) {
        vis[x]=true;
        trav(y, adj[x]) {
            if(!vis[y]) dfs1(y);
        }
        order.push(x);
    }
    void dfs2(int x) {
        comp[x]=components.size()-1;
        // cout << x << " " << comp[x] << endl;
        components[comp[x]].add(x);
        vis[x]=true;
        trav(y, invAdj[x]) {
            if(!vis[y]) {
                dfs2(y);
            }
        }
    }
    DirectedGraph(vt<vt<int>> aj) {
        adj=aj;
        n=aj.size();
    }
    bool TopoSort() {
        topo.clear();
        vt<int> inDeg(n);
        F0R(i, n) {
            trav(x, adj[i]) inDeg[x]++;
        }
        queue<int> dq;
        F0R(i, n) {
            if(inDeg[i]==0) {
                dq.push(i);
                topo.add(i);
            }
        }
        while(dq.size()) {
            int f = dq.front();
            dq.pop();
            trav(x, adj[f]) {
                inDeg[x]--;
                if(inDeg[x]==0) {
                    dq.push(x);
                    topo.add(x);
                }
            }
        }
        return topo.size()==n;
    }
    void getSCC() {
        vis.assign(n, false);
        // order.empty();
        while(order.size()) order.pop();
        invAdj.assign(n, vt<int>());
        comp.assign(n, -1);
        F0R(i, n) {
            // cout << i << endl;
            trav(x, adj[i]) {
                invAdj[x].add(i);
            }
        }
        F0R(i, n) {
            // cout << i << endl;
            if(!vis[i]) dfs1(i);
        }
        vis.assign(n, false);
        while(order.size()) {
            int v = order.top();
            // cout << v << endl;
            order.pop();
            if(!vis[v]) {
                components.add({});
                dfs2(v);
            }
        }
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> v(3, vt<int>(n));
        F0R(i, 3) {
            F0R(j, n) cin >> v[i][j];
        }
        map<int,int> mp;
        int next = 0;
        FOR(i, -n, n+1) {
            if(i==0) continue;
            mp[i]=next++;
        }
        vt<vt<int>> adj(next);
        F0R(i, n) {
            adj[mp[-v[0][i]]].add(mp[v[1][i]]);
            adj[mp[-v[0][i]]].add(mp[v[2][i]]);
            adj[mp[-v[1][i]]].add(mp[v[0][i]]);
            adj[mp[-v[1][i]]].add(mp[v[2][i]]);
            adj[mp[-v[2][i]]].add(mp[v[1][i]]);
            adj[mp[-v[2][i]]].add(mp[v[0][i]]);
        }
        DirectedGraph dg(adj);
        dg.getSCC();
        bool bad = false;
        FOR(i, 1, n+1) {
            if(dg.comp[mp[i]]==dg.comp[mp[-i]]) {
                bad=true;
            }
        }
        if(bad) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}