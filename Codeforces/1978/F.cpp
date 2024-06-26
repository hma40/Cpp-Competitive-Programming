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
int MAXN = 1e6+50;
struct DSU {
    int n;
    vt<int> par,size;
    DSU(int n): n(n) {
        par.resize(n, -1);
        size.resize(n, 1);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x==y) return;
        if(size[x]>size[y]) {
            size[x]+=size[y];
            par[y]=x;
        } else {
            size[y]+=size[x];
            par[x]=y;
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    vt<int> primes;
    vt<bool> isPrime(MAXN, true);
    vt<vt<int>> primeFactors(MAXN);
    FOR(i, 2, MAXN) {
        if(isPrime[i]) {
            isPrime[i]=false;
            primes.add(i);
            for(int j = i; j < MAXN; j+=i) {
                isPrime[j]=false;
                primeFactors[j].add(i);
            }
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> b;
        R0F(i, n) b.add(a[i]);
        ROF(i, 1, n) b.add(a[i]);
        // cout << b << endl;
        map<int, vt<int>> mp;
        F0R(i, b.size()) {
            int x = b[i];
            trav(y, primeFactors[x]) {
                mp[y].add(i);
            }
        }
        DSU d(b.size());
        trav(x, mp) {
            FOR(i, 1, x.s.size()) {
                if(x.s[i]-x.s[i-1]<=k) {
                    d.unite(x.s[i], x.s[i-1]);
                }
            }
        }
        int ans = 0;
        F0R(i, b.size()) {
            if(d.find(i)==i) {
                ans++;
            }
        }
        int sz = 0;
        F0R(i, b.size()) {
            if(i>b.size()/2) {
                sz--;
            } else {
                sz++;
            }
            // cout << i << " " << sz << endl;
            if(b[i]==1) {
                ans+=sz-1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}