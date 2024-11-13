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

    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n), b(n), c(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) {
            cin >> b[i];
        }
        F0R(i, n) cin >> c[i];
        int leasta = a[n-1], leastb = b[n-1], leastc = c[n-1];
        vt<bool> win(n);
        win[n-1]=true;
        R0F(i, n-1) {
            if(a[i]>leasta||b[i]>leastb||c[i]>leastc) {
                win[i]=true;
                leasta=min(leasta, a[i]);
                leastb=min(leastb, b[i]);
                leastc=min(leastc, c[i]);
            }
        }
        vt<pair<int,int>> next(n);
        leasta=n-1;
        leastb=n-1;
        leastc=n-1;
        if(win[0]) {
            cout << "YES" << endl;
            R0F(i, n-1) {
                if(a[i]>a[leasta]&&win[leasta]) {
                    next[i]={leasta,0};
                    if(b[i]<b[leastb]) leastb=i;
                    if(c[i]<c[leastc]) leastc=i;
                } else if(b[i]>b[leastb]&&win[leastb]) {
                    next[i]={leastb,1};
                    if(a[i]<a[leasta]) leasta=i;
                    if(c[i]<c[leastc]) leastc=i;
                } else if(c[i]>c[leastc]&&win[leastc]) {
                    next[i]={leastc,2};
                    if(a[i]<a[leasta]) leasta=i;
                    if(b[i]<b[leastb]) leastb=i;
                }
            }
            vt<pair<int,int>> moves;
            int cur = 0;
            while(cur!=n-1) {
                moves.add(next[cur]);
                cur=next[cur].f;
            }
            cout << moves.size() << endl;
            trav(x, moves)  {
                if(x.s==0) {
                    cout << "q " << x.f+1 << endl;
                } else if(x.s==1) {
                    cout << "k " << x.f+1 << endl;
                } else {
                    cout << "j " << x.f+1 << endl;
                }
            }
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}