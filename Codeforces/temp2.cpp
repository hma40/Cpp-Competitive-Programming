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
int phi(int x, vt<int> &primes) {
    trav(y, primes) {
        if(x%y==0) {
            x=x*(y-1)/y;
        }
    }
    return x;
}
int solve(int bound, int num, vt<int> &fact, vt<int> &mobius) {
    // cout << "SOLVE CALLED FOR " << bound << " " << num << " " << fact << " " << mobius << endl;
    int ans = 0;
    F0R(i, fact.size()) {
        if(num%fact[i]==0) {
            ans+=mobius[i]*(bound/fact[i]);
        }
    }
    // cout << "RETURNING " << ans << endl;
    return ans;
}
std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int a,b,d;
        cin >> a >> b >> d;
        if(a>b) swap(a,b);
        // int ans = 0, fullCyc = 0;
        vt<int> factors,primeFactors;
        b-=a;
        int bb = b;
        for(int i = 2;i*i<=bb; i++) {
            if(bb%i==0) {
                primeFactors.add(i);
                while(bb%i==0) {
                    bb/=i;
                }
            }
        }
        if(bb>1) primeFactors.add(bb);
        bb=b;
        for(int i = 1; i*i<=bb; i++) {
            if(bb%i==0) {
                factors.add(i);
                if(i!=bb/i) {
                    factors.add(bb/i);
                }
            }
        }
        vt<int> mobius;
        trav(x, factors) {
            int mob = 1;
            trav(y, primeFactors) {
                if(x%y==0) {
                    if(x%(y*y)==0) {
                        mob=0;
                    } else {
                        mob*=-1;
                    }
                }
            }
            mobius.add(mob);
        }
        // cout << b << " " << factors << primeFactors << mobius << endl;
        int ans = 0;
        int ub = a+d, lb = a-1;
        trav(x, factors) {
            ans+=x*(solve(ub/x,b/x,factors,mobius)-solve(lb/x,b/x,factors,mobius));
            ans%=mod;
        }
        cout << ans << endl;
    }
    return 0;
}