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
// #define int long long
#define vt vector
// #define endl "\n"
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
struct Math {
    int mod;
    vt<ll> facts;
    vt<ll> invFact;
    vt<bool> isPrime;
    vt<int> primes;
    Math(int m):mod(m) {}
    int bexpo(ll b, ll e) {
        ll a = 1;
        while(e) {
            if(e%2) {
                a*=b;
                a%=mod;
            }
            e/=2;
            b*=b;
            b%=mod;
        }
        return a;
    }
    void fact(int bound) {
        facts.assign(bound,0);
        invFact.assign(bound,0);
        facts[0]=invFact[0]=1;
        FOR(i, 1, bound) {
            facts[i]=facts[i-1]*i;
            facts[i]%=mod;
            invFact[i]=bexpo(facts[i], mod-2);
        }
    }
    void sieve(int bound) {
        isPrime.assign(bound, true);
        primes.clear();
        FOR(i, 2, bound) {
            if(isPrime[i]) {
                primes.add(i);
                for(int j = i*i; j < bound; j+=i) {
                    isPrime[j]=false;
                }
            }
        }
    }
    ll nck(int n, int k) {
        if(k==0) return 1;
        if(n<k||k<0||n<0) return 0;
        // ll ans = 1;
        // ans*=facts[n];
        // if(ans<0) {
        //     cout << "102" << endl;
        //     cout << n << " " << k << " " << ans << endl;
        //     assert(false);
        // }
        // ans*=invFact[k];
        // // if(ans<0) {
        // //     cout << "108" << endl;
        // //     cout << n << " " << facts[n] << endl;
        // //     cout << n << " " << k << " " << ans << " " << facts[n] << " " << invFact[k] << endl;
        // //     assert(false);
        // // }
        // ans%=mod;
        // ans*=invFact[n-1];
        // if(ans<0) {
        //     cout << "115" << endl;
        //     cout << n << " " << k << " " << ans << endl;
        //     assert(false);
        // }
        // ans%=mod;
        return facts[n]*invFact[k]%mod*invFact[n-k]%mod;
        // return ans;
    }
    int gcd(int a, int b) {
        if(a>b) swap(a,b);
        while(a!=0) {
            int t = a;
            a=b%a;
            b=t;
        }
        return b;
    }
    int lcm(int a, int b) {
        return a/gcd(a,b)*b;
    }
    int inv(int x) {
        return bexpo(x, mod-2);
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
};  
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    Math m(1e9+7);
    m.fact(10010);
    // cout << m.facts << endl;
    // return 0;
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> dp(2*n+2, vt<int>(n+1));
        //dp[i][j]: mex = i, length = j
        FOR(i, 1, 2*n+2) {
            F0R(j, n+1) {
                //empty spaces: i-1-j
                //i-1 choose i-1-j
                //1 2 3 4 5
                //1 2 (3 4 5)
                //other one is (n-1-i) choose (2j-i+1)
                // cout << i << " " << j << " " << i-1 << " " << i-1-j << " " << n-1-i << " " << 2*j+1-i << endl;
                dp[i][j]=(ll)(m.nck(min(n, i-1), i-1-j)) * m.nck(max(0,n-i), 2*j-i+1) % mod;
                // assert(dp[i][j]>0);
                if(dp[i][j]<0) {
                    cout << i << " " << j << " " << i-1 << " " << i-1-j << " " << n-1-i << " " << 2*j+1-i << endl;
                    cout << m.nck(min(n, i-1), i-1-j) << endl;
                    cout << m.nck(max(0,n-i), 2*j-i+1) << endl;
                    cout << (ll)(m.nck(min(n, i-1), i-1-j)) * m.nck(max(0,n-i), 2*j-i+1) % mod << endl;
                    return 0;
                }
            }
        }
        ll ans = 0;
        FOR(i, 1, 2*n+2) {
            F0R(j, n+1) {
                ans+=(ll)i*dp[i][j];
                ans%=mod;
            }
        }
        // cout << dp << endl;
        cout << ans << endl;
    }
    return 0;
}
/*
{}: 1
1: 3
2: 3
3: 2

*/