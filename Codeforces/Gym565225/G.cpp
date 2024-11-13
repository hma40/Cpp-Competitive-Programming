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
int solve(int x) {
    //dp[i][j][k]: i digits, j = 0 if less or 1 if equal or 2 if more, k = digit sum
    int sz = to_string(x).size();
    int dp[sz+1][3][10];
    F0R(i, sz+1) {
        F0R(j, 3) {
            F0R(k, 10) dp[i][j][k]=0;
        }
    }
    string s = to_string(x);
    dp[0][1][0]=1;
    F0R(i, sz) {
        F0R(digsum, 10) {
            //add a digit to something more
            F0R(dig, 10) {
                int nsum = (digsum+dig)%10;
                dp[i+1][2][nsum]+=dp[i][2][digsum];
            }
            //add a digit to something less
            F0R(dig, 10) {
                int nsum = (digsum+dig)%10;
                dp[i+1][0][nsum]+=dp[i][0][digsum];
            }
            //add 0...nextdigit-1 to become less
            F0R(dig, s[i]-'0') {
                int nsum = (digsum+dig)%10;
                dp[i+1][0][nsum]+=dp[i][1][digsum];
            }
            FOR(dig, s[i]-'0', s[i]-'0'+1) {
                int nsum = (digsum+dig)%10;
                dp[i+1][1][nsum]+=dp[i][1][digsum];
            }
            FOR(dig, s[i]-'0'+1, 10) {
                int nsum = (digsum+dig)%10;
                dp[i+1][2][nsum]+=dp[i][1][digsum];
            }
        }
    }
    // cout << x << endl;
    // F0R(i, s.size()+1) {
    //     F0R(j, 3) {
    //         F0R(k, 10) {
    //             if(dp[i][j][k]==0) continue;
    //             cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
    //         }
    //     }
    // }
    int ans = 0;
    // F0R(digits, s.size()) {
    //     ans+=dp[digits][0][3]+dp[digits][1][3]+dp[digits][2][3];
    // }
    ans+=dp[s.size()][0][3]+dp[s.size()][1][3];
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) {
        int l,r;
        cin >> l >> r;
        cout << solve(r)-solve(l-1) << endl;
    }
    return 0;
}