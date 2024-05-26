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
ll mod = 1000000007;
ll inf = 1e15;
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
    F0R(bruh, t) {
        int n,k;
        cin >> n >> k;
        vector<int> v(n);
        F0R(i, n) cin >> v[i];
        //dp[a][b][c]: minSum for first a elements, assuming b operations used and v[a]=v[a+c-10]
        vector<vector<int>> dp(k+1, vector<int>(21, inf));
        dp[0][10]=v[0];
        if(k>=1) {
            FOR(i, 11, 21) {
                if(i-10<n) {
                    dp[1][i]=v[i-10];
                }
            }
        }
        FOR(i, 1, n) {
            vector<vector<int>> here(k+1, vector<int>(21, inf));
            F0R(j, k+1) {
                F0R(x, 21) {
                    // cout << i << " " << j << " " << x << endl;
                    int arrayIndex = i+x-10;
                    if(arrayIndex<0||arrayIndex>=n) {
                        here[j][x]=inf;
                        continue;
                    }
                    if(j==0) {
                        if(x==10) {
                            here[j][x]=dp[j][x]+v[i];
                            continue;
                        } else {
                            here[j][x]=inf;
                            continue;
                        }
                    }
                    if(x<10) {
                        here[j][x]=dp[j-1][x+1]+v[arrayIndex];
                    } else if(x==10) {
                        F0R(y, 12) {
                            here[j][x]=min(dp[j][y]+v[i], here[j][x]);
                        }
                    } else {
                        if(x!=20) {
                            here[j][x]=dp[j-1][x+1]+v[arrayIndex];
                        }
                        F0R(y, 11) {
                            here[j][x]=min(dp[j-1][y]+v[arrayIndex], here[j][x]);
                        }
                    }
                }
            }
            swap(here, dp);
        }

        int ans = inf;
        F0R(i, k+1) {
            F0R(j, 21) {
                ans=min(ans, dp[i][j]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}