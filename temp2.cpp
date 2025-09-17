#include <bits/stdc++.h>
using namespace std;
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
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
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
<<<<<<< Updated upstream
=======
vector<bool> visited; // keeps track of which vertices are already visited

// runs depth first search starting at vertex v.
// each visited vertex is appended to the output vector when dfs leaves it.
void dfs(int v, vector<vector<int>> const& adj, vector<int> &output) {
    visited[v] = true;
    for (auto u : adj[v])
        if (!visited[u])
            dfs(u, adj, output);
    output.push_back(v);
}

// input: adj -- adjacency list of G
// output: components -- the strongy connected components in G
// output: adj_cond -- adjacency list of G^SCC (by root vertices)
void strongly_connected_components(vector<vector<int>> const& adj,
                                  vector<vector<int>> &components,
                                  vector<vector<int>> &adj_cond) {
    int n = adj.size();
    components.clear(), adj_cond.clear();

    vector<int> order; // will be a sorted list of G's vertices by exit time

    visited.assign(n, false);

    // first series of depth first searches
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    // create adjacency list of G^T
    vector<vector<int>> adj_rev(n);
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            adj_rev[u].push_back(v);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0); // gives the root vertex of a vertex's SCC

    // second series of depth first searches
    for (auto v : order)
        if (!visited[v]) {
            std::vector<int> component;
            dfs(v, adj_rev, component);
            components.push_back(component);
            int root = *min_element(begin(component), end(component));
            for (auto u : component)
                roots[u] = root;
        }

    // add edges to condensation graph
    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}

>>>>>>> Stashed changes
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
<<<<<<< Updated upstream
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        sort(begin(a),end(a));
        int sum = 0;
        F0R(i, n) sum+=a[i];
        int ans = sum;
        vt<int> p(n+1);
        F0R(i, n) p[i+1]=p[i]+a[i];
        auto getSum = [&](int lo, int hi)->int{
            return p[hi+1]-p[lo];
        };
        FOR(i, 1, n-1) {
            // cout << i << endl;
            int mxX = min(n-i-1, i/k);
            if(mxX!=n-i-1) {
                int here = i*a[i]-getSum(0, i)-getSum(i+1, i+mxX+1)+a[i]*(mxX+1);
                ans=max(ans, sum+here);
            }
            int lo = 1, hi = mxX+1;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(a[i]*k-getSum((mid-1)*k, mid*k-1)>a[i+mid]-a[i]) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            int here = k*lo*a[i]-getSum(0, k*lo-1)-getSum(i+1, i+lo)+a[i]*lo;
            ans=max(ans, sum+here);
        }
        cout << ans << endl;
=======
    int n;
    cin >> n;
    vt<vt<int>> edges(n);
    // vector<vt<int>> edges(n, vt<int>(2));
    for(int i = 0; i < n; i++) {
        // cin >> edges[i][0];
        // edges[i][1]=i+1;
        int v;
        cin >> v;
        v--;
        edges[v].add(i);
>>>>>>> Stashed changes
    }
    vt<vt<int>> bruh;
    vt<vt<int>> garbage;
    // return 0;
    strongly_connected_components(edges, bruh, garbage);
    // GFG g;
    // auto bruh = g.findSCC(n, edges);
    // cout << bruh << endl;
    // return 0;
    vt<int> which(n+1);
    F0R(i, bruh.size()) {
        trav(x, bruh[i]) which[x]=i;
    }
    // cout << bruh << which << endl;
    vt<int> ord;
    vt<vt<int>> adj(bruh.size());
    vt<vt<int>> ed;
    F0R(i, n) trav(x, edges[i]) {
        ed.add({i,x});
    }
    trav(x, ed) {
        // cout << x << which[x[0]] << " " << which[x[1]] << endl;
        if(which[x[0]]==which[x[1]]) continue;
        // else adj.add({which[x[0]], which[x[1]]});
        else adj[which[x[0]]].add(which[x[1]]);
    }
    // cout << adj << endl;
    // return 0;
    vt<int> in(bruh.size());
    F0R(i, bruh.size()) trav(x, adj[i]) in[x]++;
    deque<int> dq;
    F0R(i, bruh.size()) if(in[i]==0) {
        dq.push_back(i);
        ord.add(i);
    }
    // return 0;
    while(dq.size()) {
        auto tp = dq.front();
        dq.pop_front();
        trav(x, adj[tp]) {
            in[x]--;
            if(in[x]==0) {
                dq.push_back(x);
                ord.add(x);
            }
        }
    }
    // return 0;
    vt<vt<int>> rev(bruh.size());
    F0R(i, bruh.size()) trav(x, adj[i]) {
        rev[x].add(i);
    }
    F0R(i, bruh.size()) assert(rev[i].size()<=1);
    vt<int> dp(bruh.size());
    F0R(i, bruh.size()) if(rev[i].size()==0) dp[i]=1;
    R0F(i, bruh.size()) {
        dp[ord[i]]=1;
        trav(x, adj[ord[i]]) {
            dp[ord[i]]*=dp[x];
            dp[ord[i]]%=mod;
        }
        dp[ord[i]]++;
    }
    int ans = 1;
    F0R(i, ord.size()) if(rev[i].size()==0) {
        ans*=dp[i];
        ans%=mod;
    }
    ans--;
    ans%=mod;
    ans+=mod;
    ans%=mod;
    cout << ans << endl;
    return 0;
<<<<<<< Updated upstream
}
/*
x=1
lose: a[i+1]-a[i]
gain: sum(a[0], a[min(i-1),x-1])


*/
=======
}
>>>>>>> Stashed changes
