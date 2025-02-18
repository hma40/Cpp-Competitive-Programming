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
// #define endl "\n"
#define double long double
ll mod = 998244353;
    ll gcd(ll a, ll b) {
        if(a>b) swap(a,b);
        while(a!=0) {
            int t = a;
            a=b%a;
            b=t;
        }
        return b;
    }
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int BOUND = 100005;
    vt<vt<int>> factors(BOUND+1);
    for(int i = BOUND; i > 0; i--) {
        for(int j = 2*i; j <= BOUND; j+=i) factors[j].add(i);
    }
    vt<int> lp;
    lp.resize(BOUND+1, 0);
    vt<int> primes;
    for(int i = 2; i < BOUND+1; i++) {
        if(lp[i]==0) {
            lp[i]=i;
            primes.add(i);
        }
        for(int j = 0;i * primes[j]<=BOUND; j++) {
            lp[i*primes[j]]=primes[j];
            if(primes[j]==lp[i]) break;
        }
    }
    vt<int> phi(BOUND+1);
    phi[1]=0;
    FOR(i, 2, BOUND+1) {
        phi[i]=i;
        set<int> pr;
        int temp = i;
        while(temp!=1) {
            pr.insert(lp[temp]);
            temp/=lp[temp];
        }
        vt<int> uniqs;
        trav(x, pr) uniqs.add(x);
        FOR(mask, 1, 1<<uniqs.size()) {
            int prod = 1;
            F0R(j, uniqs.size()) if(mask&(1<<j)) prod*=uniqs[j];
            if(__builtin_popcount(mask)%2) {
                //subtract
                phi[i]-=i/prod;
            } else {
                //add
                phi[i]+=i/prod;
            }
        }
    }
    vt<int> pow2(BOUND+1);
    pow2[0]=1;
    FOR(i, 1, BOUND+1) pow2[i]=pow2[i-1]*2%mod;
    int t = 1;
    cin >> t;
    while(t--) {
        int m;
        cin >> m;
        map<int,int> mp;
        map<pair<int,int>,vt<array<int,3>>> mp;//(G, Last)->(G, Last, count)
        
        for(int curg = 2; curg <= m; curg++) {
            for(int curlast = curg; curlast <= m; curlast+=curg) {
                for(auto ng: factors[curg]) {
                    if(ng==1) {
                        
                    } else {

                    }
                }
            }
        }
        for(int i = 2; i <= m; i++) {
            vt<map<pair<int,int>,int>> v(factors[i].size()+5);
            v[1][{i,i}]=1;
            FOR(ff, 1, factors[i].size()+4) {
                trav(x, v[ff]) {
                    int curg = x.f.f;
                    int curlast = x.f.s;
                    trav(newg, factors[curg]) {
                        for(int nx = newg; nx < curlast; nx+=newg) {
                            if(gcd(nx,curg)!=newg) continue;
                            v[ff+1][{newg,nx}]+=x.s;
                        }
                    }
                    mp[ff]+=x.s;
                }
            }
            // cout << i << v << endl;
        }
        // cout << mp << endl;
        int ans = 0;
        trav(x, mp) {
            ans+=pow2[x.f-1]*x.s;
            ans%=mod;
        }
        cout << ans+1 << endl;
    }
    return 0;
}