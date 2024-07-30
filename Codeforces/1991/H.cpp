#include <bits/stdc++.h>
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
struct Math {
    ll m;
    vt<ll> facts;
    vt<ll> invFact;
    vt<int> lp;
    vt<int> primes;
    vt<vt<int>> allFactors;
    Math(int md):m(md) {}
    Math(): m(1000000007) {};
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
struct FFT{
    ll mod;
    ll bexpo(ll b, ll e) {
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
    vt<ll> invPow; //invPow[i] = the 2^ith root of unity
    vt<ll> invv;
    FFT(bool first) {
        if(first) {
            mod=998244353;
            invPow.assign(24, 0);
            invv.resize(24);
            invPow[23]=31;
            for(int i = 22; i >= 0; i--) {
                invPow[i]=(invPow[i+1]*invPow[i+1])%mod;
            }
            F0R(i, 24) {
                invv[i]=bexpo(invPow[i], mod-2);
            }
        } else {
            mod=167772161;
            invPow.assign(25, 0);
            invPow[24]=2;
            invv.resize(25);
            for(int i = 23; i >= 0; i--) {
                invPow[i]=(invPow[i+1]*invPow[i+1])%mod;
            }
            F0R(i, 25) {
                invv[i]=bexpo(invPow[i], mod-2);
            }
        }
        // cout << invPow << endl;
    }
    void transform(vt<ll> &coefs, int index) {
        int n = coefs.size();
        if(n==1) {
            return;
        }
        ll omega = invPow[index];
        vt<ll> even(n/2),odd(n/2);
        for(int i = 0; i < n; i+=2) {
            even[i/2]=coefs[i];
            odd[i/2]=coefs[i+1];
        }
        transform(even, index-1);
        transform(odd, index-1);
        // vt<ll> ret(n);
        ll powOmega = 1;
        F0R(i, n/2) {
            coefs[i]=even[i]+powOmega*odd[i];
            coefs[i]%=mod;
            coefs[i+n/2]=even[i]-powOmega*odd[i];
            coefs[i+n/2]%=mod;
            coefs[i+n/2]+=mod;
            coefs[i+n/2]%=mod;
            powOmega*=omega;
            powOmega%=mod;
        }
    }
    void invFFT(vt<ll> &coefs, int index) {
        int n = coefs.size();
        if(n==1) {
            return;
        }
        ll omega = invv[index];
        vt<ll> even(n/2),odd(n/2);
        for(int i = 0; i < n; i+=2) {
            even[i/2]=coefs[i];
            odd[i/2]=coefs[i+1];
        }
        invFFT(even, index-1);
        invFFT(odd, index-1);
        ll powOmega = 1;
        F0R(i, n/2) {
            coefs[i]=even[i]+powOmega*odd[i];
            coefs[i]%=mod;
            coefs[i+n/2]=even[i]-powOmega*odd[i];
            coefs[i+n/2]%=mod;
            coefs[i+n/2]+=mod;
            coefs[i+n/2]%=mod;
            powOmega*=omega;
            powOmega%=mod;
        }
    }
    vt<ll> mult(vt<ll> a, vt<ll> b) {
        ll sz = a.size()+b.size()-1;
        ll sz2 = 1;
        int pow2 = 0;
        while(sz2<sz) {
            sz2*=2;
            pow2++;
        }
        while(a.size()<sz2) a.add(0);
        while(b.size()<sz2) b.add(0);
        transform(a, pow2);
        transform(b, pow2);
        F0R(i, sz2) {
            a[i]*=b[i];
            a[i]%=mod;
        }
        invFFT(a, pow2);
        ll inv = bexpo(sz2, mod-2);
        trav(x, a) x=x*inv%mod;
        while(a.size()>sz) a.pop_back();
        return a;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    Math m;
    FFT f(false);
    int MAXN = 200001;
    m.sieve(MAXN);
    vt<bool> prime(MAXN), winning(MAXN);
    trav(x, m.primes) {
        prime[x]=true;
    }
    winning[1]=false;
    for(int i = 3; i < MAXN; i+=2) {
        if(prime[i-2]&&!winning[i-2]) {
            winning[i]=true;
        }
    }
    // cout << winning << endl;
    vt<int> poly(MAXN);
    for(int i = 1; i < poly.size(); i+=2) {
        if(prime[i]&&!winning[i]) {
            poly[i]=1;
        } 
    }
    poly=f.mult(poly,poly);
    F0R(i, MAXN) {
        if(poly[i]) {
            winning[i]=true;
        }
    }
    winning[4]=true;
    poly.assign(MAXN, 0);
    vt<bool> good(MAXN);
    for(int i = 1; i < poly.size(); i+=2) {
        if(prime[i]&&winning[i]) {
            poly[i]=1;
        }
    }
    // cout << poly[19] << endl;
    poly=f.mult(poly,poly);
    // cout << poly << endl;
    // cout << poly[38] << winning[38] << endl;
    F0R(i, MAXN) {
        if(poly[i]) good[i]=true;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        int win=0, gud=0;
        F0R(i, n) {
            if(winning[v[i]]) win++;
            if(good[v[i]]) gud++;
        }
        if(n%2==0) {
            if(win>0) {
                cout << "ALICE" << endl;
            } else {
                cout << "BOB" << endl;
            }
        } else {
            if(win==0) {
                cout << "BOB" << endl;
            } else if(win==n) {
                if(gud==0) {
                    cout << "BOB" << endl;
                } else if(gud==n) {
                    cout << "BOB" << endl;
                } else {
                    cout << "ALICE" << endl;
                }
            } else {
                cout << "ALICE" << endl;
            }
        }
    }
    return 0;
}
/*
38=19+19
is 19 winning? YES!
*/
/*
1991H - Prime Split Game

Now have: is each position winning or losing if it is the only active number?
Now what if there are multiple active numbers?

If you have all losing numbers:
- No matter what you do, opponent can always just bring you to a board of losing numbers, so you lose

If n is even and you have any winning numbers:
- you win

If n is odd and you have at most n-1 winning numbers:
- You win, similarly

If n is odd and you have n winning numbers:
- Lets say you remove k numbers and split k more into 2k losing numbers
now you have 2k losing numbers and n-2k winning numbers
BUT!!! Winning number can sometimes be split into two winning numbers. Call these numbers good
How do you find good numbers? again FFT
*/
/*
1: LOSING
3: LOSING
5: WINNING
7: LOSING
9: WINNING
11: LOSING
13: WINNING
*/
/*
1
5
74970 81070 73596 181411 186486
*/