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
void dfs(int node, int par, vt<vt<int>> &adj, vt<array<int,4>> &dp, vt<vt<vt<int>>> &keep) {
    // assert(false);
    // cout << keep << endl;
    int chil = 0;
    trav(x, adj[node]) {
        if(x==par) continue;
        chil++;
        dfs(x, node, adj, dp, keep);
    }
    dp[node][3]=1;
    vt<pair<int,int>> min_active;
    trav(x, adj[node]) {
        if(x==par) continue;
        min_active.add({min(dp[x][0], dp[x][1])-dp[x][3], x});
    }
    sort(begin(min_active), end(min_active));
    trav(x, adj[node]) {
        if(x==par) continue;
        dp[node][0]+=dp[x][3];
    }
    dp[node][1]=dp[node][0];
    dp[node][2]=dp[node][0];
    if(chil){
        dp[node][1]+=min_active[0].f;
        dp[node][2]+=min_active[0].f;
        keep[node][1].add(min_active[0].s);
        keep[node][2].add(min_active[0].s);
    }
    F0R(i, 3) keep[node][i].add(node);
    // cout << "LINE 175: " << dp[node] << endl;
    if(chil>1) {
        dp[node][2]+=min_active[1].f;
        keep[node][2].add(min_active[1].s);
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        if(dp[x][3]!=min({dp[x][0], dp[x][1], dp[x][2], dp[x][3]})) {
            keep[node][3].add(x);
        }
        dp[node][3]+=min({dp[x][0], dp[x][1], dp[x][2], dp[x][3]});
    }
    // cout << node << min_active << endl;
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
        // vt<int> mp(n);
        set<pair<int,int>> s;
        vt<vt<int>> adj(n);
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        vt<vt<vt<int>>> keep(n, vt<vt<int>>(4));
        vt<array<int,4>> dp(n); //Yes+0, Yes+1, Yes+2, No
        dfs(0,-1, adj, dp, keep);
        // cout << dp << endl;
        // cout << keep << endl;
        // cout << n << " " << n+min({dp[0][0], dp[0][1], dp[0][2], dp[0][3]}) << endl;
        deque<pair<int,int>> dq;
        if(dp[0][0]==min({dp[0][0], dp[0][1], dp[0][2], dp[0][3]})) {
            dq.push_back({0,0});
        } else if(dp[0][1]==min({dp[0][0], dp[0][1], dp[0][2], dp[0][3]})) {
            dq.push_back({0,1});
        } else if(dp[0][3]==min({dp[0][0], dp[0][1], dp[0][2], dp[0][3]})) {
            dq.push_back({0,3});
        } else {
            dq.push_back({0,2});
        }
        vt<bool> vis(n);
        vt<pair<int,int>> ops;
        vis[0]=true;
        vt<bool> vis2(n);
        vt<int> deg(n);
        F0R(i, n) deg[i]=adj[i].size();
        // assert(false);
        while(dq.size()) {
            auto tp = dq.front();
            dq.pop_front();
            // cout << tp << endl;
            if(tp.s==3) {
                vis2[tp.f]=true;
                ops.add({1,tp.f});
                ops.add({2,tp.f});
                trav(x, adj[tp.f]) deg[x]--;
            }
            trav(x, keep[tp.f][tp.s]) {
                if(vis[x]) continue;
                vis[x]=true;
                if(tp.s==3) {
                    if(dp[x][2]==min({dp[x][0],dp[x][1],dp[x][2]})) {
                        dq.push_back({x,2});
                    } else if(dp[x][1]==min({dp[x][0],dp[x][1],dp[x][2]})) {
                        dq.push_back({x,1});
                    } else {
                        dq.push_back({x,0});
                    }
                } else {
                    if(dp[x][1]==min(dp[x][1], dp[x][0])) {
                        dq.push_back({x,1});
                    } else {
                        dq.push_back({x,0});
                    }
                }
            }
            trav(x, adj[tp.f]) {
                if(vis[x]) continue;
                vis[x]=true;
                dq.push_back({x,3});
            }
        }
        deque<int> dq2;
        F0R(i, n) {
            if(!vis2[i] && deg[i]<=1) {
                dq2.push_back(i);
                vis2[i]=true;
                while(dq2.size()) {
                    auto tp = dq2.front();
                    dq2.pop_front();
                    ops.add({1,tp});
                    trav(x, adj[tp]) {
                        if(vis2[x]) continue;
                        vis2[x]=true;
                        dq2.push_front(x);
                    }
                }
            }
        }

        // cout << n << endl;
        cout << ops.size() << endl;
        trav(x, ops) {
            cout << x.f << " " << x.s+1 << endl;
        }
        // cout << dp << enld;
        // cout << keep << endl;
        // cout << n << " " << ops.size() << endl;
        // cout << ops << endl;
        // assert(ops.size()<5*n/4);
    }
    return 0;
}
/*
1
13
1 2
2 3
3 4
3 5
4 6
4 7
7 8
7 9
9 10
1 11
11 12
6 13
*/