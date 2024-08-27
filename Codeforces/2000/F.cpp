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
int leastPoints[101][101][201];
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    // F0R(i, 101) {
    //     F0R(j, i) {
    //         leastPoints[1][i][j]=j;
    //         leastPoints[i][1][j]=j;
    //     }
    //     leastPoints[1][i][i]=leastPoints[1][i][i+1]=i;
    // }
    FOR(smaller, 1, 101) {
        leastPoints[smaller][smaller][0]=0;
        leastPoints[smaller][smaller][1]=smaller;
        leastPoints[smaller][smaller][2]=smaller+smaller-1;
        FOR(points, 3, smaller+smaller+1) {
            leastPoints[smaller][smaller][points]=leastPoints[smaller][smaller][2]+leastPoints[smaller-1][smaller-1][points-2];
        }
        FOR(larger, smaller+1, 101) {
            leastPoints[smaller][larger][0]=0;
            leastPoints[larger][smaller][0]=0;
            F0R(points, larger-smaller) {
                leastPoints[smaller][larger][points+1]=leastPoints[smaller][larger][points]+smaller;
                leastPoints[larger][smaller][points+1]=leastPoints[smaller][larger][points]+smaller;
            }
            FOR(points, larger-smaller+1, larger+smaller+1) {
                leastPoints[smaller][larger][points]=leastPoints[smaller][larger][larger-smaller]+leastPoints[smaller][smaller][points-larger+smaller];
                leastPoints[larger][smaller][points]=leastPoints[smaller][larger][larger-smaller]+leastPoints[smaller][smaller][points-larger+smaller];
            }
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        //dp[i][j]=first x rectangles, y points, min operations
        int n,k;
        cin >> n >> k;
        // priority_queue<array<int,4>>
        vt<pair<int,int>> rect(n);
        F0R(i, n) cin >> rect[i].f >> rect[i].s;
        vt<vt<int>> dp(n+1, vt<int>(k+1, inf));
        dp[0][0]=0;
        F0R(i, n) {
            F0R(j, k+1) {
                int maxGained = k-j;
                maxGained=min(maxGained, rect[i].f+rect[i].s);
                F0R(gain, maxGained+1) {
                    dp[i+1][j+gain]=min(dp[i+1][j+gain], dp[i][j]+leastPoints[rect[i].f][rect[i].s][gain]);
                }
            }
        }
        if(dp[n][k]>=inf) {
            cout << -1 << endl;
        } else {
            cout << dp[n][k] << endl;
        }
    }
    return 0;
}
/*
1 15
vs
2 7
15 for 16
vs
14 for 9
*/