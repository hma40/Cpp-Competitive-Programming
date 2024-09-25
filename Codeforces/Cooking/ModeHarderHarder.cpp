#include <bits/stdc++.h>
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
int n;
vector<int> a;
vector<vector<int>> adj;
map<int, set<int>> invFreq;
vector<int> freq;
int an[200001];
void solve(int node) {
    int most = (*invFreq.rbegin()).f;
    auto l = invFreq.begin();
    auto r = invFreq.rbegin();
    // l++;
    int mn = inf, mx = -inf;
    int ans = 0;
    while(true) {
        while((*l).f+(*r).f>=most) {
            mn=min(mn, *((*r).s.begin()));
            mx = max(mx, *((*r).s).rbegin());
            if((*r).f!=(*invFreq.begin()).f) {
                ++r;
            } else {
                break;
            }
        }
        if((*l).f+(*r).f<most) {
            r--;
        }
        ans=max(ans, (*(*l).s.rbegin())-mn);
        ans=max(ans, mx-*((*l).s.begin()));
        l++;
        if(l==invFreq.end()) break;
    }
    an[node]=ans;
}
void dfs(int node, int par) {
    for(auto x: adj[node]) {
        if(x==par) continue;
        if(freq[a[x]]!=0) {
            invFreq[freq[a[x]]].erase(x);
            if(invFreq[freq[a[x]]].size()==0) invFreq.erase(freq[a[x]]);
        }
        freq[a[x]]++;
        invFreq[freq[a[x]]].insert(x);
        solve(x);
        dfs(x, node);
    }
    invFreq[freq[a[node]]].erase(node);
    if(invFreq[freq[a[node]]].size()==0) {
        invFreq.erase(freq[a[node]]);
    }   
    freq[a[node]]--;
    invFreq[freq[a[node]]].insert(node);
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
        a.assign(n,0);
        adj.assign(n, vt<int>());
        invFreq.clear();
        freq.assign(n, 0);
        F0R(i, n-1) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            adj[x].add(y);
            adj[y].add(x);
        }
        freq[a[0]]++;
        invFreq[freq[a[0]]].insert(0);
        dfs(0,-1);
        FOR(i, 1, n) cout << an[i] << " ";
        cout << endl;
    }
    return 0;
}