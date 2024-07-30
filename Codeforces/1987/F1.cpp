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
// #define int long long
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
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        F0R(i, n) v[i]--;
        vt<vt<int>> dp(n, vt<int>(n, 1e9));//min moves to delete
        vt<vt<int>> dp2(n, vt<int>(n, 1e9));//min elements remain
        F0R(i, n) {
            FOR(j, i, n) {
                dp2[i][j]=j-i+1;
            }
        }
        for(int end = 1; end < n; end++) {
            for(int beg = end-1; beg >= 0; beg--) {
                bool poss = true;
                poss&=(end%2)!=(beg%2);
                poss&=(beg>=v[beg]);
                poss&=(beg%2)==(v[beg]%2);
                // cout << beg << " " << end << " " << poss << endl;
                if(beg!=0) {
                    poss&=(dp2[0][beg-1]<=v[beg]);
                }
                if(end!=beg+1) {
                    poss&=v[beg]<v[beg+1];
                    int moves = (beg-v[beg])/2;
                    poss&=dp[beg+1][end-1]!=1e9;
                    poss&=dp[beg+1][end-1]<=moves;
                }
                if(poss) {
                    dp[beg][end]=(beg-v[beg])/2;
                    dp2[beg][end]=0;
                    continue;
                }
                // dp[beg][end]=poss;
                dp2[beg][end]=dp2[beg+1][end]+1;
                // cout << beg << " " << end << " " << dp2[beg][end] << endl;
                for(int mid = beg+1; mid < end; mid++) {
                    if(dp[beg][mid]!=1e9) {
                        dp2[beg][end]=min(dp2[beg][end], dp2[mid+1][end]);
                        if(dp2[mid+1][end]==0) {
                            dp[beg][end]=min(dp[beg][end], max(dp[beg][mid], dp[mid+1][end]-(mid-beg+1)/2));
                        }
                    }
                }
                // if(dp[beg][end]) dp2[beg][end]=0;
            }
        }
        // F0R(i, n) {
        //     F0R(j, n) {
        //         if(dp[i][j]!=1e9) {
        //             // cout << i << " " << j << " " << dp[i][j] << endl;
        //         }
        //     }
        // }
        // cout << dp2 << endl;
        cout << (n-dp2[0][n-1])/2 << endl;
    }
    return 0;
}
/*

1
8
1 2 2 2 4 7 8 3
*/
/*
1
8
2 1 3 4 5 6 7 8
*/