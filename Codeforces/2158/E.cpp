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
// your original is_iterable (unchanged)
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// detect std::basic_string<...>
template <typename T>
struct is_string : std::false_type {};

template <typename CharT, typename Traits, typename Alloc>
struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type {};

// optionally also detect string_view (C++17)
template <typename CharT, typename Traits>
struct is_string<std::basic_string_view<CharT, Traits>> : std::true_type {};

// now enable the generic container printer only when T is iterable AND not a string
template <typename T>
typename std::enable_if<
    is_iterable<T>::value && !is_string<T>::value,
    std::ostream&
>::type
operator<<(std::ostream& os, const T& container) {
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
const ll mod = 998244353;
const ll inf = 1e18;
template<typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>; //defines min_pq
int ans;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rand_num(int l, int r) {
    return rnd()%(r-l+1)+l;
}
struct DSU {
    int n;
    vt<int> par, sz, with;
    vt<bool> counted;
    DSU(int nn): n(nn), par(nn, -1), sz(nn,1), with(nn, 1), counted(nn,1){};
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int u, int v) {
        u=find(u), v=find(v);
        if(u==v) return;
        if(sz[u]>sz[v]) swap(u,v);
        par[u]=v;
        sz[v]+=sz[u];
        if(counted[u] || counted[v]) ans--;
        counted[v]=counted[v]&&counted[u];
        with[v]+=with[u];
        
        with[u]=0;
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
        int n,m;
        cin >> n >> m;
        vt<vt<int>> a(n, vt<int>(m));
        vt<vt<int>> cur(n, vt<int>(m));
        F0R(i, n) F0R(j, m) cin >> a[i][j];
        vt<pair<int,int>> d = {{-1,0},{1,0},{0,-1},{0,1}};
        int q;
        cin >> q;
        DSU ds(n*m+q);
        ans=n*m;
        int nxt = 0;
        F0R(i, n) F0R(j, m) {
            cur[i][j]=nxt++;
            ds.with[cur[i][j]]++;
        }
        F0R(i, n) F0R(j, m) {
            trav(x, d) {
                pair<int,int> nw = {i+x.f,j+x.s};
                if(nw.f>=0 && nw.f<n && nw.s>=0 && nw.s<m) {
                    if(a[nw.f][nw.s]==a[i][j]) ds.unite(cur[nw.f][nw.s], cur[i][j]);
                    else if(a[nw.f][nw.s]>a[i][j] && ds.counted[ds.find(cur[nw.f][nw.s])]) {
                        ans--;
                        ds.counted[ds.find(cur[nw.f][nw.s])]=false;
                    }
                }
            }
        }
        // int ans = 0;
        cout << ans << " ";
        while(q--) {
            int i, j, x;
            cin >> i >> j >> x;
            i--,j--;
            int bef = cur[i][j];
            ds.with[ds.find(bef)]--;
            if(ds.counted[ds.find(bef)]) {
                ans--;
                ds.counted[ds.find(bef)]=false;
            }
            cur[i][j]=nxt++;
            ans++;
            // cout << "\nline 187: " << ans << endl;
            a[i][j]-=x;
            trav(xx, d) {
                pair<int,int> nw = {i+xx.f,j+xx.s};
                if(nw.f>=0 && nw.f<n && nw.s>=0 && nw.s<m) {
                    if(a[nw.f][nw.s]==a[i][j]) {
                        // if(ds.with[ds.find(cur[i][j])]==1 && ds.counted[ds.find(cur[i][j])]) ans--;
                        ds.unite(cur[nw.f][nw.s], cur[i][j]);
                    }
                    else if(a[nw.f][nw.s]>a[i][j]) {
                        if(ds.counted[ds.find(cur[nw.f][nw.s])]) {
                            ds.counted[ds.find(cur[nw.f][nw.s])]=false;
                            ans--;
                        }
                    } else {
                        if(ds.counted[ds.find(cur[i][j])]) {
                            ans--;
                            ds.counted[ds.find(cur[i][j])]=false;
                        }
                    }
                }
            }
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
1
3 4
10 10 10 10
10 10 10 10
10 10 11 10
5
3 3 5
2 2 5
2 4 5
2 3 5
1 1 9

10 10 10 10
10 5 10 5
10 10 6 10
*/