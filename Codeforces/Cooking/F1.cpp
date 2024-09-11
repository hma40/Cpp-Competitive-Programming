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
struct Math {
    ll m;
    vt<ll> facts;
    vt<ll> invFact;
    int curSieve = 0;
    //lp is 0 if its prime
    vt<int> lp;
    vt<int> primes;
    vt<vt<int>> allFactors;
    vt<int> mobius;
    Math(int md):m(md) {}
    Math(): m(1000000007) {};
    void mob(int n) {
        mobius.assign(n+1,-1);
        vt<int> p(n+1, 1);
        mobius[0] = 0, mobius[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (p[i]) {
                for (int j = 2; j*i <= n; j++) {
                    // cout << "LINE 142 " << i << " " << j << endl;
                    if (j%i) mobius[i*j] = mobius[i]*mobius[j];
                    else mobius[i*j] = 0;
                    p[i*j] = 0;
                }
            }
        }
    }
    ll bexpo(ll b, ll e) {
        ll a = 1;
        while(e) {
            if(e%2) {
                a*=b;
                a%=m;
            }
            e/=2;
            b*=b;
            b%=m;
        }
        return a;
    }
    void fact(int bound) {
        facts.assign(bound,0);
        invFact.assign(bound,0);
        facts[0]=invFact[0]=1;
        FOR(i, 1, bound) {
            facts[i]=facts[i-1]*i;
            facts[i]%=m;
            invFact[i]=bexpo(facts[i], m-2);
        }
    }
    void sieve(int bound) {
        if(curSieve>=bound) return;
        curSieve=bound;
        lp.assign(bound+1, 0);
        primes.clear();
        for(int i = 2; i <= bound; i++) {
            if(lp[i]==0) {
                lp[i]=i;
                primes.add(i);
            }
            for(int j = 0;i * primes[j]<=bound; j++) {
                lp[i*primes[j]]=primes[j];
                if(primes[j]==lp[i]) break;
            }
        }
    }
    ll nck(int n, int k) {
        if(n<k||k<0||n<0) return 0;
        return facts[n]*invFact[k]%m*invFact[n-k]%m;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    Math ma(mod);
    ma.fact(200005);
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> l(n);
        F0R(i, n) cin >> l[i].f >> l[i].s;
        vt<pair<int,int>> r = l;
        sort(begin(l),end(l), [](const auto a, const auto b)->bool{
            if(a.f==b.f) return a.s<b.s;
            return a.f<b.f;
        });
        sort(begin(r),end(r), [](const auto a, const auto b)->bool{
            if(a.s==b.s) return a.f<b.f;
            return a.s<b.s;
        });

        // cout << l << r <<  endl;
        int ans = 0;
        F0R(i, n) {
            F0R(j, n) {
                // cout << i << " " << j << " " << l[i].f << " " << r[i].s << endl;
                if(l[i].f<=r[j].s) {
                    continue;
                }
                // cout << i << " " << j << " " << l[i] << r[i] << endl;
                int mul = l[i].f-r[j].s;
                int lleft = n-i-1;
                int rleft = j;
                int left = n-lleft-rleft-2;
                mul*=ma.nck(lleft+rleft, lleft);
                mul%=mod;
                mul*=ma.bexpo(2, left);
                mul%=mod;
                ans+=mul;
                ans%=mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}