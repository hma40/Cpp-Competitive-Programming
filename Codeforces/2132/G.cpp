#pragma GCC optimize("O3,unroll-loops")

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
#define endl "\n"
#define enld "\n"
#define double long double
// const ll mod = 998244353;
#define __int128_t long long
ll inf = 1e18;
vector<__int128_t> PWX(1e6+5), PWY(1e6+5);
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
__int128_t PX,PY;
__int128_t mod = 998244353;
struct Hashing {
  vector<vector<__int128_t>> hs;
  int n, m;

//   static const int PX = 3731,  PY = 2999, mod = 998244353;
  Hashing() {}
  Hashing(vector<string>& s) {

    n = (int)s.size(), m = (int)s[0].size();
    hs.assign(n + 1, vector<__int128_t>(m + 1, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        hs[i + 1][j + 1] = s[i][j] - 'a' + 1;
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m; j++) {
        hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
      }
    }
  }
  int get_hash(int x1, int y1, int x2, int y2) {
    x2++;
    y2++;
    int dx = x2 - x1, dy = y2 - y1;
    return (int)((1LL * (hs[x2][y2] - 1LL * hs[x2][y1] * PWY[dy] % mod + mod) % mod -
        1LL * (hs[x1][y2] - 1LL * hs[x1][y1] * PWY[dy] % mod + mod) % mod * PWX[dx] % mod + mod) % mod);
  }
  int get_hash() {
    return get_hash(1, 1, n, m);
  }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    PX = rnd()%mod;
    PY = rnd()%mod;
    PWX[0]=PWY[0]=1;
    FOR(i, 1, 1e6+5) {
        PWX[i]=PWX[i-1]*PX%mod;
        PWY[i]=PWY[i-1]*PY%mod;
    }
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<string> v1(n),v2,v3,v4;
        F0R(i, n) cin >> v1[i];
        // auto w = v;
        v2=v1;
        reverse(begin(v2),end(v2));
        v3=v2;
        F0R(i, n) reverse(begin(v3[i]),end(v3[i]));
        v4=v1;
        F0R(i, n) reverse(begin(v4[i]),end(v4[i]));
        array<Hashing,4> a = {Hashing(v1),Hashing(v2),Hashing(v3),Hashing(v4)};
        int here = inf;
        FOR(r, n, 2*n) {
            FOR(c, m, 2*m) {
                if((a[0].get_hash(r-n,c-m,n-1,m-1) == a[2].get_hash(0,0,2*n-1-r,2*m-1-c))) {
                    here=min(here, r*c);
                    break;
                }
                if((a[2].get_hash(r-n,c-m,n-1,m-1) == a[0].get_hash(0,0,2*n-1-r,2*m-1-c))) {
                    here=min(here, r*c);
                    break;
                }
                if((a[1].get_hash(r-n,c-m,n-1,m-1) == a[3].get_hash(0,0,2*n-1-r,2*m-1-c))) {
                    here=min(here, r*c);
                    break;
                }
                if((a[3].get_hash(r-n,c-m,n-1,m-1) == a[1].get_hash(0,0,2*n-1-r,2*m-1-c))) {
                    here=min(here, r*c);
                    break;
                }
            }
        }
        cout << here-n*m << endl;
    }
    return 0;
}
/*

af
fa
te

lets say we fix dimensions (4 rows x 3 cols)

???
af?
fa?
te?

what do we need to be correct?

r1=rev(r3)
r2=rev(r2)
c1=rev(c4)
c2=rev(c3)

??????
abcd??
efgh??
ijkl??

abcd??
efgh??
ijkl??
??????

rows we care about: 2,3 (need to match with 3,2)
cols we care about: 3,4 (need to match with 4,3)

hey?
hey?
*/