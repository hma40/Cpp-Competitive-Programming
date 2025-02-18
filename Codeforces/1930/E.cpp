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
int bexpo(int b, int e=mod-2) {
    int a = 1;
    while(e) {
        if(e&1) a=a*b%mod;
        b=b*b%mod;
        e>>=1;
    }
    return a;
}
vector<int> fact, invfact;
int nck(int n, int k) {
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    fact.resize(2000001);
    invfact.resize(2000001);
    fact[0]=invfact[0]=1;
    FOR(i, 1, 2000001) {
        fact[i]=fact[i-1]*i%mod;
        invfact[i]=bexpo(fact[i]);
    }
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        for(int k = 1; k*2+1<=n; k++) {
            int ans = 0;
            for(int dellen = 0; dellen < n; dellen+=2*k) {
                ans+=nck(n, dellen);
                ans%=mod;
            }

            // cout << ans << endl;
            int empty = 2*k;
            for(int dellen = 2*k; dellen < n; dellen+=2*k) {
                int left = n-dellen;
                // cout << left << " " << empty << endl;
                ans-=nck(left+empty-1, empty-1);
                ans%=mod;
                if(ans<0) ans+=mod;
            }
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
n=8, k=1
?
1 2 3 4 5 6 7 8
1 5
2 5
3 5
4 5
4 6
4 7
4 8

1 2 3 4 5 6 7 8 9 10
k=1:
- length=2: (?YY?) -> 2 empty spaces
- length=4: (?YYYY?) -> 2 empty spaces
- length=6: 5
- length=8: 3

k=2:
- length=4: (+?Y?YY?Y?)
- length=8: (+?Y?YYYYYY?Y?)

k=4:
- length=8: (+?Y?Y?Y?YY?Y?Y?Y?)
*/