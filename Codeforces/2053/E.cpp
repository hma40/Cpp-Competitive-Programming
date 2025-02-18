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
#define endl "\n"
#define double long double
const ll mod = 1000000007;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int ans,root,n;
vt<vt<int>> adj;
vt<int> par,depth,goodChildren;
vt<bool> good;
void dfs(int node) {
    if(adj[node].size()==1) {
        good[node]=false;
        good[par[node]]=false;
    }
    trav(x, adj[node]) {
        if(par[node]==x) continue;
        par[x]=node;
        depth[x]=depth[node]+1;
        dfs(x);
    }
}
void dfs2(int node) {
    trav(x, adj[node]) {
        if(par[node]==x) continue;
        dfs2(x);
        goodChildren[node]+=goodChildren[x];
    }
}
void dfs3(int node) {
    trav(x, adj[node]) {
        if(x==par[node]) continue;
        dfs3(x);
    }
    if(par[node]==-1) return;
    if(adj[node].size()==1) return;
    if(good[par[node]]) return;
    // cout << "LINE 169 " << node << " " << goodChildren[node] << endl;
    ans+=goodChildren[root]-goodChildren[node];
}
void dfs4(int node) {
    trav(x, adj[node]) {
        if(x==par[node]) continue;
        dfs4(x);
    }
    if(par[node]==-1) return;
    if(good[node]) return;
    ans+=goodChildren[node];
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n;
        adj.assign(n,vt<int>());
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            adj[u-1].add(v-1);
            adj[v-1].add(u-1);
        }
        if(n==2) {
            cout << 0 << endl;
            continue;
        }
        goodChildren.assign(n,0);
        good.assign(n,true);
        par.assign(n,-1);
        depth.assign(n,0);
        root = -1;
        F0R(i, n) {
            if(adj[i].size()!=1) {
                root=i;
                break;
            }
        }
        // cout << root << endl;
        // cout << goodChildren << endl;
        ans=0;
        dfs(root);
        F0R(i, n) if(good[i]) goodChildren[i]=1;

        dfs2(root);
        // cout << goodChildren << endl;
        /*
        lets say that Nora's forced first move is moving x->p(x)
        then: p(x) has to be "bad" 
        
        */
        dfs3(root);
        // cout << "LINE 211 " << ans << endl;
        int leaves = 0;
        F0R(i, n) if(adj[i].size()==1) leaves++;
        dfs4(root);
        ans+=leaves*(n-leaves);
        cout << ans << endl;
    }
    return 0;
}
/*
1
10
1 2
2 3
3 4
4 5
5 6
4 7
6 8
4 9
4 10
*/