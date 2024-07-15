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
    vt<int> facts;
    vt<int> invFact;
    vt<bool> isPrime;
    vt<int> primes;
    Math(int m):mod(m) {}
    int bexpo(int b, int e) {
        int a = 1;
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
    int nck(int n, int k) {
        return facts[n]*invFact[k]%mod*invFact[n-k]%mod;
    }
    int npk(int n, int k) {
        return facts[n]*invFact[n-k]%mod;
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
    int t;
    cin >> t;
    Math m(1000000007);
    m.fact(200005);
    while(t-- ){
        int n,m1,m2;
        cin >> n >> m1 >> m2;
        vt<int> pmax(m1),smax(m2);
        F0R(i, m1) cin >> pmax[i];
        F0R(i, m2) cin >> smax[i];
        if(pmax.back()!=smax[0]) {
            cout << 0 << endl;
            continue;
        }
        if(pmax[0]!=1||smax.back()!=n) {
            cout << 0 << endl;
            continue;
        }
        reverse(begin(smax),end(smax));

        // cout << m.facts << endl;
        int md = 1000000007;
        int ans = m.nck(n-1, pmax.back()-1);
        // cout << ans << endl;
        int numbers = pmax.back()-1;
        while(pmax.size()>1) {
            ans*=m.npk(numbers-1,pmax[pmax.size()-1]-pmax[pmax.size()-2]-1);
            // cout << "LINE 151 MULTIPLYING ANS BY " << numbers-1 << " choose " << pmax[pmax.size()-1]-pmax[pmax.size()-2]-1 << endl;
            ans%=md;
            pmax.pop_back();
            numbers=pmax.back()-1;
        }
        numbers = n-smax.back();
        while(smax.size()>1) {     
            // cout << "LINE 159 MULTIPLYING ANS BY " << numbers-1 << " choose " << smax[smax.size()-2]-smax[smax.size()-1]-1 << endl;
            ans*=m.npk(numbers-1, smax[smax.size()-2]-smax[smax.size()-1]-1);

            ans%=md;
            smax.pop_back();
            numbers=n-smax.back();
        }
        cout << ans << endl;
    }
    return 0;
}