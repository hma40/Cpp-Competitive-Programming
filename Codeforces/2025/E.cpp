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
    ll bexpo(ll b, ll e) {
        ll a = 1;
        while(e) {
            if(e%2) {
                a*=b;
                a%=mod;
            }
            e/=2;
            b*=b;
            b%=mod;
        }
        return a;
    }
    vt<int> fact(10000), invfact(10000);
    int nck(int n, int k) {
        if(n<k) return 0;
        return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
    }
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // vt<int> fact(10000);
    fact[0]=1;
    FOR(i, 1, 10000) fact[i]=fact[i-1]*i%mod;
    // vt<int> invfact(10000);
    F0R(i, 10000) invfact[i]=bexpo(fact[i], mod-2);
    vt<int> cata(501);
    F0R(i, 501) {
        cata[i]=nck(2*i,i)-nck(2*i, i+1);
        cata[i]%=mod;
        cata[i]+=mod;
        cata[i]%=mod;
    }
    int n,m;
    cin >> n >> m;
    vt<int> ways(m+1);//ways[i] = ways for Alice to take i, Bob to take n-i, and for 1 to cover for n-2i
    /*
    how to calculate ways? ways[i]=
    */
    vt<vt<int>> dp(m+1, vt<int>(m+1));//dp[i][j] = 1-i, alice takes j already
    dp[1][1]=0;
    dp[1][0]=1;
    FOR(tot, 2, m+1) {
        F0R(taken, tot+1) {
            int bobtaken = tot-taken;
            if(taken>bobtaken) continue;
            dp[tot][taken]+=dp[tot-1][taken];
            if(taken>0) dp[tot][taken]+=dp[tot-1][taken-1];
            dp[tot][taken]%=mod;
        }
    }
    // cout << dp << endl;
    vt<vt<int>> dp2(n+1, vt<int>(m+1));
    FOR(alice, m/2, m+1) {
        int bob = m-alice;
        dp2[1][alice-bob]=dp[m][bob];
    }
    FOR(i, 1, n) {
        F0R(prev, m+1 ){
            FOR(alice, 0, m/2+1) {
                int bob = m-alice;
                int ndelta = prev-(bob-alice);
                if(ndelta<0) continue;
                // cout << i << " " << prev << " " << alice << " " << ndelta << endl;
                dp2[i+1][ndelta]+=dp2[i][prev]*dp[m][alice];
                dp2[i+1][ndelta]%=mod;
            }
        }
    }
    // cout << dp2 << endl;
    cout << dp2[n][0] << endl;
    return 0;

}
/*
1 2 3 4
A can take 
- 4 3
- 4 2
- 4 3 2
- 4 3 1
- 4 2 1
- 4 3 2 1 

1 2 3 4 5 6
- 6 5 4
- 6 5 3
- 6 5 2
- 6 4 3
- 6 4 2
- 6 5 4 3
- 6 5 4 2
- 6 5 4 1
- 6 5 3 2
- 6 5 3 1
- 6 5 2 1
- 6 4 3 2
- 6 4 3 1
- 6 4 2 1

*/