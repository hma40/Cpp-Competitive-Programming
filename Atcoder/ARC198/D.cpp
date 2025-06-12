#ifdef ONLINE_JUDGE
#include <bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops,inline")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
struct TreeAlg {
    vt<vt<int>> jmp;
    vt<int> par;
    vt<vt<int>> l;
    vt<int> depth;
    vt<vt<int>> adj;
    void dfs(int node, int p) {
        trav(x, adj[node]) {
            if(x==p) continue;    
            depth[x]=depth[node]+1;
            par[x]=node;
            dfs(x, node);
        }
    }
    TreeAlg(vt<vt<int>> &adja): adj(adja) {
        int n = adja.size();
        par.resize(n,-1);
        jmp.resize(n, vt<int>(n));
        l.resize(n,vt<int>(n,-1));
        depth.resize(n);
        dfs(0,-1);
        F0R(i, n) {
            jmp[i][0]=i;
            FOR(j, 1, n) {
                if(jmp[i][j-1]==-1) jmp[i][j]=-1;
                else jmp[i][j]=par[jmp[i][j-1]];
            }
        }
    }
    int lca(int u, int v) {
        int tmpu = u, tmpv = v;
        if(l[u][v]!=-1) return l[u][v];
        if(depth[u]>depth[v]) u=jump(u, depth[u]-depth[v]);
        if(depth[v]>depth[u]) v=jump(v, depth[v]-depth[u]);
        if(u==v) {
            return l[tmpu][tmpv]=u;
        } else {
            return l[tmpu][tmpv]=lca(par[u], par[v]);
        }
    }
    int dist(int u, int v) {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
    int jump(int u, int steps) {
        return jmp[u][steps];
    }
};
struct DSU {
    vt<int> par, sz;
    DSU(int n) {
        par.resize(n, -1);
        sz.resize(n,1);
    }
    int find(int u) {
        if(par[u]==-1) return u;
        return par[u]=find(par[u]);
    }
    void unite(int u, int v) {
        u=find(u);
        v=find(v);
        if(u==v) return;
        if(sz[u]>sz[v]) swap(u,v);
        sz[v]+=sz[u];
        par[u]=v;
    }
};
void dfs(int u, int v, TreeAlg& ta, DSU &d, vt<vt<bool>> &done) {
    if(u>v) swap(u,v);
    if(done[u][v]) return;

    done[u][v]=true;
    d.unite(u,v);
    if(ta.dist(u,v)<=1) return;
    int dist = ta.dist(u,v);
    if(ta.lca(u,v)==u) {
        dfs(ta.jump(v, dist-1), ta.par[v], ta, d, done);
    } else if(ta.lca(u,v)==v) {
        dfs(ta.jump(u, dist-1), ta.par[u], ta, d, done);
    } else {
        dfs(ta.par[u], ta.par[v], ta, d, done);
    }
}
bool dfs_2(int u, int v, TreeAlg &ta, vt<int> &seq, vt<vt<bool>> &done2, vt<vt<bool>> &isPali) {
    if(u>v) swap(u,v);
    if(done2[u][v]) return isPali[u][v];
    int dist = ta.dist(u,v);
    if(dist<=1) {
        if(seq[u]==seq[v]) {
            done2[u][v]=true;
            isPali[u][v]=true;
            return true;
        } else {
            done2[u][v]=true;
            isPali[u][v]=false;
            return false;
        }
    }
    if(seq[u]!=seq[v]) {
        done2[u][v]=true;
        isPali[u][v]=false;
        return false;
    }
    done2[u][v]=true;
    if(ta.lca(u,v)==u) {
        return isPali[u][v]=dfs_2(ta.jump(v, dist-1), ta.par[v], ta, seq, done2, isPali);
    } else if(ta.lca(u,v)==v) {
        return isPali[u][v]=dfs_2(ta.jump(u, dist-1), ta.par[u], ta, seq, done2, isPali);
    } else {
        return isPali[u][v]=dfs_2(ta.par[u], ta.par[v], ta, seq, done2, isPali);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n;
    cin >> n;
    vt<vt<int>> adj(n);
    F0R(i, n-1) {
        int u,v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].add(v);
        adj[v].add(u);
    }
    TreeAlg ta(adj);
    vt<string> v(n);
    F0R(i, n) cin >> v[i];
    DSU d(n);
    vt<vt<bool>> done(n,vt<bool>(n,false));
    F0R(i, n) {
        FOR(j, i, n) {
            if(v[i][j]=='1') dfs(i,j,ta,d,done);
        }
    }
    vt<int> seq(n);
    int nxt = 1;
    F0R(i, n) {
        // cout << i << seq << endl;
        if(seq[i]!=0) continue;
        seq[i]=nxt++;
        FOR(j, i+1, n) if(d.find(j)==d.find(i)) seq[j]=seq[i];
    }
    int ans = n;
    vt<vt<bool>> done2(n, vt<bool>(n)), isPali(n, vt<bool>(n));
    F0R(i, n) {
        FOR(j, i+1, n) {
            ans+=2*dfs_2(i, j, ta, seq, done2, isPali);
        }
    }
    cout << ans << endl; 
    // cout << seq << endl;
    return 0;
}