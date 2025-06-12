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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<pair<int,int>> adj;
int max_sum(int sz, int depth) {
    //sz-1 of depth, sz-2 of depth+1, ..., 1 of depth+sz-1
    /*
    
    (sz-1)(depth)+(sz-2)(depth+1)+(sz-3)(depth+2)+...+(1)(depth+sz-2)
    last one is (sz-(sz-1))(depth+(sz-2))
    szdepth-depth
    szdepth+sz-2depth-2
    szdepth+2sz-3depth-6
    szdepth+3sz-4depth-12

    
    ...
    szdepth+(sz-2)(sz)-(sz-1)(depth)-(sz-1)(sz-2)

    sum of n(n+1) until sz-2

    n^2+n

    (sz-2)(sz-1)(2sz-3)/6
    
    so when sz=3 and depth=1
    (2)(1)+(1)(2)=4
    (3-1)(1+0)+(3-2)(1+1)+...
    (3)(1)(2) = 6
    (3)(0)+(3)(1) = 3
    (-1)(1) + (-2)(1) = -3
    (-2)=-2
    */
    int ans = sz*depth*(sz-1);
    ans+=sz*(sz-1)*(sz-2)/2;
    ans-=depth*(sz)*(sz-1)/2;
    ans-=(sz-2)*(sz-1)*(2*sz-3)/6;
    ans-=(sz-2)*(sz-1)/2;
    return ans;
}
void solve(int par, int start, int end, int depth, int k) {
    // cout << par << " " << start << " " << end << " " << depth << " " << k << endl;
    //add a node directly to par
    int node = end-start+1;
    if(node==0) return;
    if(max_sum(node-1, depth+1)+(node-1)*depth+1>=k) {
        // cout << "LINE 183" << endl;
        adj.push_back({par, start});
        solve(par, start+1, end, depth, k-(node-1)*(depth));
    } else {
        // cout << "LINE 187" << endl;
        adj.push_back({par, start});
        k-=(node-1)*(depth+1);
        solve(start, start+1, end, depth+1, k);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // int sz,depth;
    // cin >> sz >> depth;
    // cout << max_sum(sz,depth) << endl;
    // return 0;
    int t = 1;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        // cout << max_sum(n-1,0) << endl;
        // int mx = (n-2)*(n-1)/2;
        // cout << max_sum(n,0) << endl;
        if(max_sum(n, 0)<k-1) {
            cout << "No" << endl;
            continue;
        }
        adj = vt<pair<int,int>>();
        solve(1,2,n,0,k);
        // cout << adj << endl;
        cout << "Yes" << endl;
        trav(x, adj) cout << x.f << " " << x.s << endl;
    }
    return 0;
}