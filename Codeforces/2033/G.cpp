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
ll mod = 1000000007;
struct SegTree {
    int n;
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=max(tree[2*pos], tree[2*pos+1]);
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = -inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=max(ans, tree[a++]);
            if(b%2==0) ans=max(ans, tree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
};
SegTree st(1);
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};

FastMod fs(mod);
int n;
vt<vt<int>> adj;
vt<array<int,2>> dp;
int ans[200001];
vt<vt<pair<int,int>>> queries;
vt<int> depth;
void dfs2(int node, int par) {
    trav(x, adj[node]) {
        if(x==par) continue;
        if(dp[x][0]==dp[node][0]) {
            st.set(depth[node], -2*depth[node]+dp[node][1]);
        } else {
            st.set(depth[node], -2*depth[node]+dp[node][0]);
        }
        dfs2(x, node);
    }
    if(node==0) {
        trav(x, queries[node]) {
            ans[x.s]=dp[node][0];
        }
        return;
    }
    // cout << node << st.tree << endl;
    trav(x, queries[node]) {
        int minDepth = max(0LL, depth[node]-x.f);
        int an = max(depth[node]-minDepth, dp[node][0]-depth[node]);
        // cout << node << x << an << " " << minDepth << endl;
        an=max(an, depth[node]+st.rangeQuery(minDepth, depth[node]-1));
        // cout << an << " " << depth[node] << " " << st.rangeQuery(minDepth, depth[node]-1) << endl;
        ans[x.s]=an;
    }
}
void dfs(int node, int par) {
    trav(x, adj[node]) {
        if(x==par) continue;
        depth[x]=depth[node]+1;
        dfs(x, node);
    }
    multiset<int> here;
    trav(x, adj[node]) {
        if(x==par) continue;
        here.insert(dp[x][0]);
    }
    if(adj[node].size()==1&&node!=0) {
        dp[node][0]=depth[node];
        dp[node][1]=-1e9;
        return;
    }
    if(here.size()==1) {
        dp[node][0]=(*here.rbegin());
        dp[node][1]=-1e9;
    } else {
        dp[node][0]=(*here.rbegin());
        here.erase(here.find(dp[node][0]));
        dp[node][1]=(*here.rbegin());
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n;
        st = SegTree(n+5);
        adj.assign(n, vt<int>());
        F0R(i, n-1) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].add(b);
            adj[b].add(a);
        }
        dp.assign(n, array<int, 2>());
        depth.assign(n, 0);
        dfs(0, -1);
        int q;
        cin >> q;
        queries.assign(n, vt<pair<int,int>>());
        F0R(i, q) {
            int v,k;
            cin >> v >> k;
            v--;
            queries[v].add({k, i});
        }
        dfs2(0, -1);
        // cout << dp << endl;
        F0R(i, q) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}