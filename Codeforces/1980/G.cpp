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
// #define int long long
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
struct BinaryTrie {
    int next;
    vt<int> leftChild, rightChild;
    vt<int> last;
    BinaryTrie(int maxNodes) {
        leftChild.assign(32*maxNodes, -1);
        rightChild.assign(32*maxNodes, -1);
        next = 1;
        last.assign(32*maxNodes,-2);
    }  
    int maxXOR(int x, int avoid) {
        // cout << "LINE 63 " << x <<  endl;
        int cur = 0;
        int val = 0;
        // if(last[0].size()==1&&*(last[0].begin())==avoid) return 0;
        if(last[0]==avoid) return 0;
        R0F(i, 31) {
            // cout << i << " " << val << " " << x << endl;
            assert(leftChild[cur]!=-1||rightChild[cur]!=-1);
            if(x&(1<<i)) {
                if(leftChild[cur]!=-1&&last[leftChild[cur]]!=avoid) {
                    cur=leftChild[cur];
                } else {
                    cur=rightChild[cur];
                    val^=(1<<i);
                }
            } else {
                if(rightChild[cur]!=-1&&last[rightChild[cur]]!=avoid) {
                    cur=rightChild[cur];
                    val^=(1<<i);
                } else {
                    cur=leftChild[cur];
                }
            }
        }
        return x^val;
    }
    void insert(int x, int pos) {
        // cout << "LINE 86 " << x << endl;
        int cur = 0;
        if(last[0]==-2) last[0]=pos;
        else last[0]=-1;
        R0F(i, 31) {
            if(x&(1<<i)) {
                if(rightChild[cur]==-1) {
                    rightChild[cur]=next++;
                }
                cur=rightChild[cur];
            } else {
                if(leftChild[cur]==-1) {
                    leftChild[cur]=next++;
                }
                cur=leftChild[cur];
            }
            if(last[cur]==-2) {
                last[cur]=pos;
            } else {
                last[cur]=-1;
            }
        }
    }
};
struct TreeAlg {
    int n;
    vt<vt<pair<int,int>>> adj;
    vt<int> xr;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    TreeAlg(vt<vt<pair<int,int>>> aj, int rt) {
        adj=aj;
        root=rt;
        n=aj.size();
        xr.assign(n,0);
        par.resize(n, -1);
        // subSize.resize(n, 1);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        trav(x, adj[node]) {
            if(x.f==par[node]) continue;
            par[x.f]=node;
            depth[x.f]=depth[node]+1;
            xr[x.f]=xr[node]^x.s;
            dfs(x.f);
            // subSize[node]+=subSize[x.f];
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<vt<pair<int,int>>> adj(n);
        F0R(i, n-1) {
            int a,b,c;
            cin >> a >> b >> c;
            adj[--a].add({--b,c});
            adj[b].add({a,c});
        }
        int od=0, ev=0;
        TreeAlg ta(adj,0);
        F0R(i, n) if(ta.depth[i]%2) od++; else ev++;
        BinaryTrie odd(od+1),even(ev+1);
        F0R(i, n) {
            if(ta.depth[i]%2) {
                odd.insert(ta.xr[i], i);
            } else {
                even.insert(ta.xr[i], i);
            }
        }
        int oddXOR = 0;
        while(m--) {
            char c;
            cin >> c;
            if(c=='^') {
                int y;
                cin >> y;
                oddXOR^=y;
            } else {
                int v,x;
                cin >> v >> x;
                v--;
                // cout << v << " " << x << " " << ta.xr[v] << endl;
                if(ta.depth[v]%2) x^=oddXOR;
                int ans = max(even.maxXOR(x^ta.xr[v], v), odd.maxXOR(x^ta.xr[v]^oddXOR, v));
                cout << ans << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}