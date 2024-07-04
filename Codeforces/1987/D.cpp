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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> count(n+1);
        F0R(i, n) {
            int x;
            cin >> x;
            count[x]++;
        }
        // vt<vt<int>> dp(n, vt<int>(n));
        vt<bool> canStop(n);
        F0R(i, n+1) {
            if(count[i]!=0) {
                int prev = i;
                for(int j = i-1; j >= 0; j--) {
                    if(count[j]==0) {
                        count[j]=count[prev];
                        count[prev]=0;
                        prev=j;
                    }
                }
            }
            // cout << i << " " << count << endl;
        }
        while(count.back()==0) count.pop_back();
        // cout << count << endl;
        vt<vt<int>> dp(count.size(), vt<int>(2+count.size(), inf));
        //dp[i][j]: min moves for Bob to guarantee Alice has j points for 0-i
        dp[0][1]=0;
        FOR(i, 1, count.size()) {
            FOR(j, 1, i+2) {
                //case 1: Bob does not coccblock i
                dp[i][j]=dp[i-1][j-1];
                //case 2: coccblocked
                int moves = dp[i-1][j];
                moves+=count[i];
                //how long alice takes to get here
                int aliceMoves = j;

                if(aliceMoves<moves) {
                    moves=inf;
                }
                dp[i][j]=min(dp[i][j], moves);
                // cout << i << " " << j << " " << moves << " " << aliceMoves << " " << dp[i][j] << endl;
            }
        }
        int ans = inf;
        // cout << dp << endl;
        F0R(i, count.size()+2) {
            if(dp.back()[i]<inf) {
                ans=min(ans, i);
            }
        }
        cout << ans << endl;
    }
    return 0;
}