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
set<pair<int,int>> sections;
set<int> active;
struct DSU {
    int n;
    vector<int> sz, par, mn, mx;
    DSU(int nn) {
        this->n=nn;
        sz.resize(n, 1);
        par.resize(n, -1);
        F0R(i, n) {
            mn.add(i);
            mx.add(i);
        }
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int i, int j) {
        i=find(i);
        j=find(j);
        if(i==j) return;
        if(sz[i]>sz[j]) swap(i,j);
        sections.erase({-sz[i], mn[i]});
        sections.erase({-sz[j], mn[j]});
        sz[j]+=sz[i];
        par[i]=j;
        mn[j]=min(mn[j], mn[i]);
        mx[j]=max(mx[j], mx[i]);
        sections.insert({-sz[j], mn[j]});
    }
};
int n;
vt<int> a;
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    cin >> n;
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    a.resize(n);
    F0R(i, n) cin >> a[i];
    F0R(i, n) active.insert(i);
    DSU d(n);
    F0R(i, n) {
        sections.insert({-1, i});
    }
    FOR(i, 1, n) {
        if(a[i]==a[i-1]) d.unite(i-1,i); 
    }
    active.insert(-inf);
    active.insert(inf);
    int ans = 0;
    while(sections.size()) {
        auto f = *(sections.begin());
        sections.erase(f);
        int nxt = f.s;
        F0R(i, -f.f) {
            int cur = nxt;
            nxt=(*active.upper_bound(cur));
            active.erase(cur);
        }
        // cout << active << sections << endl;
        ans++;
        auto ub = active.upper_bound(f.s);
        auto lb = active.upper_bound(f.s);
        --lb;
        // cout << (*ub) << " " << (*lb) << endl;
        if((*ub)==inf||(*lb)==-inf) continue;
        if(a[*ub]==a[*lb]) {
            d.unite((*ub), (*lb));
        }
    }
    cout << ans << endl;
    return 0;
}
/*
10
4 1 5 8 8 5 1 1 5 4 
4 1 5 5 1 1 5 4
4 1 1 1 5 4
4 5 4
5 4
4

*/