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
ll mod = 998244353;
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
Math m(mod);
map<int,pair<int,int>> fuck;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void get_data(int count) {
    // cout << count << endl;
    int left = (count+1)/2, right = count/2;
    if(!fuck.count(left)) get_data(left);
    if(!fuck.count(right)) get_data(right);
    int fuck0=0,fuck1=0;
    fuck0+=2*fuck[left].f;
    fuck0+=2*fuck[right].f;
    int choiceLeft = m.bexpo(2, left);
    choiceLeft--;
    choiceLeft+=mod;
    choiceLeft%=mod;
    int choiceRight = m.bexpo(2,right);
    choiceRight--;
    choiceRight+=mod;
    choiceRight%=mod;
    choiceLeft*=choiceRight;
    choiceLeft%=mod;
    fuck0+=choiceLeft;
    fuck0%=mod;
    fuck1+=fuck[left].s;
    fuck1+=fuck[right].s;
    fuck1+=fuck[right].f;
    fuck1%=mod;
    fuck[count]={fuck0,fuck1};
}
int solve(int root, int count) {
    if(!fuck.count(count)) {
        get_data(count);
    }
    return (root%mod*fuck[count].f%mod+fuck[count].s)%mod;
}

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fuck[1]={1,0};
    //fuck[2]={}
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        cout << solve(1,n) << endl;
    }
    return 0;
}
/*
n
2n 2n+1

2n+2n+1+n=5n+1
*/