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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int n;
    cin >> n;
    vt<string> board(n);
    F0R(i, n) cin >> board[i];
    vt<vt<vt<bool>>> vis(n, vt<vt<bool>>(n, vt<bool>(4)));
    queue<array<int,3>> q;
    F0R(i, n) {
        F0R(j, n) {
            if(board[i][j]=='?') {
                q.push({i,j,0});
                q.push({i,j,1});
                q.push({i,j,2});
                q.push({i,j,3});
                vis[i][j][0]=vis[i][j][1]=vis[i][j][2]=vis[i][j][3]=true;
            }
        }
    }
    bool good = true;
    vt<int> dx = {-1,1,0,0}, dy = {0,0,1,-1};
    while(q.size()) {
        auto f = q.front();
        q.pop();
        int nx = f[0]+dx[f[2]], ny = f[1]+dy[f[2]];
        if(nx<0||ny<0||nx>=n||ny>=n) continue;
        if(board[nx][ny]=='X'||(board[nx][ny]>='0'&&board[nx][ny]<='4')) continue;
        if(board[nx][ny]=='?') good=false;
        if(vis[nx][ny][f[2]]) continue;
        vis[nx][ny][f[2]]=true;
        q.push({nx,ny,f[2]});
    }

    F0R(i, n) {
        F0R(j, n) {
            if(board[i][j]=='.') {
                if(!vis[i][j][0]&&!vis[i][j][1]&&!vis[i][j][2]&&!vis[i][j][3]) good=false;
            }
            if(board[i][j]=='?') {
                F0R(k, 4) {
                    int nx = i+dx[k], ny = j+dy[k];
                    if(nx<0||ny<0||nx>=n||ny>=n) continue;  
                    if(board[nx][ny]=='?') good=false;
                }
            }
            if(board[i][j]>='0'&&board[i][j]<='4') {
                int cnt = 0;
                F0R(k, 4) {
                    int nx = i+dx[k], ny = j+dy[k];
                    if(nx<0||ny<0||nx>=n||ny>=n) continue;  
                    if(board[nx][ny]=='?') cnt++;
                }
                if(cnt!=board[i][j]-'0') good=false;
            }
        }
    }
    if(!good) cout << 0 << endl;
    else cout << 1 << endl;
    return 0;
}