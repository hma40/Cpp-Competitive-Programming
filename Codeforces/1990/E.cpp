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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct TreeAlg {
    int n;
    vt<vt<int>> adj;
    int root;
    vt<int> par;
    vt<int> maxDepth;
    vt<int> depth;
    TreeAlg(vt<vt<int>> aj, int rt=0) {
        adj=aj;
        root=rt;
        n=aj.size();
        par.resize(n, -1);
        maxDepth.resize(n, 0);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        maxDepth[node]=depth[node];
        trav(x, adj[node]) {
            if(x==par[node]) continue;
            par[x]=node;
            depth[x]=depth[node]+1;
            dfs(x);
            maxDepth[node]=max(maxDepth[node], maxDepth[x]);
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
int maxDepth = 0;
int fail = -1;
int queries = 0;
int query(int x) {
    if(queries==300) return -1;
    cout << "? " << x+1 << endl;
    int res;
    queries++;
    cin >> res;
    return res;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> adj(n);
        // reset();
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }

        // dfs(0);
        TreeAlg ta(adj);
        // cout << ta.maxDepth << endl;
        ta.set_sparse();
        // if(ta.maxDepth[0]<=300) {
        //     F0R(i, ta.maxDepth[0]) {
        //         query(0);
        //     }
        //     cout << "! 1" << endl;
        //     continue;
        // }
        int cur = 0;
        int done = -1;
        int minDepth = 0;
        bool weirdChamp = false;
        while(done==-1) {
            vt<pair<int,int>> poss;
            trav(x, adj[cur]) {
                if(x==ta.par[cur]) {
                    continue;
                }
                if(ta.maxDepth[x]<=maxDepth-1) continue;
                poss.add({ta.maxDepth[x], x});
            }
            if(poss.size()==1) {
                cur=poss[0].s;
                continue;
            }
            sort(begin(poss),end(poss));
            int q = query(cur);
            if(q==-1) assert(false);
            if(q==0) {
                done=cur;
                break;
            }      
            minDepth=ta.depth[cur];
            if(poss.size()==0) {
                done=cur;
                weirdChamp = true;
                break;
            }

            F0R(i, poss.size()-1) {
                q=query(poss[poss.size()-i-1].s);
                if(q==-1) assert(false);
                if(q==0) continue;
                cur=poss[poss.size()-1-i].s;
                break;
            }
        }
        int maxDepth = ta.depth[done]-1;
        if(weirdChamp) maxDepth++;
        while(minDepth<maxDepth) {
            int mid = (minDepth+maxDepth+1)/2;
            int up = ta.jump(cur, ta.depth[cur]-ta.depth[mid]);
            int q = query(up);
            if(q==-1) assert(false);
            if(q==0) {
                maxDepth=ta.depth[up]-1;
                minDepth--;
                maxDepth--;
                minDepth=max(0LL,minDepth);
                maxDepth=max(0LL,maxDepth);
            } else {
                minDepth=ta.depth[up];
            }
        }
        cout << "! " << ta.jump(cur, ta.depth[cur]-minDepth)+1 << endl;
    }
    return 0;
}