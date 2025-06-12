
#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
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
// #define double float
const ll mod = 998244353;
ll inf = 1e18;
double dp[4001][401][20];
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
double bexpo(double base, int exp) {
    if(exp<0) return 0;
    double ans = 1;
    while(exp) {
        if(exp&1) ans=ans*base;
        exp>>=1;
        base=base*base;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        double p;
        cin >> n >> m >> p;
        p/=100;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        sort(begin(a),end(a));
        int x = 0;
        F0R(i, n) x+=a[i]-a[0];
        int y = a[0];
        int Y = y;
        //dp[min health][rounds left][need type 2] = max probability
        // vt<vt<vt<double>>> dp(m+1, vt<vt<double>>(Y+1, vt<double>(n)));
        F0R(i, m+1) dp[i][1][0]=1;
        FOR(rleft, 1, m+1) {
            FOR(minhp, 1, Y+1) {
                //nt=0
                if(minhp!=1) {
                    dp[rleft][minhp][0]=p*dp[rleft-1][minhp-1][0]+(1-p)*max(dp[rleft-1][minhp-1][n-1], dp[rleft-1][minhp][0]);
                }
                FOR(nt, 1, n) {
                    if(minhp!=1) {
                        dp[rleft][minhp][nt]=p*dp[rleft-1][minhp-1][nt]+(1-p)*dp[rleft-1][minhp][nt-1];
                    } else {
                        dp[rleft][minhp][nt]=p*dp[rleft-1][minhp][nt]+(1-p)*dp[rleft-1][minhp][nt-1];
                    }
                }
            }
        }
        if(x==0) {
            cout << fixed << setprecision(15) << dp[m][y][0] << endl;
            continue;
        }
        // cout << "LINE 216: " << x << endl;
        // vt<vt<double>> chance2(m+1, vt<double>(m+1));//chance2[total rounds][]
        double ans = 0;
        // vt<vt<double>> dp2(x+1, vt<double>(m+1));
        vt<double> last(x+1);
        // dp2[x][m]=1;
        last[x]=1;
        ROF(i, 0, m) {
            vt<double> here(x+1);
            here[0]=last[1]*(1-p);
            here[x]=last[x]*p;
            // cout << "LINE 226: " << i << " " << here << endl;
            // dp2[0][i]=dp2[1][i+1]*(1-p);
            // dp2[x][i]=dp2[x][i+1]*p;
            // cout << "LINE 223: " << i << " " << dp2[0][i] << " " << dp2[x][i] << endl;
            FOR(j, 1, x) {
                here[j]=last[j+1]*(1-p)+last[j]*p;
                // dp2[j][i]=dp2[j+1][i+1]*(1-p)+dp2[j][i+1]*p;                
                // cout << j << " " << i << " " << dp2[j][i] << endl;
            }
            // cout << "LINE 229 " << dp2[0][i] << " " << dp2[1][i] << endl;
            int rounds = m-i;
            // cout << rounds << endl;
            int temp = rounds-x;
            int health = max(1LL, y-temp);
            if(temp>=0) {
                ans+=here[0]*dp[i][health][0];
                // cout << "LINE 232: " << dp2[0][i] << " " << dp[health][i][0] << endl;
                // cout << ans << endl;
            }
            // cout << here << last << endl;
            swap(last,here);
        }
        cout << fixed << setprecision(15) << ans << endl;
        // FOR(rleft, )
    }
    return 0;
}
/*
1
20 4000 50
400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400
*/