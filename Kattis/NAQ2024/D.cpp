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
int n;
vt<int> col;
vt<vt<pair<int,int>>> adj;
vt<int> ans;
vt<int> colCount;
vt<map<int,int>> v(100001);
//return map, answer
int dfs(int node, int par) {
    int ansHere = 0;
    trav(xx, adj[node]) {
        if(xx.f==par) continue;
        auto temp = dfs(xx.f, node);
        ans[xx.s]=temp;

        if(v[xx.f].size()>v[node].size()) {
            swap(v[node], v[xx.f]);
            swap(ansHere, temp);
        }
        //now, add temp.f to here
        trav(x, v[xx.f]) {
            if(v[node].count(x.f)) {
                auto cnt = v[node][x.f];
                ansHere-=cnt*(colCount[x.f]-cnt);
                v[node][x.f]+=x.s;
                cnt=v[node][x.f];
                ansHere+=cnt*(colCount[x.f]-cnt);
            } else {
                ansHere+=x.s*(colCount[x.f]-x.s);
                v[node][x.f]+=x.s;
            }
        }
    }
    if(v[node].count(col[node])) {
        auto cnt = v[node][col[node]];
        ansHere-=cnt*(colCount[col[node]]-cnt);
        v[node][col[node]]++;
        cnt++;
        ansHere+=cnt*(colCount[col[node]]-cnt);     
    } else {
        ansHere+=colCount[col[node]]-1;
        v[node][col[node]]++;
    }
    // cout << node << " " << par << " RETURNING " << here << " " << ansHere << endl;
    return ansHere;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    cin >> n;
    col.resize(n);
    adj.resize(n);
    colCount.resize(n);
    ans.resize(n);
    F0R(i, n) cin >> col[i];
    F0R(i, n-1) {
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].add({y,i});
        adj[y].add({x,i});
    }
    F0R(i, n) {
        col[i]--;
        colCount[col[i]]++;
    }
    dfs(0,-1);
    // cout << ans << endl;
    F0R(i, n-1) cout << ans[i] << endl;
    return 0;
}