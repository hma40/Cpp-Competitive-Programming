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
const ll mod = 1000000007;
ll inf = 1e18;
ll gcd(ll a, ll b) {
    if(a>b) swap(a,b);
    while(a!=0) {
        int t = a;
        a=b%a;
        b=t;
    }
    return b;
}
__int128_t inv(int n, int x) {
    __int128_t t = 0, new_t = 1;
    __int128_t r = x, new_r = n;
 
    while (new_r != 0) {
        __int128_t quotient = r / new_r;
 
        __int128_t temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
 
        __int128_t temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
 
    if (r > 1) {
        throw std::invalid_argument("No inverse exists (MY_gcd(n, x) ≠ 1)");
    }
 
    if (t < 0) {
        t += x;
    }
 
    return t;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void dfs(int node, vt<int> &par, vt<int> &depth, vt<vt<int>> &adj) {
    trav(x, adj[node]) {
        if(x==par[node]) {
            continue;
        }
        par[x]=node;
        depth[x]=depth[node]+1;
        dfs(x, par, depth, adj);
    }
}
int lca(int u, int v, vt<int> &depth, vt<int> &par) {
    while(depth[u]>depth[v]) u=par[u];
    while(depth[v]>depth[u]) v=par[v];
    while(u!=v) {
        u=par[u];
        v=par[v];
    }
    return u;
}
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
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
        if(n==1) {
            cout << 2 << endl;
            continue;
        }
        vt<vt<int>> adj(n);
        vt<int> par(n, -1), depth(n);
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        dfs(0, par, depth, adj);
        vt<int> leaf;
        FOR(i, 1, n) {
            if(adj[i].size()==1) leaf.add(i);
        }
        if(leaf.size()>2) {
            cout << 0 << endl;
            continue;
        }
        if(leaf.size()==1) {
            cout << bexpo(2, n) << endl;
            continue;
        }
        if(leaf.size()==2) {
            int l = lca(leaf[0], leaf[1], depth, par);
            // cout << leaf << l << endl;
            if(depth[leaf[0]]-depth[l]==1 && depth[leaf[1]]-depth[l]==1) {
                cout << bexpo(2, n-1) << endl;
            } else if(depth[leaf[0]]-depth[l]==1 || depth[leaf[1]]-depth[l]==1) {
                //1 2 1, 1 2 2, 2 1 2
                cout << 3*bexpo(2, n-3)%mod << endl;
                continue;
            } else if(depth[leaf[0]]!=depth[leaf[1]]) {
                cout << 3*bexpo(2, max(depth[leaf[0]], depth[leaf[1]])-min(depth[leaf[0]], depth[leaf[1]])+depth[l])%mod << endl;
            } else {
                cout << 2*bexpo(2, depth[l]+1) << endl;
            }
        }
    }

    return 0;
}