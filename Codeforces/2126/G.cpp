#pragma GCC optimize("O3,unroll-loops")
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
// #define int long long
#define vt vector
#define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct SegTree {
    int n;       // original array size
    int size;    // internal tree size (power of two)
    int log;     // levels
    vector<ll> mn, mx, lazy;

    SegTree(int _n): n(_n) {
        log = 0;
        while ((1u << log) < n) ++log;
        size = 1 << log;
        mn.assign(2*size, LLONG_MAX);
        mx.assign(2*size, LLONG_MIN);
        lazy.assign(2*size, 0);
    }

    // Build leaves and compute parents in O(n)
    void build(vector<int>& a) {
        // leaves
        for (int i = 0; i < n; i++) {
            mn[size + i] = mx[size + i] = a[i];
        }
        for (int i = n; i < size; i++) {
            mn[size + i] = LLONG_MAX;
            mx[size + i] = LLONG_MIN;
        }
        // internal nodes
        for (int i = size - 1; i > 0; --i) {
            pull(i);
        }
        // clear lazy
        fill(lazy.begin(), lazy.end(), 0);
    }

    // apply add to a node
    void apply(int p, ll v) {
        mn[p] += v;
        mx[p] += v;
        lazy[p] += v;
    }

    // recalc from children
    void pull(int p) {
        mn[p] = min(mn[p<<1], mn[p<<1|1]);
        mx[p] = max(mx[p<<1], mx[p<<1|1]);
    }

    // push pending tags down one level
    void push(int p) {
        if (lazy[p] != 0) {
            apply(p<<1, lazy[p]);
            apply(p<<1|1, lazy[p]);
            lazy[p] = 0;
        }
    }

    // push tags from root down to p (exclusive)
    void push_to(int p) {
        for (int h = log; h > 0; --h) {
            int parent = p >> h;
            push(parent);
        }
    }

    // pull updates from p to root
    void pull_to(int p) {
        while (p > 1) {
            p >>= 1;
            pull(p);
            // reapply lazy for correctness
            if (lazy[p] != 0) {
                mn[p] += lazy[p];
                mx[p] += lazy[p];
            }
        }
    }

    // add x to [l..r]
    void add(int l, int r, ll x) {
        if (l > r) return;
        l += size;
        r += size;
        int l0 = l, r0 = r;
        // push down for boundaries
        push_to(l0);
        push_to(r0);
        
        // apply on segments
        while (l <= r) {
            if (l & 1) apply(l++, x);
            if (!(r & 1)) apply(r--, x);
            l >>= 1;
            r >>= 1;
        }
        // update affected parents
        pull_to(l0);
        pull_to(r0);
    }

    // query minimum in [l..r]
    ll getMin(int l, int r) {
        l += size;
        r += size;
        push_to(l);
        push_to(r);
        ll res = LLONG_MAX;
        while (l <= r) {
            if (l & 1) res = min(res, mn[l++]);
            if (!(r & 1)) res = min(res, mn[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

    // query maximum in [l..r]
    ll getMax(int l, int r) {
        l += size;
        r += size;
        push_to(l);
        push_to(r);
        ll res = LLONG_MIN;
        while (l <= r) {
            if (l & 1) res = max(res, mx[l++]);
            if (!(r & 1)) res = max(res, mx[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};
// SegTree st(2e5+2);
bool poss(int x, vt<int> &a, vt<vt<int>> &inv, SegTree& st, vt<int> &start) {
    int n = a.size();
    st.build(start);
    vt<int> nxt(n), prv(n);
    F0R(i, n) {
        prv[i]=i-1;
        nxt[i]=i+1;
    }
    nxt[n-1]=-1;
    int las = 0;
    F0R(mn, n-x+1) {
        while(las<min(n,mn+x)) {
            trav(xx, inv[las]) {
                if(prv[xx]!=-1) nxt[prv[xx]]=nxt[xx];
                if(nxt[xx]!=-1) prv[nxt[xx]]=prv[xx];
                st.add(xx+1, n, -2);
            }
            ++las;
        }
        trav(xx, inv[mn]) { 
            int lb = nxt[xx];
            if(lb!=-1) {
                auto least_bef = st.getMin(0, xx);
                auto largest_aft = st.getMax((lb)+1, n);
                if(largest_aft>=least_bef) return true;
            }
            lb=prv[xx];
            if(lb==-1) continue;
            auto least_bef = st.getMin(0, lb);
            auto largest_aft = st.getMax(xx+1, n);
            if(largest_aft>=least_bef) return true;
        }
    }
    return false;
}
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
        F0R(i, n) {
            a[i]--;
        }
        vt<vt<int>> inva(n);
        F0R(i, n) {
            inva[a[i]].add(i);
        }
        int lo = 0, hi = n;
        SegTree st(n+1);
        vt<int> start(n+1);
        F0R(i, n) start[i+1]=i+1;
        // poss(3, a, inva);
        while(lo+1<hi) {
            // cout << lo << " " << hi << endl;
            int mid = (lo+hi)/2;
            if(poss(mid, a, inva, st, start)) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}