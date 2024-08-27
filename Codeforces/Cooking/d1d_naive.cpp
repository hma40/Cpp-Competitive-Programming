#include <bits/stdc++.h>
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
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
int n,k;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<vt<int>> allPoss;
void cont(int pos, vt<int> v) {
    if(pos>n) {
        allPoss.add(v);
        return;
    }
    for(int i = 1; i <= n+k; i++) {
        vt<int> temp = v;
        temp[pos]=i;
        cont(pos+1, temp);
    }
}
void gen_all() {
    vt<int> fun(n+k+1);
    FOR(i, n+1, n+k+1) {
        fun[i]=i;
    }
    cont(1, fun);
}
bool works(vt<int> func) {
    vt<int> appliedFunc(n+k+1);
    F0R(i, n+k+1) appliedFunc[i]=i;
    F0R(iters, n) {
        F0R(j, n+k+1) {
            appliedFunc[j]=func[appliedFunc[j]];
        }
    }
    bool good = true;
    for(int i = 1; i <= n; i++) {
        if(appliedFunc[i]<=n) good=false;
    }
    for(int i = 1; i < n; i++) {
        if(appliedFunc[i]>appliedFunc[i+1]) good=false;
    }
    return good;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // int n,k;
    cin >> n >> k;
    gen_all();
    // cout << allPoss << allPoss.size() << endl;
    int ans = 0;
    for(auto x: allPoss) {
        if(works(x)) {
            // cout << x << endl;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}