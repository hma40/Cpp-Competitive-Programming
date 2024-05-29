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
vt<vt<int>> adj;
vt<int> par,depth;
vt<set<int>> activeChildren;
int highestUp=-1;
vt<bool> active;
vt<vt<int>> sparse;
set<int> waiting;
vt<int> conn;
void reset(int n) {
    adj.clear();
    par.clear();
    depth.clear();
    activeChildren.clear();
    active.clear();
    waiting.clear();
    sparse.clear();
    conn.clear();
    adj.resize(n);
    par.resize(n);
    depth.resize(n);
    activeChildren.resize(n);
    active.resize(n);
    sparse.resize(n, vt<int>(20));
}
void dfs(int n) {
    // cout << n << par << endl;
    trav(x, adj[n]) {
        if(x!=par[n]) {
            par[x]=n;
            depth[x]=depth[n]+1;
            dfs(x);
        }
    }
}
int jump(int n, int amount) {
    F0R(i, 20) {
        if(amount&(1<<i)) n=sparse[n][i];
    }
    return n;
}
int lca(int m, int n) {
    if(depth[m]>depth[n]) swap(m,n);
    n=jump(n, depth[n]-depth[m]);
    if(m==n) return m;
    R0F(i, 20) {
        if(sparse[n][i]!=sparse[m][i]) {
            n=sparse[n][i];
            m=sparse[m][i];
        }
    }
    return par[m];
}
void getS(int n) {
    F0R(i, n) sparse[i][0]=par[i];
    FOR(i, 1, 20) {
        F0R(j, n) {
            // cout << i << " " << j << " " << sparse[j][i-1] << endl;
            if(sparse[j][i-1]==-1) {
                sparse[j][i]=-1;
                continue;
            }
            // cout << i << " " << j << endl;
            sparse[j][i]=sparse[sparse[j][i-1]][i-1];
        }
    }
}

bool query(int n) {
    if(active[n]) {
        active[n]=false;
    } else {
        active[n]=true;
        if(n!=0) {
            activeChildren[par[n]].add(n);
        }
        if(highestUp.size()==0) {
            highestUp.add(n);
            return true;
        }
        trav(x, activeChildren[n]) {
            waiting.erase(x);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        reset(n);
        vt<int> qy;
        F0R(i, n) {
            int x;
            cin >> x;
            if(x) {
                qy.add(x);
            }

        }
        F0R(i, n-1) {
            int x,y;
            cin >> x >> y;
            adj[x-1].add(y-1);
            adj[y-1].add(x-1);
        }
        par[0]=-1;
        // cout << par << endl;
        // cout << par[0] << endl;
        dfs(0);
        // cout << par << adj << depth << endl;
        getS(n);
        trav(x, qy) {
            query(x);
        }
        F0R(i, q) {
            int x;
            cin >> x;
            if(query(x-1)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
/*
1
4 4
0 0 0 0
1 2
2 3
1 4
*/