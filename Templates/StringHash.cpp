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
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(string s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
void initialize() {
    sd = rand()%mod;
    F0R(i, 10000) {
        sd*=rand();
        sd+=rand();
        sd%=mod;
    }
    pw.add(1);
    F0R(i, 200050) {
        pw.add(pw.back()*sd%mod);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    
    return 0;
}