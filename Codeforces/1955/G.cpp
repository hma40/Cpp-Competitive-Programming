#include <bits/stdc++.h>
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
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
int n,m;
vt<vt<int>> v;
struct Math {
    ll m;
    vt<ll> facts;
    vt<ll> invFact;
    vt<int> lp;
    vt<int> primes;
    vt<vt<int>> allFactors;
    Math(int md):m(md) {}
    Math(): m(1000000007) {};
    ll bexpo(ll b, int e) {
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
    ll gcd(ll a, ll b) {
        if(a>b) swap(a,b);
        while(a!=0) {
            int t = a;
            a=b%a;
            b=t;
        }
        return b;
    }
    ll lcm(ll a, ll b) {
        return a/gcd(a,b)*b;
    }
    ll inv(ll x) {
        return bexpo(x, m-2);
    }
    vt<int> factorize(int x) {
        vt<int> factors;
        for(int i = 1; i*i<=x; i++) {
            if(x%i==0) {
                factors.add(i);
                if(i*i!=x) factors.add(x/i);
            }
        }
        return factors;
    }
    void factorAll(int bound) {
        allFactors.assign(bound+1, vt<int>{});
        FOR(i, 1, bound+1) {
            for(int j = i; j <= bound; j+=i) {
                allFactors[j].add(i);
            }
        }
    }
};  
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    Math math(3);
    cin >> t;
    while(t--) {
        // int n,m;
        cin >> n >> m;
        v.assign(n,vt<int>(m,0));
        F0R(i, n) {
            F0R(j, m) cin >> v[i][j];
        }
        int g = math.gcd(v[0][0], v.back().back());
        vt<int> fact;
        for(int i = 1; i*i<=g; i++) {
            if(g%i==0) {
                fact.add(i);
                fact.add(g/i);
            }
        }
        int ans = 1;
        vt<vt<bool>> dp(n, vt<bool>(m));
        trav(x, fact) {
            dp[0][0]=true;
            FOR(i, 1, n) {
                if(v[i][0]%x==0) {
                    dp[i][0]=dp[i-1][0];
                } else {
                    dp[i][0]=false;
                }
            }
            FOR(i, 1, m) {
                if(v[0][i]%x==0) {
                    dp[0][i]=dp[0][i-1];
                } else {
                    dp[0][i]=false;
                }
            }
            FOR(i, 1, n) {
                FOR(j, 1, m) {
                    if(v[i][j]%x==0) {
                        dp[i][j]=dp[i-1][j]||dp[i][j-1];
                    } else {
                        dp[i][j]=false;
                    }
                }
            }
            if(dp[n-1][m-1]) ans=max(ans,x);
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
3 5
8 18 10 3 20
19 1 18 4 8
8 2 5 13 10
*/