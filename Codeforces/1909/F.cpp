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
int npk(int n, int k) {
    int ans = 1;
    F0R(i, k) {
        ans=ans*(n-k)%mod;
    }
    return ans;
}
int bexpo(int b, int e) {
    int a = 1;
    while(e) {
        if(e&1) a=a*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return a;
}
int fact[400005], invfact[400005];
int nck(int n, int k) {
    if(n<k) return 0;
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fact[0]=invfact[0]=1;
    FOR(i, 1, 400005) {
        fact[i]=fact[i-1]*i%mod;
        invfact[i]=bexpo(fact[i], mod-2);
    }
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> reqs;
        reqs.add({0,0});
        F0R(i, n) {
            int x;
            cin >> x;
            if(x!=-1) reqs.add({i+1,x});
        }
        if(reqs.back().f==n&&reqs.back().s!=n) {
            cout << -1 << endl;
            continue;
        }
        if(reqs.back().f!=n) reqs.add({n,n});
        int ans = 1;
        cout << reqs << endl;
        FOR(i, 1, reqs.size()) {
            if(reqs[i].s<reqs[i-1].s) {
                ans=0;
                break;
            }
            /*
            say we have requirements 
            (3,1)
            (11,8)
            - take 0 from 4-11 for the empty hole: (2 choose 0)(8 choose 0)(0!)(8 choose 7)(9)(8)...(3)
            - take 1 from 4-11 for the empty holes: (2 choose 1)(8 choose 1)(1!)(8 choose 6)(8)...(3)
            - take 2 from 4-11 for the empty holes: (2 choose 2)(8 choose 2)(2!)(8 choose 5)(7)(...)(3)
            */
            int here = 0;
            int factBef = npk(reqs[i].f-reqs[i-1].s, reqs[i].s-reqs[i-1].s);
            F0R(holesfilled, reqs[i-1].f) {
                
            }
        }
    }
    return 0;
}
/*
1
4
1 1 2 4 

1 4 3 2
1 4 2 3
*/