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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct TreeAlg {
    int n;
    vt<vt<int>> adj;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    TreeAlg(vt<vt<int>> aj, int rt=0) {
        adj=aj;
        root=rt;
        n=aj.size();
        par.resize(n, -1);
        subSize.resize(n, 1);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        trav(x, adj[node]) {
            if(x==par[node]) continue;
            par[x]=node;
            depth[x]=depth[node]+1;
            dfs(x);
            subSize[node]+=subSize[x];
        }
    }
    vt<vt<int>> sparse;
    void set_sparse() {
        sparse.resize(n, vt<int>(20));
        F0R(i, n) sparse[i][0]=par[i];
        FOR(i, 1, 20) {
            F0R(j, n) {
                if(sparse[j][i-1]==-1) sparse[j][i]=-1;
                else sparse[j][i]=sparse[sparse[j][i-1]][i-1];
            }
        }
    }
    int jump(int x, int steps) {
        R0F(i, 20) {
            if(steps&(1<<i)) {
                x=sparse[x][i];
            }
        }
        return x;
    }
    int lca(int x, int y) {
        if(depth[x]>depth[y]) swap(x,y);
        y=jump(y, depth[y]-depth[x]);
        if(x==y) return x;
        R0F(i, 20) {
            if(sparse[x][i]!=sparse[y][i]) {
                x=sparse[x][i];
                y=sparse[y][i];
            }
        }
        return par[x];
    }
    int dist(int x, int y) {
        return depth[x]+depth[y]-2*depth[lca(x,y)];
    }
};
void disable(int u, int v, TreeAlg &t, vt<bool> &active) {
    int x = t.lca(u,v);
    while(u!=x) {
        active[u]=false;
        u=t.par[u];
    }
    active[x]=false;
    while(v!=x) {
        active[v]=false;
        v=t.par[v];
    }
}
array<int,5> dfs(int node, int par, vt<vt<int>> &adj, vt<bool> &active, vt<array<int,3>> &ans, TreeAlg &t) {
    // cout << node << " " << par << active << endl;
    //returns: diameter, first, second, longest path, largest index with that longest path
    if(!active[node]) {
        // cout << "LINE 216 " << endl;
        trav(x, adj[node]) {
            if(x==par) continue;
            dfs(x, node, adj, active, ans, t);
        }
        // cout << "RETURNING -1 FOR " << node << endl;
        return {-1,-1,-1,-1,-1};
    }

    pair<int,int> largest = {-1, -1}, sec = {-1,-1};
    array<int,3> bestFromChild = {-1,-1,-1};  
    if(adj[node].size()==1&&node!=0) {
        // return {1,node,node,1,node};
        bestFromChild = {1,node,node};
        largest = {0, node};
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        auto lol = dfs(x, node, adj, active, ans, t);
        // cout << "LINE 230 " << x << " " << lol << endl;
        // cout << largest << " " << sec << endl;
        bestFromChild = max(bestFromChild, {lol[0],lol[1],lol[2]});
        pair<int,int> pathHere = {lol[3],lol[4]};
        if(largest.f==-1) largest=pathHere;
        else if(sec.f==-1) {
            if(largest<pathHere) {
                sec=largest;
                largest=pathHere;
            } else {
                sec=pathHere;
            }
        }
        else if(largest<pathHere) {
            swap(sec, largest);
            largest=pathHere;
        } else if(sec<pathHere) {
            sec=pathHere;
        }
    }
    // cout << "LINE 250 " << node << " " <<  largest << " " << sec << endl;
    if(largest.f==-1) {
        bestFromChild = {1, node, node};
        largest={0,node};
    } else if(sec.f==-1) {
        bestFromChild = max(bestFromChild, {largest.f+1, max(node, largest.s), min(node, largest.s)});
    } else {
        bestFromChild = max(bestFromChild, {1+largest.f+sec.f, max(largest.s, sec.s), min(largest.s, sec.s)});
    }
    if(par==-1 || !active[par]) {
        // cout << "LINE 249 " << bestFromChild << endl;
        bestFromChild[1]++;
        bestFromChild[2]++;
        ans.add(bestFromChild);
        disable(bestFromChild[1]-1, bestFromChild[2]-1, t, active);
        // cout << "RETURNING -1 FOR " << node << enld;
        return {-1,-1,-1,-1,-1};
    } 
    // cout << "RETURNING " << 
    array<int,5> ret = {bestFromChild[0], bestFromChild[1], bestFromChild[2], largest.f+1, largest.s};
    // cout << "RETURNING " << ret << " FOR " << node << endl;
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> adj(n);
        vt<bool> active(n, true);
        vt<array<int,3>> ans;
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        auto done = [&active, &n]() ->bool{
            F0R(i, n) if(active[i]) return false;
            return true;
        };
        TreeAlg ta(adj);
        ta.set_sparse();
        while (!done()) {
            dfs(0, -1, adj, active, ans, ta);
            // dfs(0, -1, adj, active, ans, ta);
        }
        sort(rbegin(ans),rend(ans));
        // cout << ans << endl;
        trav(x, ans) trav(y, x) cout << y << " ";
        cout << enld;
    }
    return 0;
}