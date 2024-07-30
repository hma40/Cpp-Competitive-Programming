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
    int edgesRemoved(int ty, int node, vt<int> &copySub) {
        int ans = 0;
        trav(x, adj[node]) {
            if(x==par[node]) continue;
            ans+=edgesRemoved(ty,x,copySub);
        }
        // cout << ty << " " << node << " " <<  ans << " " << copySub << endl;
        if(node!=0) {
            copySub[par[node]]-=subSize[node]-copySub[node];
        }
        if(copySub[node]>=ty) {
            if(node!=0) {
                copySub[par[node]]-=copySub[node];
                return ans+1;
            } else {
                return ans;
            }
        } else if(node==0) {
            return ans-1;
        } else {
            return ans;
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<vt<int>> adj(n);
        F0R(i, n-1) {
            int a,b;
            cin >> a >> b;
            adj[--a].add(--b);
            adj[b].add(a);
        }
        TreeAlg ta(adj);
        int lo = 1, hi = n;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            vt<int> copy = ta.subSize;
            if(ta.edgesRemoved(mid, 0,copy)>=k) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}