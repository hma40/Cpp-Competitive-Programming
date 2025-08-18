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
set<array<int,3>> s;
struct DSU {
    int n;
    vt<int> par, sz, left, right, val, rsize;
    DSU(vt<int> &a): n(a.size()) {
        F0R(i, n) {
            par.add(-1);
            sz.add(1);
            left.add(i);
            right.add(i);
            val.add(a[i]);
            rsize.add(1);
        }
    };
    int find(int u) {
        if(par[u]==-1) return u;
        return par[u]=find(par[u]);
    }
    void unite(int u, int v) {
        u=find(u);
        v=find(v);
        if(u==v) return;
        s.erase({val[u], left[u], right[u]});
        s.erase({val[v],left[v],right[v]});
        if(sz[u]>sz[v]) swap(u,v);
        sz[v]+=sz[u];
        par[u]=v;
        left[v]=min(left[u],left[v]);
        val[v]=max(val[u],val[v]);
        right[v]=max(right[u],right[v]);
        rsize[v]+=rsize[u];
        s.insert({val[v], left[v], right[v]});
    }
    void set_val(int x, int value) {
        int bruh = find(x);
        s.erase({val[bruh], left[bruh], right[bruh]});
        val[bruh]=value;
        s.insert({val[bruh], left[bruh], right[bruh]});
    }
    void set_rval(int x, int value) {
        int bruh = find(x);
        rsize[bruh]=value;
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
        s.clear();
        F0R(i, n) {
            cin >> a[i];
            s.insert({a[i],i,i});
        }
        DSU d(a);
        FOR(i, 1, n) if(a[i]==a[i-1]) d.unite(i-1,i);
        int ans = 0;

        while(true) {
            // cout << s << ans << endl;
            auto bot = *s.begin();

            int bruh = d.find(bot[1]);
            if(s.size()==1 && d.rsize[bruh]==1) {
                break;
            }
            if(d.rsize[bruh]!=1) {
                if(d.rsize[bruh]&1) ans++;
                d.set_val(bruh, d.val[bruh]+1);
                d.set_rval(bruh, (d.rsize[bruh]+1)/2);
                if(d.left[bruh]!=0 && d.val[d.find(d.left[bruh]-1)]==d.val[bruh]) {
                    d.unite(d.left[bruh]-1, d.left[bruh]);
                }
                if(d.right[bruh]!=n-1 && d.val[d.find(d.right[bruh]+1)]==d.val[bruh]) {
                    d.unite(d.right[bruh]+1, d.right[bruh]);
                }
            } else {
                int left = inf, right = inf;
                if(d.left[bruh]!=0) {
                    left=d.val[d.find(d.left[bruh]-1)];
                }
                if(d.right[bruh]!=n-1) {
                    right=d.val[d.find(d.right[bruh]+1)];
                }
                if(left<right) {
                    ans+=left-d.val[bruh];
                    d.unite(d.left[bruh]-1, d.left[bruh]);
                } else if(left>right) {
                    ans+=right-d.val[bruh];
                    d.unite(d.right[bruh]+1, d.right[bruh]);
                } else {
                    ans+=left-d.val[bruh];
                    d.unite(d.left[bruh]-1, d.left[bruh]);
                    d.unite(d.right[bruh]+1, d.right[bruh]);
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}