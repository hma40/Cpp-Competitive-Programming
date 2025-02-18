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
const ll mod = 1000000007;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n,m;
int comp(int x, int y ){
    if(x<0||y<0||x>=n||y>=n) return n*n;
    return x*n+y;
}
vt<vt<bool>> vis;
bool good(int x, int y) {
    return x>=0&&y>=0&&x<n&&y<n&&!vis[x][y];
};
bool check(int x, int y) {
    return x<0||y<0||x>=n||y>=n||vis[x][y];
};
int ans;
deque<pair<int,int>> dq;
vt<vt<char>> a;
void bfs() {
    while(dq.size()) {
        auto tp = dq.front();
        // cout << "LINE 209 " << tp << endl;
        dq.pop_front();
        if(good(tp.f,tp.s+1)) {
            if(a[tp.f][tp.s+1]=='L'||a[tp.f][tp.s+1]=='.') {
                // cout << "LINE 221 " << endl;
                vis[tp.f][tp.s+1]=true;
                ans--;
                dq.push_back({tp.f,tp.s+1});
            }
        }
        if(good(tp.f,tp.s-1)) {
            if(a[tp.f][tp.s-1]=='R'||a[tp.f][tp.s-1]=='.') {
                // cout << "LINE 229 " << endl;
                vis[tp.f][tp.s-1]=true;
                ans--;
                dq.push_back({tp.f,tp.s-1});
            }
        }
        if(good(tp.f+1,tp.s)) {
            if(a[tp.f+1][tp.s]=='U'||a[tp.f+1][tp.s]=='.') {
                // cout << "LINE 237 " << endl;
                vis[tp.f+1][tp.s]=true;
                ans--;
                dq.push_back({tp.f+1,tp.s});
            }
        }
        if(good(tp.f-1,tp.s)) {
            if(a[tp.f-1][tp.s]=='D'||a[tp.f-1][tp.s]=='.') {
                // cout << "LINE 245 " << endl;
                vis[tp.f-1][tp.s]=true;
                ans--;
                dq.push_back({tp.f-1,tp.s});
            }
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    cin >> n >> m;
    vector<pair<int,int>> v;
    a.resize(n, vt<char>(n, '.'));
    F0R(i, m) {
        int r,c;
        char t;
        cin >> r >> c >> t;
        r--;
        c--;
        a[r][c]=t;
        v.add({r,c});
    }
    ans = n*n;
    // deque<pair<int,int>> dq;
    vis.resize(n,vt<bool>(n));
    vt<pair<int,int>> dirs = {{-1,0},{0,1},{0,-1},{1,0}};
    F0R(i, n) {
        if(a[0][i]=='U'||a[0][i]=='.') {
            if(!vis[0][i]) {
            // if(vis[0][i]) continue;
            ans--;
            vis[0][i]=true;
            dq.push_back({0,i});
            }
        }
        if(a[n-1][i]=='D'||a[n-1][i]=='.') {
            if(!vis[n-1][i]) {
            ans--;
            vis[n-1][i]=true;
            dq.push_back({n-1,i});
            }
        }
        if(a[i][0]=='L'||a[i][0]=='.') {
            if(!vis[i][0]) {
            ans--;
            vis[i][0]=true;
            dq.push_back({i,0});
            }
        }
        if(a[i][n-1]=='R'||a[i][n-1]=='.') {
            if(!vis[i][n-1]) {
            ans--;
            vis[i][n-1]=true;
            dq.push_back({i,n-1});
            }
        }
    }
    bfs();
    reverse(begin(v),end(v));
    vt<int> an;
    F0R(i,m) {
        // cout << "LINE 256 " << i << endl;
        an.add(ans);
        a[v[i].f][v[i].s]='.';
        if(vis[v[i].f][v[i].s]) continue;
        if(check(v[i].f-1,v[i].s)||check(v[i].f+1,v[i].s)||check(v[i].f,v[i].s+1)||check(v[i].f,v[i].s-1)) {
            vis[v[i].f][v[i].s]=true;
            dq.push_back({v[i].f,v[i].s});
            ans--;
            bfs();
        }
    }
    R0F(i, m) cout << an[i] << endl;
    return 0;
}
/*
3 6
2 3 D
3 3 L
1 2 L
1 3 R
2 2 U
2 1 L

.LR
LUD
..L
*/