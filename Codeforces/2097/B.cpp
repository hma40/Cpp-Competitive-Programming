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
const ll mod = 1000000007;
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
        int n,m,k;
        cin >> n >> m >> k;
        set<pair<int,int>> bad;
        vt<vt<vt<pair<int,int>>>> adj(n, vt<vt<pair<int,int>>>(m));
        pair<int,int> prev;
        // bool dead = false;
        cin >> prev.f >> prev.s;
        prev.f--;
        prev.s--;
        int ans = 1;
        F0R(i, k) {
            pair<int,int> here;
            cin >> here.f >> here.s;
            here.f--;
            here.s--;
            if(abs(here.f-prev.f)+abs(here.s-prev.s)!=2) {
                ans=0;
                continue;
            }
            if(here.f==prev.f+2) {
                if(bad.count({prev.f+1, here.s})) {
                    ans=0;
                    continue;
                } else {
                    bad.insert({prev.f+1, here.s});
                }
            } else if(here.f==prev.f-2) {
                if(bad.count({prev.f-1, here.s})) {
                    ans=0;
                    continue;
                } else {
                    bad.insert({prev.f-1, here.s});
                }
            } else if(here.s==prev.s+2) {
                if(bad.count({prev.f, prev.s+1})) {
                    ans=0;
                    continue;
                } else {
                    bad.insert({prev.f, prev.s+1});
                }
            } else if(here.s==prev.s-2) {
                if(bad.count({prev.f, prev.s-1})) {
                    ans=0;
                    continue;
                } else {
                    bad.insert({prev.f, prev.s-1});
                }
            } else if(here.f==prev.f+1 && here.s==prev.s+1) {
                adj[prev.f+1][prev.s].add({prev.f, prev.s+1});
                adj[prev.f][prev.s+1].add({prev.f+1, prev.s});
            } else if(here.f==prev.f+1 && here.s==prev.s-1) {
                adj[prev.f+1][prev.s].add({prev.f, prev.s-1});
                adj[prev.f][prev.s-1].add({prev.f+1, prev.s});
            } else if(here.f==prev.f-1 && here.s==prev.s+1) {
                adj[prev.f-1][prev.s].add({prev.f, prev.s+1});
                adj[prev.f][prev.s+1].add({prev.f-1, prev.s});
            } else if(here.f==prev.f-1 && here.s==prev.s-1) {
                adj[prev.f-1][prev.s].add({prev.f, prev.s-1});
                adj[prev.f][prev.s-1].add({prev.f-1, prev.s});
            } else {
                assert(false);
            }
            swap(prev,here);
            // cout << i << adj << endl;
        }
        // F0R(i, n) F0R(j, m) cout << i << " " << j << " " << adj[i][j] << endl;
        // cout << bad << endl;
        // assert(false);
        vt<vt<bool>> vis(n, vt<bool>(m));
        F0R(i, n) F0R(j, m) {
            // cout << i << " " << j << endl;
            if(vis[i][j]) continue;
            int edges=0, nodes=0, self = 0;
            if(adj[i][j].size()==0) continue;
            deque<pair<int,int>> dq;
            dq.push_back({i,j});
            vis[i][j]=true;
            while(dq.size()) {
                auto tp = dq.front();
                nodes++;
                dq.pop_front();
                edges+=adj[tp.f][tp.s].size();
                if(bad.count({tp.f,tp.s})) self++;
                trav(x, adj[tp.f][tp.s]) {
                    if(vis[x.f][x.s]) continue;
                    vis[x.f][x.s]=true;
                    dq.push_back(x);
                }
            }
            // cout << nodes << " " << edges << " " << self << endl;
            edges/=2;
            edges+=self;
            if(nodes==edges+1 && !self) ans=ans*nodes%mod;
            else if(nodes<edges) ans=0;
            else if(self) continue;
            else {
                // cout << "case 254" << endl;
                ans=ans*2%mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
5 5 3
3 3
3 5
4 4
2 4
*/