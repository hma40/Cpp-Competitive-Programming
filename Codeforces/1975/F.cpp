#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n;
vt<vt<int>> hr;
vt<int> constraints;
pair<int,int> solve(int x, vt<int> &ans) {
    if(x==n) {
        return {ans.size(),ans.size()-1};
    }
    int start = ans.size();
    FOR(i, 1, 1<<(n-x-1)) {
        int raised = i<<(x+1);
        hr[x][i]=constraints[raised];
    }
    vt<int> ret;
    FOR(i, 1, 1<<(n-x-1)) {
        int raised = i<<(x+1);
        constraints[raised]=constraints[raised]&(constraints[raised|(1<<x)]>>1);
    }
    if(constraints[1<<x]&2) {
        auto inc = solve(x+1,ans);
        FOR(i, inc.f, inc.s+1) {
            ans[i]^=(1<<x);
        }
    }
    FOR(i, 1, 1<<(n-x-1)) {
        int raised = i<<(x+1);
        constraints[raised]=hr[x][raised>>(x+1)];
    }
    FOR(i, 1, 1<<(n-x-1)) {
        int raised= i<<(x+1);
        constraints[raised]=constraints[raised]&(constraints[raised|(1<<x)]);
    }
    if(constraints[1<<x]&1) {
        solve(x+1, ans);
    }
    FOR(i, 1, 1<<(n-x-1)) {
        int raised= i<<(x+1);
        constraints[raised]=hr[x][raised>>(x+1)];
    }
    bool good = true;
    FOR(i, 1, 1<<(n-x)) {
        int raised = i<<x;
        if(raised&(1<<x)) {
            if(constraints[raised]&2) {

            } else {
                good=false;
            }
        } else {
            if(constraints[raised]&1) {

            } else {
                good=false;
            }
        }
    }
    if(good) ans.add(1<<x);
    return {start, ans.size()-1};
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    F0R(i, 20) {
        hr.add(vector<int>(1<<(19-i)));
    }
    cin >> n;
    constraints.resize(1<<n);
    FOR(i, 1, 1<<n) cin >> constraints[i];
    vt<int> x;
    solve(0,x);
    bool good = true;
    FOR(i, 1, 1<<n) if(constraints[i]&1) {} else good=false;
    if(good) x.add(0);
    sort(begin(x),end(x));
    cout << x.size() << endl;
    trav(y, x) cout << y << endl;
    return 0;
}