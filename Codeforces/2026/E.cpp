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
struct Match {
    int n, m, k;
    // dist[node] = the position of node in the alternating path
    vector<int> match, dist;
    vector<vector<int>> g;

    bool bfs() {
        queue<int> q;
        // The alternating path starts with unmatched nodes
        for (int node = 1; node <= n; node++) {
            if (!match[node]) {
                q.push(node);
                dist[node] = 0;
            } else {
                dist[node] = inf;
            }
        }

        dist[0] = inf;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            if (dist[node] >= dist[0]) { continue; }
            for (int son : g[node]) {
                // If the match of son is matched
                if (dist[match[son]] == inf) {
                    dist[match[son]] = dist[node] + 1;
                    q.push(match[son]);
                }
            }
        }
        // Returns true if an alternating path has been found
        return dist[0] != inf;
    }
    // Returns true if an augmenting path has been found starting from vertex node
    bool dfs(int node) {
        if (node == 0) { return true; }
        for (int son : g[node]) {
            if (dist[match[son]] == dist[node] + 1 && dfs(match[son])) {
                match[node] = son;
                match[son] = node;
                return true;
            }
        }
        dist[node] = inf;
        return false;
    }

    int hopcroft_karp() {
        int cnt = 0;
        // While there is an alternating path
        while (bfs()) {
            for (int node = 1; node <= n; node++) {
                // If node is unmatched but we can match it using an augmenting path
                if (!match[node] && dfs(node)) { cnt++; }
            }
        }
        return cnt;
    }
    Match(int nn, int mm, int kk, vector<pair<int,int>> &adj) {
        n=nn;
        m=mm;
        k=kk;
        dist.resize(n + m + 1);

        match.resize(n + m + 1);
        g.resize(n + m + 1);    
        for(auto x: adj) {
            g[x.first].push_back(x.second);
		    g[x.second].push_back(x.first);
        }
    }
};
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
        vt<pair<int,int>> adj;
        F0R(i, n) {
            int x;
            cin >> x;
            F0R(j, 60) {
                if(x&(1LL<<j)) {
                    adj.add({i+1,j+n+1});
                }
            }
        }
        Match m(n, 60, adj.size(), adj);
        int best_match = n+60-m.hopcroft_karp();
        cout << best_match-60 << endl;
    }
    return 0;
}