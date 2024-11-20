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
#define int long long
#define vt vector
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct DSU {
    vt<int> par, sz;
    int comps;
    int n,m;
    DSU(int nn, int mm) {
        this->n=nn;
        this->m=mm;
        comps=n*m;
        par.resize(n*m, -1);
        sz.resize(n*m, 1);
    }
    int conv(int a, int b) {
        return a*m+b;
    }
    int find(int c) {
        if(par[c]==-1) return c;
        return par[c]=find(par[c]);
    }
    void connect(int a1, int b1, int a2, int b2) {
        int c1 = find(conv(a1,b1)), c2 = find(conv(a2,b2));
        if(c1==c2) return;
        if(sz[c1]>sz[c2]) swap(c1,c2);
        par[c1]=c2;
        sz[c2]+=sz[c1];
        comps--;
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
        int n,m;
        cin >> n >> m;
        DSU d(n,m);
        vt<vt<bool>> active(n, vt<bool>(m));
        vt<vt<int>> a(n, vt<int>(m));
        priority_queue<array<int,3>> pq;
        F0R(i, n) {
            F0R(j, m) {
                int x;
                cin >> x;
                pq.push({x,i,j});
            }
        }
        vt<pair<int,int>> directions = {{-1,0},{1,0},{0,1},{0,-1}};
        int inactive = n*m;
        int ans = 0 ;
        while(pq.size()) {
            vt<pair<int,int>> here;
            auto tp = pq.top()[0];
            while(pq.size()&&pq.top()[0]==tp) {
                here.add({pq.top()[1], pq.top()[2]});
                inactive--;
                pq.pop();
            }
            trav(x, here) active[x.f][x.s]=true;
            trav(x, here) {
                trav(y, directions) {
                    pair<int,int> nd = {x.f+y.f,x.s+y.s};
                    // cout << nd << endl;
                    if(nd.f>=0&&nd.f<n&&nd.s>=0&&nd.s<m&&active[nd.f][nd.s]) {
                        d.connect(x.f,x.s,nd.f,nd.s);
                    }
                }
            }
            ans=max(ans, d.comps-inactive);
        }
        cout << ans << endl;
    }
    return 0;
}