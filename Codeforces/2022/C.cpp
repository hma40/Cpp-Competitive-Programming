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
        vt<string> v(2);
        cin >> n >> v[0] >> v[1];
        /*
        dp[i][0] = best score if i on row 0 done and i on row 1 done
        dp[i][1] = best score if i on row 0 done and i-1 on row 1 done
        dp[i][2] = best score if i on row 0 done and i-2 on row 1 done
        dp[i][3]: i-1 on 0, i on 1
        dp[i][4]: i-2 on 0, i on 1
        */
        vt<vt<int>> dp(n+1, vt<int>(5, -1));
        dp[0][0]=0;
        FOR(i, 2, n+1) {
            if(i>=3&&i%3==0) {
                dp[i][0]=dp[i-3][0];
                int count = 0;
                if(v[0][i-1]=='A') count++;
                if(v[0][i-2]=='A') count++;
                if(v[0][i-3]=='A') count++;
                if(count>1) dp[i][0]++;
                count=0;
                if(v[1][i-1]=='A') count++;
                if(v[1][i-2]=='A') count++;
                if(v[1][i-3]=='A') count++;
                if(count>1) dp[i][0]++;
            }
            // if(i==9) cout << dp[i] << endl;
            if(i>=3&&i%3==0) {
                int here = dp[i-1][1];
                int count = 0;
                if(v[0][i-1]=='A') count++;
                if(v[1][i-1]=='A') count++;
                if(v[1][i-2]=='A') count++;
                if(count>1) here++;
                dp[i][0]=max(dp[i][0], here);
                here = dp[i-1][3];
                count = 0;
                if(v[0][i-1]=='A') count++;
                if(v[1][i-1]=='A') count++;
                if(v[0][i-2]=='A') count++;
                if(count>1) here++;
                dp[i][0]=max(dp[i][0], here);                
            }
            if(i%3==1) {
                dp[i][2]=dp[i-2][3];
                int count = 0;
                if(v[0][i-1]=='A') count++;
                if(v[0][i-3]=='A') count++;
                if(v[0][i-2]=='A') count++;
                if(count>1) dp[i][2]++;
                dp[i][4]=dp[i-2][1];
                count = 0;
                if(v[1][i-1]=='A') count++;
                if(v[1][i-3]=='A') count++;
                if(v[1][i-2]=='A') count++;
                if(count>1) dp[i][4]++;
            }
            if(i%3==2) {
                dp[i][1]=dp[i-2][0];
                int count = 0;
                if(v[0][i-1]=='A') count++;
                if(v[1][i-2]=='A') count++;
                if(v[0][i-2]=='A') count++;
                if(count>1) dp[i][1]++;
                dp[i][3]=dp[i-2][0];
                count = 0;
                if(v[0][i-2]=='A') count++;
                if(v[1][i-1]=='A') count++;
                if(v[1][i-2]=='A') count++;
                if(count>1) dp[i][3]++;
                if(i>3) {
                    int here = dp[i-1][2];
                    count = 0;
                    if(v[1][i-1]=='A') count++;
                    if(v[1][i-3]=='A') count++;
                    if(v[1][i-2]=='A') count++;
                    if(count>1) here++;
                    dp[i][3]=max(dp[i][3], here);
                    here = dp[i-1][4];
                    count = 0;
                    if(v[0][i-1]=='A') count++;
                    if(v[0][i-3]=='A') count++;
                    if(v[0][i-2]=='A') count++;
                    if(count>1) here++;
                    dp[i][1]=max(dp[i][1], here);
                }
                // cout << i << " " << dp[i] << endl;
            }
        }
        cout << dp[n][0] << endl;
    }
    return 0;
}