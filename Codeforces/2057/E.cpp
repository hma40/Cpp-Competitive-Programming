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
// #define int long long
#define vt vector
#define endl "\n"
#define double long double
const ll mod = 1000000007;
const ll inf = 2e9;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct DSU {
    vt<int> par,sz;
    DSU(int n) {
        par.resize(n,-1);
        sz.resize(n,1);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(sz[x]>sz[y])swap(x,y);
        sz[y]+=sz[x];
        par[x]=y;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m,q;
        cin >> n >> m >> q;
        vt<vt<pair<int,int>>> adj(n);
        // min_pq<int> pq;
        // vt<array<int,3>> mp;
        min_pq<array<int,3>> pq;
        // mp.add({-inf,-inf,-inf});
        F0R(i, m) {
            int u,v,w;
            cin >> u >> v >> w;
            u--;
            v--;
            adj[u].add({v,w});
            adj[v].add({u,w});
            pq.push({w,u,v});
        }
        vt<int> mp;
        // sort(begin(mp),end(mp));
        vt<vt<vt<int>>> ans(n,vt<vt<int>>(n,vt<int>(n+1, inf)));//ans[i][j][k] = dist[i][j] if the smallest k weights are 0 
        // int nxt = 0;
        F0R(i, n) {
            queue<int> qq;
            qq.push(i);
            ans[i][i][0]=0;
            while(qq.size()) {
                auto tp = qq.front();
                qq.pop();
                trav(x, adj[tp]) {
                    if(ans[i][x.f][0]>ans[i][tp][0]+1) {
                        ans[i][x.f][0]=ans[i][tp][0]+1;
                        qq.push(x.f);
                    }
                }
            }
        }
        DSU d(n);
        int ii = 0;
        while(pq.size()) {
            auto tp = pq.top();
            pq.pop();
            if(d.find(tp[1])==d.find(tp[2])) continue;
            d.unite(tp[1],tp[2]);
            mp.add(tp[0]);
            // cout << ii << endl;
            // auto tp = mp[ii+1];
            F0R(i, n) {
                F0R(j,n) {
                    ans[i][j][ii+1]=min({ans[i][j][ii], ans[i][tp[1]][ii]+ans[j][tp[2]][ii], ans[i][tp[2]][ii]+ans[j][tp[1]][ii]});
                }
            }
            ii++;
        }
        // cout << ans[0] << endl << mp << endl;
        F0R(iiq, q) {
            int a,b,k;
            cin >> a >> b >> k;
            a--;
            b--;
            int lo = -1, hi = n;
            while(lo+1<hi) {
                int mid = (1+lo+hi)/2;
                if(ans[a][b][mid]>k-1) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            cout << mp[hi-1] << " ";
        }
        cout << endl;
    }
    return 0;
}