#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
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
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
vector<ll> comb(vt<int> pr) {
    map<int,int> p;
    // cout << "LINE 310 " << n << " " << pr << endl;
    for (ll x : pr){
        p[x]++;
    }
    // cout << p << endl;
    vector<ll> out = {1};
    for (auto& x : p) {
        ll q = x.f;
        int f = x.s;
        vector<ll> tmp;
            for (ll x : out) {
                ll r = 1;
                for (int i = 0; i <= f; i+=2) {
                    tmp.push_back(x*r);
                    r *= q;
                }
            }
        out = tmp;
    }
    return out;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    vt<int> lp(1000001);
    vt<int> primes;
    for(int i = 2; i <= 1000000; i++) {
        if(lp[i]==0) {
            lp[i]=i;
            primes.add(i);
        }
        for(int j = 0;i * primes[j]<=1000000; j++) {
            lp[i*primes[j]]=primes[j];
            if(primes[j]==lp[i]) break;
        }
    }
    map<int,int> squares;
    for(int i = 1; i * i <= 1000000000; i++) {
        squares[i*i]=i;
    }
    while(t--) {
        int n;
        cin >> n;
        unordered_map<int,int,custom_hash> mp;
        // unordered_map<int,int,custom_hash> mp;
        vt<int> a(n);
        F0R(i, n) {
            cin >> a[i];
            mp[a[i]]++;
        }

        int ans = 0;
        trav(x, mp) ans+=x.s*(x.s-1)*(x.s-2);
        // cout << "LINE 360 " << ans << endl;
        F0R(i, n) {
            vt<int> factors;
            int tmp = a[i];
            for(int x = 2; x <= 1000; x++) {
                while(tmp%x==0) {
                    tmp/=x;
                    factors.add(x);
                }
            }
            if(tmp<=1000000) {
                while(tmp!=1) {
                    factors.add(lp[tmp]);
                    tmp/=lp[tmp];
                }
            } else {
                if(squares.count(tmp)) {
                    factors.add(squares[tmp]);
                    factors.add(squares[tmp]);
                }
            }
            trav(x, comb(factors)) {
                // cout << i << " " << x << endl;
                if(x==1) continue;
                int bef = a[i]/x, aft = a[i]/x/x;
                if(mp.count(bef) && mp.count(aft)) ans+=mp[bef]*mp[aft];
            }
            // cout << i << " " << ans << endl;
        }
        cout << ans << endl;
    }
    return 0;
}