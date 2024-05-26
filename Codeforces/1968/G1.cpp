#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
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
// ll mod = 1000000007;
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
int MAXN = 2e5+50;
__int128_t MOD = (1LL<<61)-1;
__int128_t pol;
vt<__int128_t> powPol(MAXN);
struct Hash {
    vt<__int128_t> pow;
    Hash(string s) {
        pow.resize(s.size()+1);
        pow[0]=0;
        F0R(i, s.size()) {
            pow[i+1]=(pow[i]*pol+s[i])%MOD;
        }
    }
    int getHash(int start, int end) {
        __int128_t raw = pow[end+1]-pow[start]*powPol[end-start+1];
        return (raw%MOD+MOD)%MOD;
    }
};
bool poss(Hash &h, string &s, int x, int test) {
    vt<int> dp(s.size()+1);
    R0F(i, s.size()-test+1) {
        dp[i]=dp[i+1];
        if(h.getHash(0,test-1)==h.getHash(i, i+test-1)) {
            dp[i]=max(dp[i], dp[i+test]+1);
        }
    }
    return dp[0]>=x;
}
signed main() {
    srand(time(NULL));
    pol=rand()%MOD;
    powPol[0]=1;
    FOR(i, 1, MAXN) {
        powPol[i]=powPol[i-1]*pol%MOD;
    }
    // cout << rand() << " " << rand() << endl;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,l,r;
        cin >> n >> l >> r;
        string s;
        cin >> s;
        Hash h(s);
        int lo = 0, hi = n;
        while(lo<hi) {
            int mid = (1+lo+hi)/2;
            if(!poss(h, s, l, mid)) {
                hi=mid-1;
            } else {
                lo=mid;
            }
        }
        cout << lo << endl;
    }
    return 0;
}