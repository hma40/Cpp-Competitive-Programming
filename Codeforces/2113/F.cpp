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
        int n;
        cin >> n;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        F0R(i, n) {
            a[i]--;
            b[i]--;
            if(a[i]>b[i]) swap(a[i],b[i]);
        }
        vt<array<int,3>> v;
        F0R(i, n) v.add({a[i],b[i],i});
        sort(begin(v),end(v));
        vt<vt<pair<int,int>>> adj(2*n), tadj(2*n), back(2*n);
        // cout << v << endl;
        F0R(i, n) {
            if(i!=0 && v[i][0]==v[i-1][0] && v[i][1]==v[i-1][1]) {
                if(adj[v[i][0]].size() && adj[v[i][0]].back().f==v[i][1]) {
                    adj[v[i][0]].pop_back();
                    adj[v[i][1]].pop_back();
                }
                swap(a[v[i][2]],b[v[i][2]]);
            } else if(v[i][0]!=v[i][1]) {
                adj[v[i][0]].add({v[i][1],v[i][2]});
                adj[v[i][1]].add({v[i][0],v[i][2]});
            }
        }
        // cout << "LINE 185 " << adj << endl;
        vt<int> par(2*n,-1), depth(2*n);
        vt<bool> vis(2*n);
        auto dfs = [&](auto self, int node)->void{
            trav(x, adj[node]) {
                if(vis[x.f]) {
                    if(par[node]==x.f) {
                        continue;
                    } else {
                        back[node].add({x.f,x.s});
                    }
                } else {
                    vis[x.f]=true;
                    par[x.f]=node;
                    depth[x.f]=depth[node]+1;
                    tadj[x.f].add({node,x.s});
                    tadj[node].add({x.f,x.s});
                    self(self,x.f);
                }
            }
        };
        /*
        tree-edges: lower depth on a, higher depth on b
        back-edges: lower depth on b, higher depth on a
        */
        auto dfs2 = [&](auto self, int node)->void{
            trav(x, back[node]) {
                if(depth[x.f]>depth[node]) {
                    //node has lower depth
                    b[x.s]=node;
                    a[x.s]=x.f;
                } else {
                    a[x.s]=node;
                    b[x.s]=x.f;
                }
            }
            trav(x, tadj[node]) {
                if(depth[x.f]>depth[node]) {
                    //node has lower depth
                    a[x.s]=node;
                    b[x.s]=x.f;
                    self(self,x.f);
                } else {
                    a[x.s]=x.f;
                    b[x.s]=node;
                }
            }
        };

        auto rev = [&](auto self, int node)->void{
            trav(x, back[node]) {
                if(depth[x.f]>depth[node]) {
                    //node has lower depth
                    a[x.s]=node;
                    b[x.s]=x.f;
                } else {
                    b[x.s]=node;
                    a[x.s]=x.f;
                }
            }
            trav(x, tadj[node]) {
                if(depth[x.f]>depth[node]) {
                    //node has lower depth
                    b[x.s]=node;
                    a[x.s]=x.f;
                    self(self,x.f);
                } else {
                    b[x.s]=x.f;
                    a[x.s]=node;
                }
            }
        };  
        // cout << adj << endl;
        F0R(i, 2*n) {
            if(vis[i]) continue;
            vis[i]=true;
            dfs(dfs,i);
            // cout << i << tadj << back << endl;
            dfs2(dfs2,i);
            if(adj[i].size()>1) {
                rev(rev, tadj[i][0].f);
            }
        }
        // cout << tadj << back << endl;
        // cout << a << endl << b << endl;
        set<int> aa,bb;
        trav(x, a) aa.insert(x);
        trav(x, b) bb.insert(x);
        cout << aa.size()+bb.size() << endl;
        trav(x, a) cout << x+1 << " ";
        cout << endl;
        trav(x, b) cout << 1+x << " ";
        cout << enld;
    }
    return 0;
}