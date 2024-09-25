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
// #define int long long
#define vt vector
// #define endl "\n"
#define double long double
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int MAX_VAL = 55001;
    vector<int> fib = {1,1};
    while(fib.back()<MAX_VAL) {
        fib.add(fib[fib.size()-1]+fib[fib.size()-2]);
    }
    vector<int> min_sum_fib(MAX_VAL, 1e9);
    min_sum_fib[0]=0;
    FOR(i, 1, MAX_VAL) {
        trav(x, fib) {
            if(x>i) continue;
            min_sum_fib[i]=min(min_sum_fib[i], min_sum_fib[i-x]+1);
        }
    }
    // cerr << "DONE" << std::endl;
    int n,x,m;
    cin >> n >> x >> m;
    vt<vt<int>> ways(MAX_VAL, vt<int>(n+1));
    // vt<vt<vt<int>>> ways(MAX_VAL, vt<vt<int>>(n+1, vt<int>(x)));//ways to make i using j fibonacci numbers from 1 to k
    // F0R(i, x) ways[fib[i]][1][i]=1;
    // ways[0][0][0]=1;
    ways[0][0]=1;
    F0R(k, x) {
        // cout << k << endl;
        FOR(i, 0, MAX_VAL) {
            F0R(j, n) {
                if(i+fib[k]>=MAX_VAL) break;
                ways[i+fib[k]][j+1]+=ways[i][j];
                if(ways[i+fib[k]][j+1]>mod) ways[i+fib[k]][j+1]-=mod;
                // ways[i+fib[k]][j+1]%=mod;
            }
        }
    }
    // cout << ways[0][1][0] << endl;
    // cout << ways[1][1][0] << endl;
    // cout << ways[1][1][1] << endl;
    int ans = 0;
    FOR(i, 1, MAX_VAL) {
        // cout << i << " " << min_sum_fib[i] << endl;
        if(min_sum_fib[i]==m) {
            // cout << i << endl;
            // F0R(j, x) {
                // if(ways[i][n][j]!=0) cout << i << " " << n << " " << j << " " << ways[i][n][j] << endl;
            ans+=ways[i][n];
            ans%=mod;
            // }
        }
    }
    cout << ans << endl;
    return 0;
}
/*
1 1 0
2 2 1
*/