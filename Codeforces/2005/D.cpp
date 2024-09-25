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
ll gcd(ll a, ll b) {
    if(a>b) swap(a,b);
    while(a!=0) {
        int t = a;
        a=b%a;
        b=t;
    }
    return b;
}
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=gcd(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getGCD(int lo, int hi) {
        if(lo>hi) return 0;
        // cout << lo << " " << hi << endl;
        int log = lg[hi-lo+1];
        return gcd(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
pair<int,int> bruteforce(int n, vt<int> &a, vt<int> &b) {
    int best=0, count=0;
    RMQ armq(a, 8), brmq(b, 8);
    F0R(start, n) {
        FOR(end, start, n) {
            //g = gcd(a[0...start-1], b[start...end], a[end+1...n])
            int hr = gcd(gcd(armq.getGCD(0, start-1), brmq.getGCD(start, end)), armq.getGCD(end+1, n-1));
            hr += gcd(gcd(brmq.getGCD(0, start-1), armq.getGCD(start, end)), brmq.getGCD(end+1, n-1));
            if(hr>best) {
                best=hr;
                count=1;
            } else if(hr==best) {
                count++;
            } 
        }
    }
    return {best, count};
}
pair<int,int> solve(int n, vt<int> &a, vt<int> &b) {
    /*
    Suppose we fix A, B
    Lets say gcd(0...l1) is divisible by A but gcd(0...l1+1) is not
    and say gcd(r1...n) is divisible by A but gcd(r1-1...n) is not
    similarly l2, r2 for B
    then, the segment we want to replace is [min(l1,l2), max(r1,r2)]
    brute force over all
    */
    RMQ armq(a, 20), brmq(b, 20);
    // assert(false);
    set<int> weCare;
    FOR(i,1, n) {
        if(armq.getGCD(0,i)!=armq.getGCD(0, i-1)) weCare.insert(i);
        if(brmq.getGCD(0,i)!=brmq.getGCD(0, i-1)) weCare.insert(i);
    }
    F0R(i, n-1) {
        if(armq.getGCD(i,n-1)!=armq.getGCD(i+1,n-1)) weCare.insert(i);
        if(brmq.getGCD(i,n-1)!=brmq.getGCD(i+1,n-1)) weCare.insert(i);
    }
    // assert(false);
    weCare.insert(0);
    weCare.insert(n-1);
    int best=0;
    
    for(int start: weCare) {
        for(int end: weCare) {
            if(start>end) continue;
            int hr = gcd(gcd(armq.getGCD(0, start-1), brmq.getGCD(start, end)), armq.getGCD(end+1, n-1));
            hr += gcd(gcd(brmq.getGCD(0, start-1), armq.getGCD(start, end)), brmq.getGCD(end+1, n-1));
            if(hr>best) {
                best=hr;
            } 
        }
    }
    int ans = 0;
    F0R(i, n) {
        int hr = gcd(armq.getGCD(0,i),brmq.getGCD(i+1,n-1));
        hr+=gcd(brmq.getGCD(0,i),armq.getGCD(i+1,n-1));
        if(hr==best) ans++;
    }
    // assert(false);
    vt<int> factors;
    for(int i = 1; i*i<=a[0]; i++) {
        if(a[0]%i==0) {
            factors.add(i);
            if(i!=a[0]/i) {
                factors.add(a[0]/i);
            }
        }
    }
    // cout << "LINE 240 " << ans << endl;
    // assert(false);
    for(auto f: factors) {
        int s = best-f;
        // cout << f << " " << s << endl;
        if(s<=0||b[0]%s!=0) continue;
        vt<vt<int>> dp(n, vt<int>(3));
        dp[0][0]=1;
        for(int i = 1; i < n; i++) {
            if(a[i]%f==0&&b[i]%s==0) {
                dp[i][0]+=dp[i-1][0];
                dp[i][2]+=dp[i-1][2];
            }
            if(a[i]%s==0&&b[i]%f==0) {
                dp[i][1]+=dp[i-1][0];
                dp[i][1]+=dp[i-1][1];
                dp[i][2]+=dp[i-1][0]+dp[i-1][1];
            }
        }
        // cout << f << " " << s << " " << dp << endl;
        ans+=dp[n-1][2];
    }
    return {best,ans};
}

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n), b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        if(n<=100) {
            auto x = bruteforce(n,a,b);
            cout << x.f << " " << x.s << endl;
        } else {
            auto x = solve(n,a,b);
            cout << x.f << " " << x.s << endl;
        }
    }
    return 0;
}
/*
1
5
1 10 2 10 2
3 8 1 9 4
*/