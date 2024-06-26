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
int gcd(int a, int b) {
    if(a<b) return gcd(b,a);
    if(b==0) return a;
    return gcd(b,a%b);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vt<vt<int>> v(n, vt<int>(n));
    F0R(i, n) F0R(j, n) cin >> v[i][j];
    int x = v[0][1];
    FOR(i, 2, n) x=gcd(x,v[0][i]);
    vt<int> a(n);
    a[0]=x;
    FOR(i,1, n) {
        a[i]=v[0][i]/x;
    }
    if(a[1]*a[2]!=v[1][2]) {
        int div = v[1][2]/a[1]/a[2];
        int temp = 0;
        FOR(i, 1, div) {
            if(i*i==div) {
                temp=i;
                break;
            }
        }
        a[0]/=temp;
        FOR(i, 1, n) a[i]*=temp;
    }
    F0R(i, n) cout << a[i] << endl;
    return 0;
}