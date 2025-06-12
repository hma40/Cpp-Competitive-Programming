#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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
        q.pop_front();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct DSU {
    int n;
    vt<int> par;
    vt<int> sz;
    DSU(int n): n(n), par(n, -1), sz(n, 1){}
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(sz[x]>sz[y]) swap(x,y);
        sz[y]+=sz[x];
        par[x]=y;
    }
};
struct GraphAlgs {
    int n;
    vt<vt<int>> adj;
    vt<int> timer, lowestTimer;
    vt<bool> vis;
    int time;
    set<pair<int,int>> bridges;
    vt<vt<int>> dfs_tree_edges;
    vt<int> eulerPath;
    GraphAlgs(vt<vt<int>> aj) {
        adj=aj;
        n=aj.size();
    }
    void dfs(int node, int par) {   
        vis[node]=true;
        trav(x, adj[node]) {
            if(x==par) continue;
            if(vis[x]) continue;
            dfs_tree_edges[node].add(x);
            dfs_tree_edges[x].add(node);
            dfs(x,node);
        }
    }
    void getDFSTree(int node) {
        vis.assign(n, false);
        dfs_tree_edges.assign(n,vt<int>());
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

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> points;
        map<int,set<int>> row,col;
        map<pair<int,int>,int> ind;
        F0R(i, n) {
            int x,y;
            cin >> x >> y;
            row[x].insert(y);
            col[y].insert(x);
            ind[{x,y}]=i+1;
            points.add({x,y});
        }
        map<int,int> invrow, invcol;
        int nxt = 0;
        vt<vt<int>> adj;
        vt<vt<int>> adj2;
        map<int,int> indToRow, indToCol;
        F0R(i, n) {
            auto x = points[i];
            if(!invrow.count(x.f)) {
                indToRow[nxt]=(x.f);
                invrow[x.f]=nxt++;
                adj.add({});
                adj2.add({});
            } 
            if(!invcol.count(x.s)) {
                indToCol[nxt]=x.s;
                invcol[x.s]=nxt++;
                adj.add({});
                adj2.add({});
            }
            adj[invrow[x.f]].add(invcol[x.s]);
            adj[invcol[x.s]].add(invrow[x.f]);
            adj2[invrow[x.f]].add(i+1);
            adj2[invcol[x.s]].add(i+1);
        }
        GraphAlgs g(adj);
        int odd_deg = 0;
        F0R(i, adj.size()) odd_deg+=adj[i].size()%2;
        if(odd_deg>2) {
            cout << "NO" << endl;
            continue;
        }
        if(odd_deg==0) {
            g.getEulerPath(0);
        } else {
            F0R(i, n) {
                if(adj[i].size()%2) {
                    g.getEulerPath(i);
                    break;
                }
            }
        }
        // cout << adj << endl;
        // cout << indToCol << indToRow << endl;
        vt<int> ans;
        FOR(i, 1, g.eulerPath.size()) {
            if(indToRow.count(g.eulerPath[i-1])) {
                ans.add(ind[{indToRow[g.eulerPath[i-1]], indToCol[g.eulerPath[i]]}]);
            } else {
                ans.add(ind[{indToRow[g.eulerPath[i]], indToCol[g.eulerPath[i-1]]}]);
            }
        }
        if(ans.size()==n) {
            cout << "YES" << enld;
            F0R(i, n) cout << ans[i] << " ";
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}