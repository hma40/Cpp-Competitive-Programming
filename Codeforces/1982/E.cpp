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
const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
map<pair<int,int>,array<int,3>> mp;//mp[{x, k}]={first, ans, last}
int solve(int n, int k) {
    // cout << n << " " << k << endl;
    if(mp.count({n,k})) return mp[{n,k}][1];
    if(n==0) {
        mp[{n,k}][0]=mp[{n,k}][2]=-1;
        mp[{n,k}][1]=1;
        return 1;
    }
    if(k==0) {
        mp[{n,k}][0]=1;
        mp[{n,k}][2]=0;
        mp[{n,k}][1]=1;
        return 1;
    }
    R0F(i, 62) {
        if(n&(1LL<<i)) {
            pair<int,int> fir = {(1LL<<i)-1, k}, sec = {n-(1LL<<i), k-1};
            solve(fir.f,fir.s);
            solve(sec.f,sec.s);
            if(mp[fir][0]==-1 && mp[sec][0] == -1) {
                int m = (n+1)%mod;
                int ans = m*(m+1)/2;
                ans%=mod;
                mp[{n,k}]={-1, ans, -1};
                return ans;
            } else if(mp[fir][0]==-1) {
                mp[{n,k}][0]=(fir.f+1+mp[sec][0])%mod;
                mp[{n,k}][2]=mp[sec][2];
                int ans = mp[sec][1]+mp[fir][1];
                ans+=mp[sec][0]*((fir.f+1)%mod);
                ans%=mod;
                mp[{n,k}][1]=ans;
                return ans;
            } else if(mp[sec][0]==-1) {
                mp[{n,k}][0]=mp[fir][0];
                mp[{n,k}][2]=(mp[fir][2]+sec.f+1)%mod;
                int ans = mp[fir][1]+mp[sec][1];
                ans+=mp[fir][2]*((sec.f+1)%mod);
                ans%=mod;
                mp[{n,k}][1]=ans;
                return ans;
            } else {
                mp[{n,k}][0]=mp[fir][0];
                mp[{n,k}][2]=mp[sec][2];
                int ans = mp[fir][1]+mp[sec][1];
                ans+=mp[fir][2]*mp[sec][0];
                ans%=mod;
                mp[{n,k}][1]=ans;
                return ans;
            }
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        cout << solve(n-1,k) << endl;    
        // cout << mp << endl;
    }
    return 0;
}