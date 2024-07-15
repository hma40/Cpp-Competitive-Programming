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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n+1),b(n+1),c(n+1);
        F0R(i, n) cin >> a[i+1];
        F0R(i, n) cin >> b[i+1];
        F0R(i, n) cin >> c[i+1];
        F0R(i, n) {
            a[i+1]+=a[i];
            b[i+1]+=b[i];
            c[i+1]+=c[i];
        }
        int ceildiv = (a.back()+2)/3;
        a.add(inf);
        a.add(2*inf);
        a.add(3*inf);
        b.add(inf);
        b.add(2*inf);
        b.add(3*inf);
        c.add(inf);
        c.add(2*inf);
        c.add(3*inf);
        a.add(4*inf);
        b.add(4*inf);
        c.add(4*inf);
        // cout << a << b << c << endl;

        //abc
        int mina = lower_bound(begin(a),end(a),ceildiv)-begin(a);
        int lookfor = b[mina];
        int minb = lower_bound(begin(b),end(b),ceildiv+lookfor)-begin(b);
        lookfor = c[minb];
        int minc = lower_bound(begin(c),end(c),ceildiv+lookfor)-begin(c);
        if(a[minc]<inf) {
            cout << 1 << " " << mina << " " << mina+1 << " " << minb << " " << minb+1 << " " << minc << endl;
            continue;
        }
        mina = lower_bound(begin(a),end(a),ceildiv)-begin(a);
        lookfor = c[mina];
        minb = lower_bound(begin(c),end(c),ceildiv+lookfor)-begin(c);
        lookfor = b[minb];
        minc = lower_bound(begin(b),end(b),ceildiv+lookfor)-begin(b);
        if(a[minc]<inf) {
            cout << 1 << " " << mina << " " << minb+1 << " " << minc << " " << mina+1 << " " << minb << endl;
            continue;
        }
        mina = lower_bound(begin(b),end(b),ceildiv)-begin(b);
        lookfor = a[mina];
        minb = lower_bound(begin(a),end(a),ceildiv+lookfor)-begin(a);
        lookfor = c[minb];
        minc = lower_bound(begin(c),end(c),ceildiv+lookfor)-begin(c);
        if(a[minc]<inf) {
            cout << mina+1 << " " << minb << " " << 1 << " " << mina << " " << minb+1 << " " << minc << endl;
            continue;
        }
        mina = lower_bound(begin(b),end(b),ceildiv)-begin(b);
        lookfor = c[mina];
        minb = lower_bound(begin(c),end(c),ceildiv+lookfor)-begin(c);
        lookfor = a[minb];
        minc = lower_bound(begin(a),end(a),ceildiv+lookfor)-begin(a);
        if(a[minc]<inf) {
            cout << minb+1 << " " << minc << " " << 1 << " " << mina << " " << mina+1 << " " << minb << endl;
            continue;
        }
        mina = lower_bound(begin(c),end(c),ceildiv)-begin(c);
        lookfor = b[mina];
        minb = lower_bound(begin(b),end(b),ceildiv+lookfor)-begin(b);
        lookfor = a[minb];
        minc = lower_bound(begin(a),end(a),ceildiv+lookfor)-begin(a);
        if(a[minc]<inf) {
            cout << minb+1 << " " << minc << " " << mina+1 << " " << minb << " " << 1 << " " << mina << endl;
            continue;
        }
        mina = lower_bound(begin(c),end(c),ceildiv)-begin(c);
        lookfor = a[mina];
        minb = lower_bound(begin(a),end(a),ceildiv+lookfor)-begin(a);
        lookfor = b[minb];
        minc = lower_bound(begin(b),end(b),ceildiv+lookfor)-begin(b);
        if(a[minc]<inf) {
            cout << mina+1 << " " << minb << " " << minb+1 << " " << minc << " " << 1 << " " << mina << endl;
            continue;
        }
        cout << -1 << endl;
        
    }
    return 0;  
}