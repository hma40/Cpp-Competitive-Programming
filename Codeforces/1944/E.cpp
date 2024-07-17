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
struct TreeAlg {
    int n;
    vt<vt<int>> adj;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    vt<int> maxDepth;
    TreeAlg(vt<vt<int>> aj, int rt) {
        adj=aj;
        root=rt;
        n=aj.size();
        par.resize(n, -1);
        subSize.resize(n, 1);
        depth.resize(n, 0);
        maxDepth.resize(n,0);
        dfs(root);
    }
    void dfs(int node) {
        // cout << "LINE 73 " << node << endl;
        maxDepth[node]=depth[node];
        trav(x, adj[node]) {
            if(x==par[node]) continue;
            par[x]=node;
            depth[x]=depth[node]+1;
            dfs(x);
            subSize[node]+=subSize[x];
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> adj(n);
        F0R(i,n-1) {
            int a,b;
            cin >> a >> b;
            adj[a-1].add(b-1);
            adj[b-1].add(a-1);
        }
        TreeAlg tt(adj,0);
        tt.set_sparse();
        int bestDist=0;
        pair<int,int> vert = {0,0};
        F0R(i, n) {
            F0R(j, n) {
                // cout << "LINE 140 " << i << " " << j << endl;
                int d = tt.dist(i,j);
                if(d>bestDist) {
                    bestDist=d;
                    vert={i,j};
                }
            }
        }
        // cout << vert << bestDist << endl;
        if(bestDist%2==0) {
            //find center
            int mid = 0;
            F0R(i, n) {
                if(tt.dist(i,vert.f)==bestDist/2&&tt.dist(i,vert.s)==bestDist/2) mid=i;
            }
            // cout << mid << endl;
            cout << bestDist/2+1 << endl;
            F0R(i, bestDist/2+1) {
                cout << mid+1 << " " << i << endl;
            }
        } else {
            int mid0,mid1;
            F0R(i, n) {
                if(tt.dist(i,vert.f)==bestDist/2&&tt.dist(i,vert.s)==(bestDist+1)/2) {
                    mid0=i;
                }
                if(tt.dist(i,vert.s)==bestDist/2&&tt.dist(i,vert.f)==(bestDist+1)/2) {
                    mid1=i;
                }
            }
            // cout << vert << " " << bestDist << " " << mid0 << " " << mid1 << endl;
            int majority = (bestDist+1)/2;
            if(majority%2==0) majority--;
            int numbers = (majority-1)/2+1;
            cout << numbers*2 << endl;
            for(int i = 1; i <= majority; i+=2) {
                cout << 1+mid0 << " " << i << endl;
                cout << 1+mid1 << " " << i << endl;
            }
            
        }
    }
    return 0;
}