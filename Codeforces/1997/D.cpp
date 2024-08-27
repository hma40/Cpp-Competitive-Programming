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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

int n;
vt<int> par;
vt<vt<int>> chil;
vt<int> points;
bool dfs(int node, int amt) {
    if(amt>inf) amt=inf;
    //returns true if it is possible to make everything in this subtree at least amt
    // bool good = true;
    if(chil[node].size()==0) {
        if(points[node]<amt) return false;
        else return true;
    }
    if(points[node]>=amt) {
        trav(x, chil[node]) {
            if(!dfs(x, amt)) return false;
        }
    } else {
        int extras = amt-points[node];
        trav(x, chil[node]) {
            if(!dfs(x, amt+extras)) return false;
        }
    }
    return true;
}
bool poss(int ty) {
    if(points[0]>=ty) return true;
    int need = ty-points[0];
    trav(x, chil[0]) {
        if(!dfs(x,need)) return false;
    }
    return true;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n;
        par.assign(n,-1);
        chil.assign(n, vt<int>());
        points.assign(n, 0);
        F0R(i, n) cin >> points[i];
        FOR(i, 1, n) {
            cin >> par[i];
            par[i]--;
            chil[par[i]].add(i);
        }
        int lo = 0, hi = inf;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(poss(mid)) { 
                lo=mid;
            } else {
                hi=mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}