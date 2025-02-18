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
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int a, int b) {
    int ans = 1;
    while(b) {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
vt<int> fact, invfact;
int nck(int n, int k) {
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}
int npk(int n, int k) {
    return fact[n]*invfact[n-k]%mod;

}
int chance(int n, int m, int x1, int y1, int x2, int y2) {
    // cout << n << " " << m << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    int ans = 1;
    n-=x1;
    m-=y1;
    y2-=y1;
    x2-=x1;
    ans*=nck(x2+y2,x2);
    ans*=npk(n, x2);
    ans%=mod;
    ans*=npk(m, y2);
    ans%=mod;
    ans*=bexpo(npk(n+m,x2+y2), mod-2);
    ans%=mod;
    // cout << "RETURNING " << ans << endl;
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fact.resize(400006);
    invfact.resize(400006);
    fact[0]=1;
    FOR(i, 1, 400006) fact[i]=fact[i-1]*i%mod;
    F0R(i, 400006) invfact[i]=bexpo(fact[i], mod-2);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m,k;
        cin >> n >> m >> k;
        vt<pair<int,int>> a(k);
        F0R(i, k) cin >> a[i].f >> a[i].s;
        F0R(i,k) {
            a[i].f=n-a[i].f;
            a[i].s=m-a[i].s;
        }
        a.add({0,0});
        a.add({n,m});
        sort(begin(a),end(a));
        k+=2;
        vt<vt<int>> dp(k, vt<int>(k));//dp[i][j] = probability that we get from i to j without crossing anything in between
        /*
        to calculate dp: we can uhh complementary count thing?
        casework on last one that is crossed
        dp[i][j]=1 initially
        for each k: dp[i][j]-=P(i,k) * dp[k][j]
        */
        // cout << a << endl;
        vt<vt<int>> chan(k, vt<int>(k));
        F0R(i, k) {
            FOR(j, i, k) {
                if(a[i].f>a[j].f||a[i].s>a[j].s) continue;
                chan[i][j]=chance(n,m,a[i].f,a[i].s,a[j].f,a[j].s);
            }
        }
        FOR(diff, 1, k) {
            FOR(j, diff, k) {
                int i = j-diff;
                if(a[i].f>a[j].f||a[i].s>a[j].s) {
                    continue;
                }
                dp[i][j]=chan[i][j];//(n,m,a[i].f,a[i].s,a[j].f,a[j].s);
                FOR(kk, i+1, j) {
                    if(a[i].f>a[kk].f||a[i].s>a[kk].s) continue;
                    dp[i][j]-=chan[i][kk]*dp[kk][j];
                    dp[i][j]%=mod;
                    dp[i][j]+=mod;
                    dp[i][j]%=mod;
                }
            }
        }
        // assert(false);
        // cout << dp << endl << a << endl;
        vt<int> dp2(k);//dp2[i] = expected value for i
        F0R(i, k) {
            F0R(prev, i) {
                //add contribution when that last one is prev
                int here = dp2[prev];
                here+=chan[0][prev]*(2*(a[i].f-a[prev].f)+(a[i].s-a[prev].s));
                here%=mod;
                // cout << "LINE 227 " << prev << " " << i << " " << here << endl;
                here*=dp[prev][i];
                here%=mod;
                // cout << prev << " " << i << " " << here << endl;
                dp2[i]+=here;
                dp2[i]%=mod;
            }
            dp2[i]*=2;
            dp2[i]%=mod;
        }
        // cout << dp2 << endl;
        cout << dp2.back()*bexpo(2, mod-2)%mod << endl;
    }
    return 0;
}
/*
sort the scrolls by R then B
We can assume theres a scroll at (0,0) and a scroll at (n,m), just divide by 2 at the end
for each scroll dp = expected earnings for scrolls 1...i, casework on what could be last scroll obtained
after determining what the last scroll is we need to avoid everything in between (how?)
*/
/*
1
2 1 2
1 1
0 1
*/