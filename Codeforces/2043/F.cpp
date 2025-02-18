#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
#define double long double
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e=mod-2) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        b=b*b%mod;
        e>>=1;
    }
    return ans;
}
vt<int> fact(100005), invfact(100005);
int nck(int n, int k) {
    if(n<k) return 0;
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    fact[0]=invfact[0]=1;
    FOR(i, 1, 100005) {
        fact[i]=fact[i-1]*i%mod;
        invfact[i]=bexpo(fact[i]);
    }
    int n,q;
    cin >> n >> q;
    vector<vector<int>> pref(n+1, vector<int>(51));
    F0R(i, n) {
        int x;
        cin >> x;
        F0R(j, 51) {
            pref[i+1][j]+=pref[i][j];
        }
        pref[i+1][x]++;
    }
    vt<int> cnt(51);
    F0R(iq, q) {
        int l,r;
        cin >> l >> r;
        F0R(i, 51) cnt[i]=pref[r][i]-pref[l-1][i];
        if(cnt[0]!=0) {
            cout << r-l << " " << cnt[0] << endl;
            continue;
        } 
        bool two = false;
        F0R(i, 51) {
            if(cnt[i]>1) {
                two=true;
            }
        }
        if(two) {
            int ans = 0;
            F0R(i, 51) {
                ans+=nck(cnt[i],2);
                ans%=mod;
            }
            cout << r-l-1 << " " << ans << endl;
            continue;
        }
        int xr = 0;
        F0R(i, 51) if(cnt[i]) xr^=i;
        vt<vt<array<int,2>>> dp(51, vt<array<int,2>>(64, {-inf,-1})), dp2(52, vt<array<int,2>>(64, {-inf,-1}));//dp[i][j] = {max elements we can remove, number of ways
        dp[0][0][0]=0;
        dp[0][0][1]=1;
        FOR(i, 1, 51) {
            if(cnt[i]==0) {
                F0R(j, 64) dp[i][j]=dp[i-1][j];
                continue;
            } 
            F0R(j, 64) dp[i][j]=dp[i-1][j]; //don't remove a[i]
            F0R(j, 64) {
                int without = j^i;
                if(dp[i-1][without][0]+1>dp[i][j][0]) {
                    dp[i][j][0]=dp[i-1][without][0]+1;
                    dp[i][j][1]=dp[i-1][without][1];
                } else if(dp[i-1][without][0]+1==dp[i][j][0]) {
                    dp[i][j][1]+=dp[i-1][without][1];
                    dp[i][j][1]%=mod;
                }
            }
        }
        dp2[51][0][0]=0;
        dp2[51][0][1]=1;
        ROF(i, 1, 51) {
            if(cnt[i]==0) {
                F0R(j, 64) dp2[i][j]=dp2[i+1][j];
                continue;
            } 
            F0R(j, 64) dp2[i][j]=dp2[i+1][j]; //don't remove a[i]
            F0R(j, 64) {
                int without = j^i;
                if(dp2[i+1][without][0]+1>dp2[i][j][0]) {
                    dp2[i][j][0]=dp2[i+1][without][0]+1;
                    dp2[i][j][1]=dp2[i+1][without][1];
                } else if(dp2[i+1][without][0]+1==dp2[i][j][0]) {
                    dp2[i][j][1]+=dp2[i+1][without][1];
                    dp2[i][j][1]%=mod;
                }
            }
        }
        // cout << dp << endl;
        pair<int,int> ans = {-inf,-1};
        FOR(i, 1, 51) {
            if(cnt[i]==0) continue;
            FOR(xrbef, 0, 64) {
                int other = xr^xrbef;
                if(dp[i-1][xrbef][0]+dp2[i+1][other][0]>ans.f) {
                    // cout << i << " " << xrbef << " " << other << endl;
                    // cout << dp[i-1][xrbef][0] << " " << dp2[i+1][other][0] << endl;
                    ans.f=dp[i-1][xrbef][0]+dp2[i+1][other][0];
                    ans.s=dp[i-1][xrbef][1]*dp2[i+1][other][1];
                    ans.s%=mod;
                } else if(dp[i-1][xrbef][0]+dp2[i+1][other][0]==ans.f) {
                    // cout << "LINE 251 " << end/l;
                    // cout << dp[i-1][xrbef][]
                    ans.s+=dp[i-1][xrbef][1]*dp2[i+1][other][1];
                    ans.s%=mod;
                }
            }
            // cout << i << " " << ans.s << endl;
        }
        // cout << ans.s << endl;
        //each is counted (however many elements left) times
        int left = r-l+1-ans.f;
        ans.s*=bexpo(left);
        ans.s%=mod;
        if(ans.f<0) cout << -1 << endl;
        else cout << ans.f << " " << ans.s << endl;
    }
    return 0;
}
/*
10 1
6 5 3 8 2 4 1 8 5 3 
5 10

6 1
2 4 1 8 5 3
1 6



4 1 5 (2 3 8)
2 1 3 (4 5 8)
*/