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
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    set<int> sq;
    for(int i = 1; i<= 1005; i++) sq.insert(i*i-1);
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> v(n,vt<int>(n, -1));
        pair<int,int> cur = {n/2,n/2};
        int nxt = 0;
        int prevdir = 0;
        vt<pair<int,int>> d = {{-1,0},{1,0},{0,-1},{0,1}};
        auto getDist = [&n](int x, int y)->int {
            // cout << "LINe 169 " << x << " " << y << " " << min(x, n-x)+min(y, n-y) << endl;
            return min(min(x, n-1-x),min(y, n-1-y));
        };
        auto getDist2 = [&n](int x, int y)->int {
            return abs(n/2-x)+abs(n/2-y);
        };
        while(true) {
            v[cur.f][cur.s]=nxt++;
            // F0R(i, n) {
            //     F0R(j, n) cout << v[i][j] << " ";
            //     cout << endl;
            // }
            // cout << endl;
            if(nxt==n*n) break;
            if(sq.count(nxt-1)) {
                cur.f+=d[prevdir].f;
                cur.s+=d[prevdir].s;
            } else {
                vt<array<int,3>> v2;
                F0R(i, 4) {
                    auto x = d[i];
                    if(cur.f+x.f<0 || cur.s+x.s<0 || cur.f+x.f>=n || cur.s+x.s>=n) continue;
                    if(v[cur.f+x.f][cur.s+x.s]!=-1) continue;
                    v2.add({cur.f+x.f, cur.s+x.s, i});
                }
                sort(begin(v2),end(v2),[&n,&getDist,&getDist2](array<int,3> &a, array<int,3> &b)->int {
                    if(getDist(a[0],a[1])==getDist(b[0],b[1])) return getDist2(a[0],a[1])<getDist2(b[0],b[1]);
                    return getDist(a[0],a[1])>getDist(b[0],b[1]);
                });
                prevdir = v2[0][2];
                cur.f+=d[prevdir].f;
                cur.s+=d[prevdir].s;
            }
        }
        F0R(i, n) {
            F0R(j, n) cout << v[i][j] << " ";
            cout << endl;
        }
        
    }
    return 0;
}