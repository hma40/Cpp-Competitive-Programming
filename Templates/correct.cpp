// include
#include<bits/stdc++.h>

using namespace std;

// define
#define fi    first
#define se    second

#define pub   push_back
#define pob   pop_back
#define puf   push_front
#define pof   pop_front
#define eb    emplace_back
#define upb   upper_bound
#define lwb   lower_bound

#define left  VAN
#define right TAN

#define sz(a)               (int)a.size()
#define all(a)              (a).begin(),(a).end()
#define rall(a)             (a).begin(),(a).end()
#define sort_and_unique(a)  sort(all(a));(a).resize(unique(all(a))-a.begin())
#define max_                max_element
#define min_                min_element

// another define
using ll  = long long;
using ld  = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
using mii = map<int, int>;
using mil = map<int, ll>;
using mli = map<ll, int>;
using mll = map<ll, ll>;
using vi  = vector<int>;
using vl  = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

// random
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// templates
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (y > x) {
            x = y;
            return (true);
        } else return (false);
    }

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (y < x) {
            x = y;
            return (true);
        } else return (false);
    }

template<class T>
    void print(const T &a, const int &l, const int &r) {
        for (int i = l; i <= r; i++)
            cout << a[i] << ' ';
        cout << '\n';
    }

// limit
const int oo = 2e9;
const ll MOD = 998244353;

// power MOD
template<class X, class Y>
    X power(const X &x, const Y &y) {
        assert(y >= 0);
        X a = x % MOD, res = 1;
        Y b = y;
        while (b > 0) {
            if (b & 1) {
                res *= a;
                res %= MOD;
            }
            a *= a;
            a %= MOD;
            b >>= 1;
        }
        return (res);
    }


// function
void yesno(bool x) {
    cout << (x ? "YES\n" : "NO\n");
}

void solve() {
    int n;
    cin >> n;
    vvi adj(n + 5);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pub(v);
        adj[v].pub(u);
    }
    vl d(n + 5, oo);
    auto dfs1 = [&](auto dfs1, int fa, int u) -> void {
        for (int v : adj[u])
        if (v != fa) {
            dfs1(dfs1, u, v);
            minimize(d[u], d[v] + 1);
        }
        if (d[u] == oo) {
            d[u] = 0;
        }
    };
    dfs1(dfs1, 0, 1);
    vl p(n + 5, 0);
    p[1] = 1;
    auto dfs2 = [&](auto dfs2, int fa, int u) -> void {
        for (int v : adj[u])
        if (v != fa) {
                p[v] = p[u] * d[v] % MOD * power(d[v] + 1ll, MOD - 2) % MOD;
            dfs2(dfs2, u, v);
        }
    };
    dfs2(dfs2, 0, 1);
    for (int i = 1; i <= n; i++)
        cout << p[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;

    while (t--) solve();
    return 0;
}

