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
#define ROF(i,a,b) for (int i = (b)-1LL; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct FFT{
    ll mod;
    ll bexpo(ll b, ll e) {
        ll a = 1LL;
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
                invPow[i]=(invPow[i+1LL]*invPow[i+1LL])%mod;
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
                invPow[i]=(invPow[i+1LL]*invPow[i+1LL])%mod;
            }
            F0R(i, 25) {
                invv[i]=bexpo(invPow[i], mod-2);
            }
        }
        // cout << invPow << endl;
    }
    void transform(vt<ll> &coefs, int index) {
        int n = coefs.size();
        if(n==1LL) {
            return;
        }
        ll omega = invPow[index];
        vt<ll> even(n/2),odd(n/2);
        for(int i = 0; i < n; i+=2) {
            even[i/2]=coefs[i];
            odd[i/2]=coefs[i+1LL];
        }
        transform(even, index-1LL);
        transform(odd, index-1LL);
        // vt<ll> ret(n);
        ll powOmega = 1LL;
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
        if(n==1LL) {
            return;
        }
        ll omega = invv[index];
        vt<ll> even(n/2),odd(n/2);
        for(int i = 0; i < n; i+=2) {
            even[i/2]=coefs[i];
            odd[i/2]=coefs[i+1LL];
        }
        invFFT(even, index-1LL);
        invFFT(odd, index-1LL);
        ll powOmega = 1LL;
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
        ll sz = a.size()+b.size()-1LL;
        ll sz2 = 1LL;
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
vt<ll> bexpo(vt<ll> orig, ll times) {
    FFT f(false);
    // cout << orig << times << endl;
    vt<ll> ans = {1LL};
    while(times) {
        if(times%2) {
            ans=f.mult(ans, orig);
        }
        times/=2;
        orig=f.mult(orig, orig);
        trav(x, orig) {
            x=min(x, 1LL);
        }
        trav(x, ans) {
            x=min(x, 1LL);
        }
        cout << times << endl;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vt<int> v(n);
    F0R(i, n) cin >> v[i];
    vt<int> bruh(1001);
    trav(x, v) bruh[x]++;
    F0R(i, 1001) bruh[i]=min(bruh[i], 1LL);
    auto x = bexpo(bruh, k);
    // cout << x << endl;
    F0R(i, x.size()) {
        if(x[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}