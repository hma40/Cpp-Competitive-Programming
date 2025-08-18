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
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n-1);
        F0R(i, n-1) cin >> a[i];
        vt<int> c(n);
        c[0]=a[0];
        c.back()=a.back();
        FOR(i, 1, n-1) c[i]=a[i-1]|a[i];
        auto d = c;
        // cout << c << endl;
        bool ok = true;
        F0R(i, n-1) if((c[i]&c[i+1])!=a[i]) {
            ok=false;
        } 

        int ans = 0;
        vt<int> b(n);
        F0R(i, n) cin >> b[i];
                if(!ok) {
            cout << -1 << endl;
            continue;
        }
        F0R(i, n) {
            bool done = false;
            R0F(j, 31) {
                if(c[i]&(1LL<<j)) {
                    if(b[i]&(1LL<<j)) {
                        continue;
                    } else {
                        done=true;
                    }
                } else {
                    if(b[i]&(1LL<<j)) {
                        if(!done) {
                            c[i]+=1LL<<j;
                        }
                    }
                }
            }
        }
        F0R(i, n) ans+=c[i]-b[i];
        vt<vt<int>> choices(n, vt<int>(33));
        // assert(false);
        // cout << d << endl;
        // assert(false);
        // return 0;
        F0R(i,n) {
            // cout << i << endl;
            choices[i][32]=c[i];
            F0R(j, 32) {
                // cout << i << " " << j << endl;
                if(c[i]&(1LL<<j)) {
                    choices[i][j]=c[i];
                    continue;
                }
                // cout << "LINE 212 " << i << " " << j << endl;
                choices[i][j]=c[i]+(1LL<<j);
                R0F(k, j) {
                    if(d[i]&(1LL<<k)) continue;
                    else if(choices[i][j]&(1LL<<k)) choices[i][j]-=1LL<<k;
                }
            }
        }
        // cout << choices[0] << endl;
        // cout << choices[1] << c <<endl;
        // assert(false);
        vt<vt<int>> dp(n,vt<int>(33,inf));
        F0R(i, 33) dp[0][i]=choices[0][i]-c[0];
        // assert(false);
        FOR(i, 1, n) {
            F0R(j, 33) {
                F0R(k, 33) {
                    if((choices[i-1][j]&choices[i][k])!=a[i-1]) {

                    } else {
                        dp[i][k]=min(dp[i][k], dp[i-1][j]+choices[i][k]-c[i]);
                    }
                }
            }
        }
        // cout << dp << endl;
        int mn = inf;
        F0R(i, 33) mn=min(mn, dp.back()[i]);
        // cout << c << endl;
        cout << ans+mn << endl;
    }
    return 0;
}