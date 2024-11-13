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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 998244353;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
ll bexpo(ll b, ll e) {
    ll a = 1;
    while(e) {
        if(e&1) {
            a*=b;
            a%=mod;
        }
        e>>=1;
        b*=b;
        b%=mod;
    }
    return a;
}
FastMod fs(mod);
int n;
int inv2, inv3, tinv3;
vt<int> depth, minDepth, ans;
vt<vt<int>> adj;
vt<int> worstChild;
void dfs(int node, int par) {
    if(adj[node].size()==1&&node!=0) {
        minDepth[node]=depth[node];
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        depth[x]=depth[node]+1;
        dfs(x, node);
        minDepth[node]=min(minDepth[node], minDepth[x]);
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        if(minDepth[x]==minDepth[node]) {
            worstChild[node]=x;
        }
    }
}

int dfs2(int node, int par, pair<int,int> info) {
    pair<int,int> here;
    // cout << node << " " << info << endl;
    /*
    P(node)=0.5P(par)+0.5P(worstChild)
    P(node)=0.5(0.5P(node)+0.5x)+0.5P(worstChild)
    0.75P(node)=0.25x+0.5P(worstChild)
    P(node)=4(0.25x)/3+4(0.5P(worstChild))/3
    P(node)=x/3+2P(worstChild)/3
    */
    if(adj[node].size()==1) {
        ans[node]=0;
        return 0;
    }
    if(info.s==-1) {
        here.f=info.f*inv2%mod;
        here.s=inv2;
    } else {
        here.f=tinv3*info.f%mod;
        here.s=tinv3;
    }
    int temp = dfs2(worstChild[node], node, here);
    int her = here.f+here.s*temp;
    her%=mod;
    trav(x, adj[node]) {
        if(x==par) continue;
        if(x==worstChild[node]) continue;
        dfs2(x, node, {her,-1});
    }
    ans[node]=her;
    return her;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    inv2=bexpo(2, mod-2);
    inv3=bexpo(3, mod-2);
    tinv3 = 2*inv3%mod;
    int t = 1;  
    cin >> t;
    while(t--) {
        cin >> n;
        adj.assign(n, vt<int>());
        ans.assign(n, 0);
        ans[0]=1;
        worstChild.assign(n, 0);
        depth.assign(n, 0);
        minDepth.assign(n, inf);
        F0R(i, n-1) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].add(b);
            adj[b].add(a);
        }
        dfs(0,-1);
        trav(x, adj[0]) {
            dfs2(x, 0, {1,-1});
        }
        // cout << ans << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}