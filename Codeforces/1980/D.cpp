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
int gcd(int a, int b) {
    if(a>b) swap(a,b);
    if(a==0) return b;
    return gcd(b%a, a);
}
int isSorted(vt<int> v) {
    FOR(i, 1, v.size()) {
        if(v[i]<v[i-1]) {
            return i;
        }
    } 
    return -1;
}
bool test(vt<int> &v, int ignore) {
    int n = v.size();
    if(ignore>=n) return false;
    vt<int> gc(n-2);
    if(ignore==0) {
        FOR(i, 1, n-1) {
            gc[i-1]=gcd(v[i], v[i+1]);
        }
        return isSorted(gc)==-1;
    }
    if(ignore==n-1) {
        F0R(i, n-2) {
            gc[i]=gcd(v[i], v[i+1]);
        }
        return isSorted(gc)==-1;
    }
    int ind = 0;
    F0R(i, ignore-1) {
        gc[ind++]=gcd(v[i], v[i+1]);
    }
    gc[ind++]=gcd(v[ignore-1], v[ignore+1]);
    FOR(i, ignore+1, n-1) {
        gc[ind++]=gcd(v[i], v[i+1]);
    }
    if(isSorted(gc)==-1) return true;
    return false;
} 
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        vt<int> gc(n-1);
        F0R(i, n-1) gc[i]=gcd(v[i], v[i+1]);
        // cout << gc << endl;
        int sort = isSorted(gc);
        // cout << sort << endl;
        bool done = false;
        if(sort==-1) {
            done=true;
        } else {
            if(test(v,sort)) done=true;
            if(test(v,sort-1)) done=true;
            if(test(v,sort+1)) done=true;
            if(test(v,sort+2)) done=true;
        }   
        if(done) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}