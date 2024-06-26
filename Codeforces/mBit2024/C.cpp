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
struct binlift {
    int n, lg;
    vector<int> dep;
    vector<vector<int>> up;
 
    binlift(vector<vector<int>> &g) : n(g.size()), lg(__lg(n) + 1), dep(n, -1), up(lg, vector<int>(n, -1)) {
        queue<int> q;
        dep[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    up[0][v] = u;
                    q.push(v);
                }
            }
        }
        for (int i = 1; i < lg; i++) {
            for (int j = 0; j < n; j++) {
                if (up[i - 1][j] != -1) {
                    up[i][j] = up[i - 1][up[i - 1][j]];
                }
            }
        }
    }
 
    int anc(int x, int k) {
        for (int i = 0; i < lg; i++) {
            if (x != -1 && (k >> i) & 1) {
                x = up[i][x];
            }
        }
        return x;
    }
 
    int lca(int a, int b) {
        if (dep[a] < dep[b]) {
            swap(a, b);
        }
        a = anc(a, dep[a] - dep[b]);
        if (a == b) {
            return a;
        }
        for (int i = lg - 1; i >= 0; i--) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return up[0][a];
    }
 
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a, b)];
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        int moves = 0;
        F0R(i, n) {
            moves+=v[i]/2;
            v[i]%=2;
        }
        // cout << moves << endl;
        // cout << v << endl;
        vt<vt<int>> adj(n);
        F0R(i, n-1) {
            int x,y;
            cin >> x >> y;
            adj[--x].add(--y);
            adj[y].add(x);
        }
        binlift bl(adj);
        // cout << bl.dep << endl;
        int last = -1;
        F0R(i, n) {
            if(v[i]) {
                if(last==-1) {
                    last=i;
                } else {
                    moves+=bl.dist(i,last)+1;
                    last=-1;
                }
            }
        }
        if(moves%2) {
            cout << "Borgs" << endl;
        } else {
            cout << "Orgs" << endl;
        }
    }
    return 0;
}