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
ll mod = 998244353;
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
int binExp(int base, int exp) {
    int ans = 1;
    while(exp) {
        if(exp%2) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        exp/=2;
    }
    return ans;
}
int MAXN = 2e5+50;
vt<int> fact(MAXN);
vt<int> invFact(MAXN);
int choose(int x, int y) {
    return fact[x]*invFact[y]%mod*invFact[x-y]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fact[0]=invFact[0]=1;
    FOR(i, 1, MAXN) {
        fact[i]=fact[i-1]*i;
        fact[i]%=mod;
        invFact[i]=binExp(fact[i], mod-2);
    }
    int m,n;
    string a,b;
    cin >> n >> m >> a >> b;
    vt<int> aC(26), bC(26);
    F0R(i, n) aC[a[i]-'A']++;
    F0R(i, m) bC[b[i]-'A']++;
    if(bC[25]<aC[25]) {
        cout << 0 << endl;
        return 0;
    }
    vt<vt<int>> dp(26, vt<int>(m+1));
    dp[25][bC[25]-aC[25]]=1;
    R0F(i, m) {
        dp[25][i]+=dp[25][i+1];
        dp[25][i]%=mod;
    }
    // cout << aC << " " << bC << endl;
    R0F(i, 25) {
        // cout << i << " " << bC[i] << endl;
        F0R(remain, bC[i]+1) {
            int used = bC[i]-remain;
            int need = aC[i];
            int borrow = need-used;
            // cout << i << " " << remain << " " << used << " " << need << " " << borrow << endl;
            if(borrow<0) continue;
            dp[i][remain]+=dp[i+1][borrow]*choose(need, used);
            dp[i][remain]%=mod;
        }
        R0F(j, m) {
            dp[i][j]+=dp[i][j+1];
            dp[i][j]%=mod;
        }
        // char c = 'A'+i;
        // cout << c << " " << dp[i] << endl;
    }
    int ans = dp[0][0];
    ans*=fact[n];
    ans%=mod;
    F0R(i, 26) {
        ans*=invFact[aC[i]];
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}
/*
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int m,n;
    string a,b;
    cin >> m >> n >> a >> b;
    vt<int> aC(26), bC(26);
    F0R(i, m) aC[a[i]-'A']++;
    F0R(i, n) bC[a[i]-'B']++;
    if(bC[25]<aC[25]) {
        cout << 0 << endl;
        return 0;
    }
    vt<vt<int>> dp(26, vt<int>(n+1));
    dp[25][bC[25]-aC[25]]=1;
    R0F(i, m) {
        dp[25][i]+=dp[25][i+1];
    }
    R0F(i, 25) {
        F0R(remain, bC[i]+1) {
            int used = bC[i]-remain;
            int need = aC[i];
            int borrow = need-used;
            if(borrow<0) continue;
            dp[i][remain]+=
        }
    }
    return 0;
*/