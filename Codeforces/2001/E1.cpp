/*
dp[i][j] = ways such that the correct path goes through specific node of layer i and a_v=j
how to calculate? Loop through score of parent. 
- if other child has score 0: 1 way ig
- if other child has score 1: there are (subsize(x)) ways to put that score
- if other child has score 2: there are (subsize(x)^2) ways to put that score

example: 3,2,988244353
dp[0][2] = 1
dp[1][0] = 0
dp[1][1]
- other=0, parent=2: dp[0][2] * 2^0 * 2 = 2
dp[1][2]
- other=0, parent=2: dp[0][2] * 2^0 * 2 = 2
dp[2][0] = 0
dp[2][1]:
- other=0, parent=1: dp[1][1] * 2^0 * 2 = 4
- other=0, parent=2: dp[1][2] * 2^0 * 2 = 4
dp[2][2]: 
- other=0, parent=2: dp[1][2] * 2^0 * 2 = 4
*/
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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k >> mod;
        vt<int> pow2(501);
        pow2[0]=1;
        FOR(i, 1, 501) {
            pow2[i]=pow2[i-1]*2%mod;
        }   
        vt<vt<int>> pref(501, vt<int>(501));//pref[i][j] = number of ways to put i score or less in 2^j-1 nodes
        vt<vt<int>> ppref(501, vt<int>(501));

        F0R(i, 501) pref[i][1]=i+1;
        F0R(i, 501) pref[0][i]=1;
        FOR(i, 1, 501) {
            FOR(j, 2, 501) {
                pref[i][j]=pref[i-1][j]*(pow2[j]-1)%mod;
            }
        }
        F0R(i, 501) ppref[i][1]=i+1;
        F0R(i, 501) ppref[0][i]=1;
        FOR(i, 1, 501) {
            FOR(j, 2, 501) {
                ppref[i][j]=ppref[i-1][j]+pref[i][j];
            }
        }
        cout << ppref[2][2] << " " << ppref[1][2] << " " << ppref[0][2] << endl;
        // cout << pref[1][1] << endl;
        cout << pref[2][2] << " " << pref[1][2] << " " << pref[0][2] << endl;
        vt<vt<int>> dp(n, vt<int>(k+1));
        dp[0][k]=1;
        FOR(layer, 1, n) {
            FOR(score, 1, k+1) {
                FOR(parscore, score, k+1) {
                    int maxother = min(parscore-score, score-1);
                    int layersLeft = n-layer;
                    dp[layer][score]+=dp[layer-1][parscore]*2*ppref[maxother][layersLeft];
                    dp[layer][score]%=mod;
                }
            }
        }
        int ans = 0;
        cout << dp << endl;
        F0R(score, k+1) ans = (ans+dp[n-1][score])%mod;
        cout << ans << endl;
    }

    return 0;
}
/*
3 5 998244353

dp[1][1]: 2
dp[1][2]: 2+6=8
dp[1][3]:
- 2(1+3+9)=
*/