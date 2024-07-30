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
int n,q;
vt<int> v;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
bool solve(int l, int r) {
    vt<int> here;
    FOR(i, l, r+1) {
        here.add(v[i]);
    }
    sort(begin(here),end(here));
    int sz = here.size();
    vt<int> her(3),notHer(3);
    //6 in a row
    FOR(end, 6, sz+1) {
        F0R(bruh, 64) {
            if(__builtin_popcount(bruh)!=3) continue;
            int nx = 0, nx2 = 0;
            R0F(i, 6) {
                if(bruh&(1<<i)) her[nx++]=here[end-1-i];
                else notHer[nx2++]=(here[end-1-i]);
            }
            if(her[0]+her[1]>her[2]&&notHer[0]+notHer[1]>notHer[2]) return true;
        }
    }
    FOR(end, 5, sz) {
        FOR(begin, 2, end-2) {
            // vt<int> her,notHer;
            her[0]=here[begin-2];
            her[1]=here[begin-1];
            her[2]=here[begin];
            notHer[0]=here[end-2];
            notHer[1]=here[end-1];
            notHer[2]=here[end];
            if(her[0]+her[1]>her[2]&&notHer[0]+notHer[1]>notHer[2]) return true;
        }
    }
    return false;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // int n,q;
    cin >> n >> q;
    // vt<int> v(n);
    v.assign(n,0);
    F0R(i, n) cin >> v[i];
    while(q--) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        if(b-a>48) {
            cout << "YES" << endl;
        } else if(solve(a,b)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}