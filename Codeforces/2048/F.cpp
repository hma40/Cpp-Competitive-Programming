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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=min(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
RMQ r({}, 0);
struct DSU {
    vt<int> par,sz;
    vt<vt<int>> dp;
    vt<int> left,right;
    DSU(vt<int> &a, vt<int> &b) {
        int n = a.size();
        r=RMQ(b, 20);
        par.resize(n, -1);
        sz.resize(n, 1);
        dp.resize(n, vt<int>(62));
        F0R(i, n) {
            left.add(i);
            right.add(i);
            dp[i][0]=a[i];
        }
        FOR(i, 1, 62) {
            F0R(j, n) {
                dp[j][i]=(dp[j][i-1]+b[j]-1)/b[j];
            }
        }
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(sz[x]>sz[y]) swap(x,y);
        par[x]=y;
        sz[y]+=sz[x];
        left[y]=min(left[y],left[x]);
        right[y]=max(right[y],right[x]);
        vt<int> nwdp(62);
        int div = r.getMin(left[y],right[y]);
        F0R(i, 62) {
            int here = inf*2;
            F0R(j, i+1) {
                int k = i-j;
                here=min(here, max(dp[x][j], dp[y][k]));
            }
            nwdp[i]=here;
            if(i!=0) nwdp[i]=min(nwdp[i], (nwdp[i-1]+div-1)/div);
        }
        dp[y]=nwdp;
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
        int n;
        cin >> n;
        vt<int> a(n), b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        DSU d(a,b);
        set<int> active;
        priority_queue<pair<int,int>> pq;
        F0R(i, n) {
            pq.push({b[i],i});
        }
        while(pq.size()) {
            auto tp = pq.top();
            // cout << tp << endl;
            pq.pop();
            active.insert(tp.s);
            if(active.count(tp.s+1)) {
                d.unite(tp.s,tp.s+1);
            }
            if(active.count(tp.s-1)) {
                d.unite(tp.s,tp.s-1);
            }
            // cout << d.dp << endl << d.par << endl;
        }
        int rep = d.find(0);
        int ans = inf;
        F0R(i, 62) {
            // cout << rep << " " << d.dp[rep][i] << endl;
            if(d.dp[rep][i]==1) {
                ans=i;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}