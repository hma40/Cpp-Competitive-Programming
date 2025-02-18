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
// const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(vt<int> s) {
        // cout << "LINE 144 " << s << endl;
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
void initialize() {
    sd = rnd()%mod;
    pw.add(1);
    F0R(i, 600050) {
        pw.add(pw.back()*sd%mod);
    }
}
array<int,2> solve(int m, vt<int>& a, vt<int>& b, Hash& aHash, int startInd, bool can) {
    // cout << b << " " << can << " " << startInd << endl;
    if(!can) {
        int lo = 0;
        Hash bHash(b);
        FOR(i, 1, m+1) {
            if(aHash.getHash(startInd,startInd+i-1) == bHash.getHash(m-i,m-1)) {
                lo=i;
            }
        }
        // cout << "RETURNING " << startInd+lo << " " << m-lo << endl;
        return {startInd+lo, m-lo};
    }
    int ans = 0;
    F0R(i, m) {
        if(a[startInd]==b[i]) {
            startInd++;
        } else {
            ans++;
        }
    }
    return {startInd, ans};
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    initialize();
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<int> a;
        vt<vt<int>> b(n,vt<int>(m));
        int ans = 0;
        F0R(i, n) F0R(j, m) {
            int x;
            cin >> x;
            a.add(x);
        }
        F0R(i, n) F0R(j, m) cin >> b[i][j];
        Hash h(a);
        int start = 0;
        F0R(i, n) {
            array<int,2> x;
            if(ans==0) 
            x = solve(m,a,b[i],h , start, false);
            else
            x = solve(m,a,b[i],h, start,true);
            start=x[0];
            ans+=x[1];
        }
        cout << ans << endl;
    }
    return 0;
}
/*

17 1 2 3
4 18 5 6
7 19 8 20
9 21 22 10

1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

17 1 2 3
4 5 6 7 
8 9 10 11 
12 13 14 15
*/