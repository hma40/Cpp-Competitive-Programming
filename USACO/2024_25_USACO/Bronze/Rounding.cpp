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
const ll mod = 1000000007;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        //dp[length][alreadyRounding?][less/equal/greater] = amount
        vt<vt<vt<int>>> dp(s.size()+1, vt<vt<int>>(2, vt<int>(3, 0)));
        // dp[0][0][1]=1;
        if(s[0]>'4') {
            dp[1][0][0]=1;
        } else if(s[0]=='4') {
            dp[1][0][1]=1;
        } else {
            dp[1][0][2]=1;
        }
        FOR(len, 1, s.size()) {
            // cout << dp[1] << endl;
            FOR(nextDigit, 0, 4) {
                //can only append to something thats already rounding
                dp[len+1][1][0]+=dp[len][1][0];
                if(s[len]>'0'+nextDigit) {
                    // cout << "LINE 156 " << nextDigit << endl;
                    dp[len+1][1][0]+=dp[len][1][1];
                } else if(s[len]=='0'+nextDigit) {
                                        // cout << "LINE 159 " << nextDigit << endl;
                    dp[len+1][1][1]+=dp[len][1][1];
                } else {
                                        // cout << "LINE 162 " << nextDigit << endl;
                    dp[len+1][1][2]+=dp[len][1][1];
                }
                dp[len+1][1][2]+=dp[len][1][2];
            }
            // cout << dp[1] << endl;
            //can append 4 to not rounding OR rounding
            dp[len+1][1][0]+=dp[len][1][0];
            dp[len+1][1][2]+=dp[len][1][2];
            dp[len+1][0][0]+=dp[len][0][0];
            dp[len+1][0][2]+=dp[len][0][2];
            if(s[len]>'4') {
                dp[len+1][1][0]+=dp[len][1][1];
                dp[len+1][0][0]+=dp[len][0][1];
            } else if(s[len]=='4') {
                dp[len+1][1][1]+=dp[len][1][1];
                dp[len+1][0][1]+=dp[len][0][1];
            } else {
                dp[len+1][1][2]+=dp[len][1][1];
                dp[len+1][0][2]+=dp[len][0][1];
            }
            // cout << dp[1] << endl;
            FOR(nextDigit, 5, 10) {
                dp[len+1][1][0]+=dp[len][0][0];
                dp[len+1][1][2]+=dp[len][0][2];
                dp[len+1][1][0]+=dp[len][1][0];
                dp[len+1][1][2]+=dp[len][1][2];
                if(s[len]>'0'+nextDigit) {
                    dp[len+1][1][0]+=dp[len][1][1];
                    dp[len+1][1][0]+=dp[len][0][1];
                } else if(s[len]=='0'+nextDigit) {
                    dp[len+1][1][1]+=dp[len][1][1];
                    dp[len+1][1][1]+=dp[len][0][1];
                } else {
                    dp[len+1][1][2]+=dp[len][1][1];
                    dp[len+1][1][2]+=dp[len][0][1];
                }
            }
            // cout << dp[1] << endl;
        }
        int ans = 0;
        FOR(len, 1, s.size()) {
            ans+=dp[len][1][0]+dp[len][1][1]+dp[len][1][2];
        }
        // cout << "LINE 200 " << ans << endl;
        // cout << dp[1][1][0] << " " << dp[1][1][1] << endl;
        ans+=dp[s.size()][1][0]+dp[s.size()][1][1];
        cout << ans << endl;
    }
    return 0;
}