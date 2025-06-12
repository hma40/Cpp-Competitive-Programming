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
// #define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll gcd(ll a, ll b) {
    a=abs(a);
    b=abs(b);
    if(a>b) swap(a,b);
    while(a!=0) {
        int t = a;
        a=b%a;
        b=t;
    }
    return b;
}
pair<int,int> frac(int num, int den) {
    int g = gcd(num,den);
    num/=g;
    den/=g;
    return {num,den};
}
pair<int,int> operator+(pair<int,int> a, pair<int,int> b) {
    int num = a.f*b.s+a.s*b.f;
    int den = a.s*b.s;
    return frac(num,den);
}
pair<int,int> operator-(pair<int,int> a, pair<int,int> b) {
    int num = a.f*b.s-a.s*b.f;
    int den = a.s*b.s;
    return frac(num,den);
}
pair<int,int> operator*(pair<int,int> a, pair<int,int> b) {
    int num = a.f*b.f;
    int den = a.s*b.s;
    return frac(num,den);
}
int inv(int b, int e) {
    // cout << "LINE 182 " << e << endl;
    int M = e;
    e-=2;
    if(e<0) return 0;
    int ans = 1;
    while(e) {
        // cout << ans << " " << b << " " << M << endl;
        if(e&1) ans=ans*b%M;
        b=b*b%M;
        e>>=1;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,x,y,vx,vy;
        cin >> n >> x >> y >> vx >> vy;
        /*
        2+5t == 0 mod 6
        t = 4/5+6k1/5

        2+2t == 0 mod 6
        t=4/2+6k2/2

        4/5+6k1/5 = 4/2+6k2/2
        8+12k1=20+30k2
        12k1-12=30k2
        2k1-2=5k2
        
        for third one:
        2+2t=0 mod 6
        t=2+3k1
        */
        
        /*
        generally
        (n-x)/vx + n k1/vx = (n-y)vy + n k2/vy
        mult by vxvy

        (n-x)vy + n vy k1 = (n-y) vx + n vx k2
        simplifying
        */
        int con = (n-x)*vy-(n-y)*vx;
        int g = gcd(gcd(con, n*vy), n*vx);
        con/=g;
        int k1_coef = vy*n/g;
        int k2_coef = vx*n/g;
        // cout << con << " " << k1_coef << " " << k2_coef << endl;
        if(gcd(k1_coef,k2_coef)!=1) {
            cout << -1 << endl;
            continue;
        }
        con*=-1;
        int k1 = con*inv(k1_coef, k2_coef);
        k1%=k2_coef;
        k1+=k2_coef;
        k1%=k2_coef;
        // cout << "LINE 244 " << k1 << endl;
        auto t = frac(n-x,vx)+frac(k1,1)*frac(n,vx);
        // cout << t << n << " " << x << " " << y << " " << vx << " " << vy << endl;
        pair<int,int> loc;
        loc.f = ((t*frac(vx,1))+frac(x,1)).f;
        loc.s = ((t*frac(vy,1))+frac(y,1)).f;
        // cout << loc << endl;
        int ans = loc.f/n-1+loc.s/n-1;
        int sum = loc.f+loc.s;
        int first = n, diff = 2*n;
        int las = (sum-1-n)/diff*diff+first;
        // cout << las << endl;
        ans+=(las-first)/diff+1;
        int beg_diff = x-y;
        int end_diff = loc.f-loc.s;
        // cout << beg_diff << " " << end_diff << endl;
        if(beg_diff<end_diff) {
            //find first number >= beg_diff and last number < end_diff
            //(2k+1)n
            __int128_t lo = -inf, hi = inf;
            while(lo+1<hi) {
                __int128_t mid = (lo+hi)/2;
                if((mid*2+1)*n>=beg_diff) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            __int128_t lo2 = -inf, hi2 = inf;
            while(lo2+1<hi2) {
                __int128_t mid = (lo2+hi2)/2;
                if((mid*2+1)*n<end_diff) {
                    lo2=mid;
                } else {
                    hi2=mid;
                }
            }
            // cout << "LINE 284 " << lo2 << " " << hi << endl;
            ans+=lo2-hi+1;
        } else {
            __int128_t lo = -inf, hi = inf;
            while(lo+1<hi) {
                __int128_t mid = (lo+hi)/2;
                if((mid*2+1)*n<=beg_diff) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            __int128_t lo2 = -inf, hi2 = inf;
            while(lo2+1<hi2) {
                __int128_t mid = (lo2+hi2)/2;
                if((mid*2+1)*n>end_diff) {
                    hi2=mid;
                } else {
                    lo2=mid;
                }
            }
            // cout << "LINE 305 " << lo2 << " " << hi << endl;
            ans+=lo-hi2+1;
        }
        cout << ans << endl;
    }
    return 0;
}