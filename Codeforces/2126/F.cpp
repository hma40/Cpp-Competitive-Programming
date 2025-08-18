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
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// const int B = 100;
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> a(n);
        vt<vt<pair<int,int>>> adj(n);
        F0R(i, n) cin >> a[i];
        ll sum = 0;
        F0R(i, n-1) {
            ll u,v,c;
            cin >> u >> v >> c;
            u--;
            v--;
            sum+=2*c;
            adj[u].add({v,c});
            adj[v].add({u,c});
        }

        vt<int> cnt(n);
        F0R(i, n) cnt[(int)adj[i].size()]++;
        int B = 0, tot = 0;
        F0R(i, n) {
            tot+=cnt[i];
            if(n-tot<=50000) {
                B=i;
                break;
            }
        }
        vt<vt<pair<int,int>>> heavy(n);
        F0R(i, n) {
            trav(x, adj[i]) {
                if(adj[x.f].size()>B) {
                    heavy[i].add(x);  
                } 
            }
        }
        // int hcount = 0;
        // F0R(i, n) if(adj[i].size()>B) hcount++;
        // assert(hcount<=1000);
        vt<map<int,ll>> mps(n);
        F0R(i, n) {
            if(adj[i].size()<=B) {
                trav(x, adj[i]) {
                    mps[x.f][a[i]]+=x.s;
                }
            }
        }
        auto get = [&](int u)->ll{
            ll an = 0;
            if(mps[u].count(a[u])) {
                an = mps[u][a[u]];
            }
            trav(x, heavy[u]) {
                if(a[x.f]==a[u]) an+=x.s;
            }
            // cout << "LINE 208: " << u << " " << an << endl;
            return an;
        };
        ll ans = 0;
        F0R(i, n) ans+=get(i);
        // assert(false);
        while(q--) {
            int v,xx;
            cin >> v >>xx;
            v--;
            ans-=2*get(v);
            if(adj[v].size()<=B) {
                trav(x, adj[v]) {
                    mps[x.f][a[v]]-=x.s;
                    if(mps[x.f][a[v]]==0) {
                        mps[x.f].erase(a[v]);
                    }
                }
            }
            a[v]=xx;
            ans+=2*get(v);
            if(adj[v].size()<=B) {
                trav(x, adj[v]) {
                    mps[x.f][a[v]]+=x.s;
                }
            }
            cout << (sum-ans)/2 << endl;
        }
    }
    return 0;
}
/*
when you update a vertex
lets manually check all heavy nearby vertices
for light ones I guess we can just check manually
*/