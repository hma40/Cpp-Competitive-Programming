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
int bexpo(int b, int e) {
    int a = 1;
    while(e) {
        if(e%2) {
            a*=b;
            a%=mod;
        }
        b*=b;
        b%=mod;
        e/=2;
    }
    return a;
}
int inv(int x) {
    return bexpo(x, mod-2);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        int normals = n-k;
        int ssum = 0;
        int nsum = 0;
        F0R(i, n) {
            int x;cin >> x;
            if(i<k) ssum+=x;
            else nsum+=x;
        }
        ssum%=mod;
        nsum%=mod;
        // cout << ssum << " " << nsum << endl;
        int alice = 0;
        if(normals%2==0) {
            alice+=nsum * inv(2) % mod;
            int parts = normals+1;
            int parts2 = normals/2+1;
            alice+=ssum * parts2 % mod * inv(parts) % mod;
            alice%=mod;
        } else {
            int parts = normals/2+1;
            alice+=nsum * parts%mod * inv(normals)%mod;
            alice+=ssum * inv(2) % mod;
            alice%=mod;
        }
        int b = (nsum+ssum+mod-alice)%mod;
        cout << alice << " " << b << endl;
        //75 * 2/3 * 3/5 + 75 * 1/2 * 2/5
    }
    return 0;
}
/*
1
3 1
1 1 1
*/
/*
3(2/3*1/2 + 1/3*2/3)
2 * 3 + 2 * 1 * 2 = 10
3 * 10 / 3 / 3 / 2
3(2*1+1*3)/(3*3*2)
1.5 * 2/3 + 3 * 2/3 * 1/3 = 5/3
Claim: 2 is 1/2(2)+1/2(1)=1.5
2/3 chance of 2, 1/3 chance of 3
123: 2
213: 1
132: 2
312: 1
Claim: 3 is 2/3(3)=2
321: 2
231: 2
10/6
*/
