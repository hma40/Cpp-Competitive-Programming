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
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e%2) {
            ans*=b;
            ans%=mod;
        }
        e/=2;
        b*=b;
        b%=mod;
    }
    return ans;
}
int inv(int num) {
    return bexpo(num, mod-2);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m,k;
        cin >> n >> m >> k;
        int iv = inv(bexpo(2, n-1));
        // cout << iv << endl;
        if(n==1) {
            cout << k << endl;
            continue;
        }
        vt<vt<int>> dp(n+1, vt<int>(m+1, -inf));
        dp[n][m]=0;
        R0F(i, n) {
            int pLeft = n-i;
            F0R(j, m+1) {
                int fLeft = m-j;
                if(fLeft>=pLeft) continue;
                if(j>i) continue;
                dp[i][j]=(dp[i+1][j+1]+dp[i+1][j])*inv(2);
                dp[i][j]%=mod;
            }
            if(m-pLeft>=0) {
                dp[i][m-pLeft]=dp[i+1][m-pLeft+1]+k*bexpo(2, n-1);
                dp[i][m-pLeft]%=mod;
            }
            dp[i].back()=0;
        }
        // cout << dp << endl;
        cout << (dp[0][0]*iv)%mod << endl;
    }
    return 0;
}