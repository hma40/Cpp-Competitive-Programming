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
struct DSU {
    int n;
    int comps;
    vt<int> par;
    vt<int> sz;
    DSU(int nn) {
        n=nn;
        comps=nn;
        par.resize(nn, -1);
        sz.resize(nn, 1);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void connect(int i, int j) {
        i=find(i);
        j=find(j);
        if(sz[i]>sz[j]) swap(i,j);
        sz[j]+=sz[i];
        par[i]=j;
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
        vt<set<int>> adj(n);
        F0R(i, m) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].insert(b);
            adj[b].insert(a);
        }
        deque<int> dq;
        vt<bool> vis(n);
        vt<array<int,3>> operations;
        F0R(i, n) {
            if(vis[i]) continue;
            vt<int> here;
            set<int> two;
            dq.push_back(i);
            here.add(i);
            while(dq.size()) {
                auto f = dq.front();
                dq.pop_front();
                trav(x, adj[f]) {
                    if(vis[x]) continue;
                    vis[x]=true;
                    dq.push_back(x);
                    here.add(x);
                }
            }
            trav(x, here) {
                if(adj[x].size()>1) {
                    two.insert(x);
                }
            }
            while(two.size()) {
                auto f = *(two.begin());
                auto fir = *(adj[f].begin()), last = *(adj[f].rbegin());
                operations.add({f, fir, last});
                adj[f].erase(fir);
                adj[f].erase(last);
                adj[fir].erase(f);
                adj[last].erase(f);
                if(adj[fir].count(last)) {
                    adj[fir].erase(last);
                    adj[last].erase(fir);
                } else {
                    adj[fir].insert(last);
                    adj[last].insert(fir);
                }
                two.erase(f);
                two.erase(fir);
                two.erase(last);
                if(adj[f].size()>1) two.insert(f);
                if(adj[fir].size()>1) two.insert(fir);
                if(adj[last].size()>1) two.insert(last);
            }
        }
        DSU d(n);
        pair<int,int> start = {-1,-1};
        F0R(i, n) {
            trav(x, adj[i]) {
                if(x>i) d.connect(i, x);
                start={i,x};
            }
        }
        if(start.f==-1) {
            cout << operations.size() << endl;
            trav(x, operations) cout << 1+x[0] << " " << 1+x[1] << " " << 1+x[2] << endl;
            continue;
        }
        F0R(i, n) {
            if(d.find(i)==d.find(start.f)) continue;
            operations.add({start.f, start.s, i});
            start={start.f, i};
            d.connect(start.f, i);
        }
        cout << operations.size() << endl;
        trav(x, operations) cout << 1+x[0] << " " << 1+x[1] << " " << 1+x[2] << endl;
    }
    return 0;
}