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
    int n,q;
    cin >> n >> q;
    vt<vt<int>> minDisplac(n, vt<int>(n));
    vt<pair<int,int>> v(q);
    F0R(i, q) {
        string s;
        cin >> v[i].f >> s;
        v[i].f--;
        if(s=="+") v[i].s=1;
        else v[i].s=-1;
    }
    F0R(fir, n) {
        F0R(sec, n) {
            if(fir==sec) continue;
            int ans = 1;
            pair<int,int> curRange = {1,1}, curRange2 = {0,0};
            trav(x, v) {
                if(x.f==fir) {
                    if(x.s==1) {
                        curRange2.s++;
                        if(curRange2.s==curRange.f) {
                            curRange.f++;
                            curRange.s++;
                            ans++;
                        }
                    } else {
                        curRange2.f++;
                    }
                } else if(x.f==sec) {
                    if(x.s==1) {
                        curRange.s++;
                    } else {
                        curRange.f++;
                    }
                }
            }
            minDisplac[fir][sec]=ans;
        }
    }
    // cout << minDisplac << endl;
    vt<vt<int>> dp(1<<n, vt<int>(n, inf));
    vt<int> bruh(n);
    F0R(i, n) {
        int right = 0;
        trav(x, v) {
            if(x.f==i) {
                if(x.s==1) right++;
            }
        }
        bruh[i]=right;
        dp[1<<i][i]=1;
        // dp[1<<i][i]=right;
    }    
    FOR(i, 1, 1<<n) {
        if(__builtin_popcount(i)==1) continue;
        F0R(last, n) {
            if((i&(1<<last))==0) {
                continue;
            }
            F0R(secondLast, n) {
                if(last==secondLast) continue;
                if((i&(1<<secondLast))==0) continue;
                dp[i][last]=min(dp[i][last], dp[i^(1<<last)][secondLast]+minDisplac[secondLast][last]);
            }
        }
    }
    int ans = inf;
    F0R(i, n) ans=min(ans, dp[(1<<n)-1][i]+bruh[i]);
    cout << ans << endl;
    // cout << dp[(1<<n)-1] << endl;
    // cout << dp[6][1] << " " << dp[6][2] << endl;
    return 0;
}