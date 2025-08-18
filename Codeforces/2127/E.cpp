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
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int ans;
void dfs(int node, int par, vt<set<int>> &cols, vt<vt<int>> &adj, vt<int> &w, vt<int> &c) {
    // cout << "DFS CALLED: " << node << " " << par << endl;
    int bad = 0;
    trav(x, adj[node]) {
        if(x==par) {
            continue;
        }
        // cout << "GOT TO LINE 159: " << node << " " << par << " " << x << endl;
        dfs(x, node, cols, adj, w, c);
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        if(cols[x].size()>cols[node].size()) {
            cols[x].swap(cols[node]);
        }
        trav(col, cols[x]) {
            if(cols[node].count(col)) {
                if(bad==0||bad==col) bad=col;
                else bad=-1;
            }
            cols[node].insert(col);
        }
    }
    if(bad!=-1 && bad!=0) {
        if(c[node]==0 || c[node]==bad) {
            c[node]=bad;
            cols[node].insert(bad);
        } else {
            ans+=w[node];
            cols[node].insert(c[node]);
        }
    } else if(bad==0) {
        if(c[node]==0) {
            // c[node]=1;
            // cols[node].insert(1);
        } else {
            cols[node].insert(c[node]);
        }
    } else {
        ans+=w[node];
        if(c[node]==0) {
            // c[node]=1;
            // cols[node].insert(1);
        } else {
            cols[node].insert(c[node]);
        }
    }

    // cout << node << " " << cols[node] << " " << ans << endl;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        ans=0;
        int n,k;
        cin >> n >> k;
        vt<int> w(n), c(n);
        vt<vt<int>> adj(n);
        F0R(i, n) {
            cin >> w[i];
        }
        F0R(i, n) cin >> c[i];
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        // cout << adj << endl;
        vt<set<int>> cols(n);
        dfs(0, -1, cols, adj, w, c);
        cout << ans << endl;
        deque<int> dq;
        F0R(i, n) {
            if(c[i]!=0) dq.push_back(i);
        }
        while(dq.size()) {
            auto tp = dq.front();
            dq.pop_front();
            trav(x, adj[tp]) {
                if(c[x]!=0) continue;
                c[x]=c[tp];
                dq.push_back(x);
            }
        }
        F0R(i, n) if(c[i]==0) c[i]=1;
        F0R(i, n) cout << c[i] << " ";
        cout << endl;
    }
    return 0;
}
/*
for the rest of them
coloring same as a descendant or ancestor is never bad
*/