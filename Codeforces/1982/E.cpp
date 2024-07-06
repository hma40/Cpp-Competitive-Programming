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
// #define endl "\n"
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
int binExp(int base, int expo) {
    int ans = 1;
    while(expo) {
        if(expo%2) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        expo/=2;
    }
    return ans;
}

vt<int> fact,invFact;
int nck(int n, int k) {
    return fact[n]*invFact[k]%mod*invFact[n-k]%mod;
}
vt<vt<int>> dp(62, vt<int>(62)), beg(62, vt<int>(62)), ed(62, vt<int>(62));
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
        // freopen("file.out", "w", stdout);
    fact.resize(100);
    invFact.resize(100);
    fact[0]=invFact[0]=1;
    FOR(i, 1, 100) {
        fact[i]=fact[i-1]*i;
        invFact[i]=binExp(fact[i], mod-2);
    }
    F0R(i, 61) dp[0][i]=beg[0][i]=ed[0][i]=1;
    FOR(bits, 1, 61) {
        beg[bits][0]=1;
        ed[bits][0]=0;
        dp[bits][0]=1;
        FOR(k, 1, 61) {
            if(k>=bits) {
                int nums = (1LL<<bits)%mod;
                beg[bits][k]=ed[bits][k]=nums;
                dp[bits][k]=(nums*(nums+1))%mod * 500000004 % mod;
                assert(0<=dp[bits][k]&&dp[bits][k]<mod);
            } else {
                ed[bits][k]=0;
                beg[bits][k]=((1LL<<(k+1))-1)%mod;
                dp[bits][k]+=dp[bits-1][k];
                dp[bits][k]-=ed[bits-1][k]*(ed[bits-1][k]+1) % mod * 500000004 % mod;
                dp[bits][k]%=mod;
                dp[bits][k]+=mod;
                dp[bits][k]%=mod;
                dp[bits][k]+=dp[bits-1][k-1];
                dp[bits][k]-=beg[bits-1][k-1]*(beg[bits-1][k-1]+1)% mod * 500000004 % mod;
                dp[bits][k]%=mod;
                dp[bits][k]+=mod;
                dp[bits][k]%=mod;
                dp[bits][k]+=(ed[bits-1][k]+beg[bits-1][k-1])*(ed[bits-1][k]+beg[bits-1][k-1]+1) % mod * 500000004 % mod;
                dp[bits][k]%=mod;
                dp[bits][k]+=mod;
                dp[bits][k]%=mod;
            }
        }
    }
    // int u;
    // cin >> u;
    // while(u--) {
    //     int x,y;
    //     cin >> x >> y;
    //     cout << dp[x][y] << " " << beg[x][y] << " " << ed[x][y] << endl;
    // }
    // cout << dp << endl << beg << endl << ed << endl;
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        // n--;
        // if(n==0) {
        //     cout << 1 << endl;
        //     continue;
        // }
        int ans = 0;
        int edbefore = -1;
        R0F(i, 61) {
            if(n&(1LL<<i)) {     
                cout << i << " " << k << " " << ans << " " << edbefore << " " << ed[i][k] << endl;
                if(edbefore!=-1) {
                    ans+=dp[i][k];
                    ans-=beg[i][k]*(beg[i][k]+1) % mod * 500000004 % mod;
                    ans%=mod;
                    ans+=mod;
                    ans%=mod;
                    ans-=edbefore * (edbefore+1) % mod * 500000004 % mod;
                    ans%=mod;
                    ans+=mod;
                    ans%=mod;
                    ans+=(edbefore+beg[i][k]) * (edbefore+beg[i][k]+1) % mod * 500000004 % mod;
                    ans%=mod;
                    ans+=mod;
                    ans%=mod;
                } else {
                    ans+=dp[i][k]; 
                    ans%=mod;
                }
                edbefore = ed[i][k];
                k--;
                if(k<0) break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
/*
10100111001
*/
/*
0 1 10
*/