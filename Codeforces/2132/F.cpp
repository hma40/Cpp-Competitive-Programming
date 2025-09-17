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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<vt<pair<int,int>>> adj(n);
        F0R(i, m) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add({v,i+1});
            adj[v].add({u,i+1});
        }
        vt<vt<pair<int,int>>> tadj(n), back(n), front(n);
        vt<bool> vis(n);
        vt<int> par(n, -1);
        vt<int> pind(n,-1);
        vis[0]=1;
        vt<int> depth(n);
        auto dfs = [&](auto self, int node)->void{
            // cout << "LINE 174 " << node << vis << endl;
            trav(x, adj[node]) {
                if(vis[x.f]) {
                    if(par[node]==x.f) {
                        continue;
                    } else {
                        if(depth[node]>depth[x.f]) {
                            back[node].add(x);
                        } else {
                            front[node].add(x);
                        }
                        // back[node].add(x);
                        // front[x.f].add({node,x.s});
                    }
                } else {
                    depth[x.f]=depth[node]+1;
                    vis[x.f]=true;
                    par[x.f]=node;
                    pind[x.f]=x.s;
                    // tadj[x.f].add({node,x.s});
                    tadj[node].add({x.f,x.s});
                    self(self, x.f);
                }
            }
        };
        dfs(dfs,0);
        // cout << tadj << back << front << endl;
        vt<array<int,3>> bridges;
        deque<int> dq;
        dq.push_back(n-1);
        vt<int> fin;
        while(dq.size()) {
            auto front = dq.front();
            dq.pop_front();
            if(tadj[front].size()==0) {
                fin.add(front);
            } else {
                trav(x, tadj[front]) {
                    dq.push_back(x.f);
                }
            }
        }
        // cout << fin << endl;
        vt<int> dp(n);
        trav(x, fin) dq.push_back(x);
        vis.assign(n,false);

        vt<bool> good(m+1);
        dp.assign(n,0);
        auto dfs2 = [&](auto self, int node)->void{
            trav(x, tadj[node]) {
                self(self,x.f);
                dp[node]+=dp[x.f];
            }
            dp[node]+=back[node].size();
            dp[node]-=front[node].size();
            if(dp[node]==0 && pind[node]!=-1) good[pind[node]]=1;
        };
        dfs2(dfs2,0);
        dq.clear();
        dq.push_back(n-1);
        while(dq.size()) {
            auto tp = dq.front();
            dq.pop_front();
            if(tp==0) continue;
            if(good[pind[tp]]) bridges.add({tp, par[tp], pind[tp]});
            if(!vis[par[tp]]) {
                vis[par[tp]]=true;
                dq.push_back(par[tp]);
            }
        }
        // cout << good << endl;
        // vis.assign(n,false);
        vt<int> dist(n,inf);
        vt<int> ans(n, inf);
        // cout << bridges << good << endl;
        trav(x, bridges) {
            if(!good[x[2]]) continue;
            if(dist[x[0]]==inf) dq.push_back(x[0]);
            if(dist[x[1]]==inf) dq.push_back(x[1]);
            // cerr << "LINE 261 " << x[2] << endl;
            dist[x[0]]=0;
            ans[x[0]]=min(ans[x[0]],x[2]);
            dist[x[1]]=0;
            ans[x[1]]=min(ans[x[1]],x[2]);
        }
        while(dq.size()) {
            auto tp = dq.front();
            // cout << "LINE 254: " << tp << endl;
            dq.pop_front();
            trav(x, adj[tp]) {
                if(dist[x.f]>dist[tp]+1) {
                    dist[x.f]=dist[tp]+1;
                    ans[x.f]=ans[tp];
                    dq.push_back(x.f);
                } else if(dist[x.f]==dist[tp]+1) {
                    ans[x.f]=min(ans[x.f],ans[tp]);
                }
            }
        }
        // cerr << tadj << endl;
        int q;
        cin >> q;
        while(q--) {
            int u;
            cin >> u;
            u--;
            if(ans[u]==inf) {
                cout << -1 << enld;
            } else {
                cout << ans[u] << endl;
            }
        }
    }
    return 0;
}
/*
make the DFS tree rooted at 1
all the bridges on the path from 1 to n is a candidate
then we can do BFS

1
6 7
1 2
1 3
3 4
4 5
2 6
1 4
4 6
6
1
2
3
4
5
6

DFS TREE
0-1
1-5
5-3
3-2
3-
*/