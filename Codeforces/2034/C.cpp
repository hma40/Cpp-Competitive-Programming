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
bool surrounded(vt<string> &a, vt<vt<bool>> &vis, int x, int y) {
    if(x!=0&&!vis[x-1][y]) return false;
    if(x!=a.size()-1&&!vis[x+1][y]) return false;
    if(y!=0&&!vis[x][y-1]) return false;
    if(y!=a[0].size()-1&&!vis[x][y+1]) return false;
    return true;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    vt<pair<int,int>> dirs = {{-1,0}, {0,-1}, {0,1}, {1,0}};
    while(t--) {
        int n,m;
        // vt<string> a(n);

        cin >> n >> m;
        int ans = n*m;
        vt<string> a(n);
        F0R(i, n) cin >> a[i];
        if(n==1&&m==1) {
            cout << 0 << endl;
            continue;
        }
        vt<vt<bool>> vis(n, vt<bool>(m));
        deque<pair<int,int>> dq;
        F0R(i, n) {
            if(a[i][0]=='L') {
                vis[i][0]=true;
                dq.push_back({i,0});
                ans--;
            } 
            if(a[i].back()=='R') {
                vis[i][m-1]=true;
                dq.push_back({i,m-1});
                ans--;
            }
        }
        F0R(i, m) {
            if(a[0][i]=='U') {
                vis[0][i]=true;
                dq.push_back({0,i});
                ans--;
            }
            if(a[n-1][i]=='D') {
                vis[n-1][i]=true;
                dq.push_back({n-1,i});
                ans--;
            }
        }
        // cout << ans << endl;
        while(dq.size()) {
            auto f = dq.front();
            // cout << f << endl;
            dq.pop_front();
            trav(xx, dirs) {
                auto nx = f.f+xx.f;
                auto ny = f.s+xx.s;
                if(nx<0||ny<0||nx>=n||ny>=m) continue;
                if(vis[nx][ny]) continue;
                if(a[nx][ny]=='U'&&vis[nx-1][ny]) {
                    vis[nx][ny]=true;
                    ans--;
                    dq.push_back({nx,ny});
                } else if(a[nx][ny]=='D'&&vis[nx+1][ny]) {
                    vis[nx][ny]=true;
                    ans--;
                    dq.push_back({nx,ny});
                } else if(a[nx][ny]=='L'&&vis[nx][ny-1]) {
                    vis[nx][ny]=true;
                    ans--;
                    dq.push_back({nx,ny});
                } else if(a[nx][ny]=='R'&&vis[nx][ny+1]) {
                    vis[nx][ny]=true;
                    ans--;
                    dq.push_back({nx,ny});
                } else if(a[nx][ny]=='?'&&surrounded(a,vis,nx,ny)) {
                    vis[nx][ny]=true;
                    ans--;
                    dq.push_back({nx,ny});
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}