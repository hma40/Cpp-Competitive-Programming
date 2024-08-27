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
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct GraphAlgs {
    int n;
    vt<vt<int>> adj;
    vt<int> timer, lowestTimer;
    vt<bool> vis;
    int time;
    set<pair<int,int>> bridges;
    vt<vt<int>> dfs_tree_edges;
    vt<int> eulerPath;
    GraphAlgs(vt<vt<int>> aj) {
        adj=aj;
        n=aj.size();
    }
    void dfs(int node, int par) {   
        vis[node]=true;
        trav(x, adj[node]) {
            if(x==par) continue;
            if(vis[x]) continue;
            dfs_tree_edges[node].add(x);
            dfs_tree_edges[x].add(node);
            dfs(x,node);
        }
    }
    void getDFSTree(int node) {
        vis.assign(n, false);
        dfs_tree_edges.assign(n,vt<int>());
        dfs(node,-1);
    }
    void bridge_dfs(int v, int p=-1) {
        timer[v]=lowestTimer[v]=time++;
        vis[v]=true;
        trav(x, adj[v]) {
            if(x==p) continue;
            if(vis[x]) {
                lowestTimer[v]=min(lowestTimer[v], timer[x]);
            } else {
                bridge_dfs(x, v);
                lowestTimer[v]=min(lowestTimer[v], lowestTimer[x]);
                if(lowestTimer[x]>timer[v]) {
                    bridges.insert({x,v});
                    bridges.insert({v,x});
                }
            }
        }
    }   
    void getBridges() {
        time=0;
        timer.assign(n, -1);
        lowestTimer.assign(n, -1);
        vis.assign(n, false);
        bridges.clear();
        F0R(i, n) {
            if(!vis[i]) {
                bridge_dfs(i, -1);
            }
        }
    }
    void getEulerPath(int start) {
        vt<set<int>> edges(n);
        F0R(i, n) {
            trav(x, adj[i]) {
                edges[i].insert(x);
            }
        }
        deque<int> dq;
        dq.push_back(start);
        eulerPath.clear();
        while(dq.size()) {
            int z = dq.front();
            if(edges[z].size()) {
                int next = *(edges[z].begin());
                edges[z].erase(next);
                edges[next].erase(z);
                dq.push_front(next);
            } else {
                eulerPath.add(z);
                dq.pop_front();
            }
        }
    }
};
vt<string> all;
deque<char> gen(int n, string pref, deque<char> start) {
    deque<char> ret;
    if(n==1) {
        if(start.front()=='0') {
            all.add(pref+'0');
            all.add(pref+'1');
            ret.push_back('1');
        } else {
            all.add(pref+'1');
            all.add(pref+'0');
            // return "0";
            ret.push_back('0');
        }
        return ret;
    } else {
        if(start.front()=='0') {
            pref+='0';
            start.pop_front();
            auto nding = gen(n-1, pref, start);
            pref.pop_back();
            pref+='1';
            auto nd = gen(n-1, pref, nding);
            nd.push_front('1');
            return nd; 
        } else {
            pref+='1';
            start.pop_front();
            auto nding = gen(n-1, pref, start);
            pref.pop_back();
            pref+='0';
            auto nd = gen(n-1, pref, nding);
            nd.push_front('0');
            return nd;
        }
    }

}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n;
    cin >> n;
    deque<char> start;
    F0R(i, n) start.push_back('0');
    gen(n, "", start);
    // cout << all << endl;
    trav(x, all) cout << x << endl;
    return 0;
}
/*
0
1

00
01
11
10

000
001
011
010
110
101
100
111

0000
0001
0010
0011
0100
0101
0110
0111
1111
1110
1101
1100
1000
1001
1011
1010
*/