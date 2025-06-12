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
        int n,m,d;
        cin >> n >> m >> d;
        vt<vt<int>> dp(n,vt<int>(m)), pref(n,vt<int>(m+1));
        vt<string> v(n);
        F0R(i, n) cin >> v[i];
        F0R(i, m) {
            if(v.back()[i]=='X') dp.back()[i]=1;
        }
        auto calcPref = [&dp,&pref, &m](int row)->void{
            F0R(i, m) {
                pref[row][i+1]=pref[row][i]+dp[row][i];
                pref[row][i+1]%=mod;
                pref[row][i+1]+=mod;
                pref[row][i+1]%=mod;
            }
        };  
        calcPref(n-1);
        F0R(i, m) {
            if(v.back()[i]!='X') continue;
            int end = i-1;
            int start = i-d;
            start=max(start, 0LL);
            dp[n-1][i]+=pref[n-1][end+1]-pref[n-1][start];
            start=i+1;
            end=i+d;
            end=min(end, m-1);
            dp[n-1][i]+=pref[n-1][end+1]-pref[n-1][start];
            dp[n-1][i]%=mod;
            dp[n-1][i]+=mod;
            dp[n-1][i]%=mod;
        }
        calcPref(n-1);
        int distBelow = d-1;
        R0F(row, n-1) {
            F0R(col, m) {
                if(v[row][col]!='X') continue;
                int start = col-distBelow, end = col+distBelow;
                start=max(start, 0LL);
                end=min(end, m-1);
                dp[row][col]+=pref[row+1][end+1]-pref[row+1][start];
                dp[row][col]%=mod;
                dp[row][col]+=mod;
                dp[row][col]%=mod;
            }
            calcPref(row);
            F0R(i, m) {
                if(v[row][i]!='X') continue;
                int end = i-1;
                int start = i-d;
                start=max(start, 0LL);
                dp[row][i]+=pref[row][end+1]-pref[row][start];
                start=i+1;
                end=i+d;
                end=min(end, m-1);
                dp[row][i]+=pref[row][end+1]-pref[row][start];
                dp[row][i]%=mod;
                dp[row][i]+=mod;
                dp[row][i]%=mod;
            }
            calcPref(row);
        }
        cout << pref[0].back() << endl;
        // cout << dp << endl;
    }
    return 0;
}