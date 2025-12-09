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
struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f,c;
    };
    vt<vt<Edge>> g;
    vt<ll> ec;
    vt<Edge*> cur;
    vt<vt<int>> hs;
    vt<int> H;
    PushRelabel(int n): g(n), ec(n), cur(n), hs(2*n), H(n) {}
    void addEdge(int s, int t, ll cap, ll rcap = 0) {
        if(s==t) return;
        g[s].add({t,(int)g[t].size(), 0, cap});
        g[t].add({s, (int)g[s].size()-1, 0, rcap});
    }
    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if(!ec[e.dest] && f) hs[H[e.dest]].add(e.dest);
        e.f+=f, e.c-=f, ec[e.dest]+=f;
        back.f-=f, back.c+=f; ec[back.dest]-=f;
    }
    ll calc(int s, int t) {
        int v = g.size();
        H[s]=v;
        ec[t]=1;
        vt<int> co(2*v); co[0]=v-1;
        F0R(i, v) cur[i]=g[i].data();
        for(Edge& e: g[s]) addFlow(e, e.c);
        for(int hi = 0;;) {
            while(hs[hi].empty()) if(!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while(ec[u]>0) 
                if(cur[u]==g[u].data()+g[u].size()) {
                    H[u]=1e9;
                    for(Edge& e: g[u]) if(e.c && H[u]>H[e.dest]+1) 
                        H[u]=H[e.dest]+1, cur[u]=&e;
                    if(++co[H[u]], !--co[hi] && hi<v) 
                        F0R(i, v) if(hi<H[i] && H[i]<v) 
                            --co[H[i]], H[i]=v+1;
                    hi=H[u];
                } else if(cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
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
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        PushRelabel p(2*n+2);
        int ans = n;
        F0R(i, n) p.addEdge(0, i+1, 1);
        F0R(i, n) p.addEdge(i+n+1, 2*n+1, 1);
        F0R(i, n) {
            FOR(j, i+1, n) {
                if(abs(a[i]-a[j])==1) p.addEdge(i+1, j+n+1, 1);
            }
        }
        int flo = p.calc(0, 2*n+1);
        cout << n-flo << endl;
    }
    return 0;
}