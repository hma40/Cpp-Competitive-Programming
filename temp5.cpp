// #include <bits/stdc++.h>
// using namespace std;
// std::string to_string(__int128_t value) {
//     if (value == 0) return "0";
    
//     std::string result;
//     bool negative = (value < 0);
//     if (negative) value = -value;
    
//     while (value > 0) {
//         result += '0' + (value % 10);
//         value /= 10;
//     }
    
//     if (negative) result += '-';
    
//     std::reverse(result.begin(), result.end());
//     return result;
// }

// // Overload << operator for __int128
// std::ostream& operator<<(std::ostream& os, __int128_t value) {
//     return os << to_string(value);
// }
// template<typename T1, typename T2>
// std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
//     os << "(" << p.first << ", " << p.second << ")";
//     return os;
// }
// template <typename T, typename = void>
// struct is_iterable : std::false_type {};

// template <typename T>
// struct is_iterable<T, std::void_t<
//     decltype(std::begin(std::declval<T>())),
//     decltype(std::end(std::declval<T>()))
// >> : std::true_type {};

// // Generic container printer (vector, set, deque, array, map, etc.)
// template <typename T>
// typename std::enable_if<is_iterable<T>::value, ostream&>::type
// operator<<(ostream& os, const T& container) {
//     os << "{ ";
//     for (auto it = std::begin(container); it != std::end(container); ++it) {
//         os << *it;
//         if (std::next(it) != std::end(container)) os << ", ";
//     }
//     os << " }";
//     return os;
// }

// // Queue-like adapters (stack, queue, priority_queue)
// template <typename T>
// ostream& operator<<(ostream& os, queue<T> q) {
//     os << "{ ";
//     while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
//     os << " }";
//     return os;
// }

// template <typename T>
// ostream& operator<<(ostream& os, stack<T> st) {
//     os << "{ ";
//     while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
//     os << " }";
//     return os;
// }

// template <typename T>
// ostream& operator<<(ostream& os, priority_queue<T> pq) {
//     os << "{ ";
//     while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
//     os << " }";
//     return os;
// }

// // using namespace std;
// using ll = long long;
// #define add push_back 
// #define FOR(i,a,b) for (int i = (a); i < (b); ++i)
// #define F0R(i,a) FOR(i,0,a)
// #define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
// #define R0F(i,a) ROF(i,0,a)
// #define f first
// #define s second
// #define trav(a,x) for (auto& a: x)
// #define int long long
// #define vt vector
// #define endl "\n"
// #define enld "\n"
// #define double long double
// const ll mod = 998244353;
// ll inf = 1e18;
// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// int bexpo(int b, int e) {
//     int ans = 1;
//     while(e) {
//         if(e&1) ans=ans*b%mod;
//         e>>=1;
//         b=b*b%mod;
//     }
//     return ans;
// }
// signed main() {
//     ios_base::sync_with_stdio(false); 
//     cin.tie(0);
//     // freopen("input.txt" , "r" , stdin);
//     // freopen("output.txt" , "w", stdout);
//     vt<int> f(1005), ivf(1005);
//     f[0]=ivf[0]=1;
//     FOR(i, 1, 1005) {
//         f[i]=f[i-1]*i%mod;
//         ivf[i]=bexpo(f[i], mod-2);
//     }
//     auto nck = [&](int n, int k)->int{
//         if(k<0 || k>n) return 0;
//         return f[n]*ivf[k]%mod*ivf[n-k]%mod;
//     };
//     int t;
//     cin >> t;
//     while(t--) {
//         int n;
//         cin >> n;
//         vt<vt<int>> adj(n);
//         F0R(i, n-1) {
//             int u,v;
//             cin >> u >> v;
//             u--;
//             v--;
//             adj[u].add(v);
//             adj[v].add(u);
//         }
//         vt<vt<int>> dp(n, vt<int>(n+1)), dp2(n, vt<int>(n+1));
//         auto dfs = [&](auto self, int node, int par)->void{
//             trav(x, adj[node]) if(x!=par) self(self, x, node);
//             dp[node][1]=1;
//             dp2[node][0]=1;
//             auto old = dp2[node];
//             trav(x, adj[node]) {
//                 if(x==par) continue;               
//                 dp2[node].assign(n+1, 0);

//                 F0R(i, n) F0R(j, n) {
//                     if(i+j>n) continue;
//                     dp2[node][i+j]+=(dp2[x][i]+dp[x][i])*(old[j])%mod*nck(i+j, i);
//                     dp2[node][i+j]%=mod;
//                 }
//                 old = dp2[node];
//             }
//             old = dp[node];
//             trav(x, adj[node]) {
//                 if(x==par) continue;        
//                 dp[node].assign(n+1, 0);

//                 F0R(i, n) F0R(j, n) {
//                     if(i+j>n) continue;
//                     dp[node][i+j]+=(dp2[x][i]+dp[x][i])*old[j]%mod*nck(i+j-1, i);
//                     dp[node][i+j]%=mod;
//                 }
//                 old = dp[node];
//             }

//             // cout << node << dp2 << endl;
//         };
//         dfs(dfs, 0, -1);
//         cout << dp << endl << dp2 << endl;
//         // cout << dp[0] << endl;
//     }
//     return 0;
// }
// /*
// dp[node][amt][disabled]

// */

#include <bits/stdc++.h>
using namespace std;
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
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> f(1005), ivf(1005);
    f[0]=ivf[0]=1;
    FOR(i, 1, 1005) {
        f[i]=f[i-1]*i%mod;
        ivf[i]=bexpo(f[i], mod-2);
    }
    auto nck = [&](int n, int k)->int{
        if(k<0 || k>n) return 0;
        return f[n]*ivf[k]%mod*ivf[n-k]%mod;
    };
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> adj(n);
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        vt<vt<vt<int>>> dp(n, vt<vt<int>>(n, vt<int>(n+1))), dp2(n, vt<vt<int>>(n, vt<int>(n+1)));
        vt<vt<bool>> anc(n, vt<bool>(n));
        // cout << "LINE 135" << endl;
        auto dfs = [&](auto self, int node, int par) -> void{
            trav(x, adj[node]) if(x==par) continue; else self(self, x, node);
            // cout << node << endl;
            trav(x, adj[node]) {
                if(x==par) continue;
                anc[node][x]=true;
                F0R(i, n) if(anc[x][i]) anc[node][i]=true;
            }
            cout << node << anc[node] << endl;
            F0R(disabled, n) {
                // cout << node << " " << disabled << endl;
                dp2[node][disabled][0]=1;
                dp[node][disabled][1]=1;
                anc[node][node]=true;
                trav(x, adj[node]) {
                    if(x==par) continue;
                    auto old = dp2[node][disabled];
                    dp2[node][disabled].assign(n+1, 0);
                    F0R(i, n) F0R(j, n) {
                        if(i+j>n) continue;
                        dp2[node][disabled][i+j]+=(dp2[x][disabled][j]+dp[x][disabled][j])*old[i]%mod*nck(i+j,i);
                        dp2[node][disabled][i+j]%=mod;
                    }
                }
                trav(x, adj[node]) {
                    if(x==par) continue;
                    auto old = dp[node][disabled];
                    dp[node][disabled].assign(n+1, 0);
                    F0R(i, n) F0R(j, n) {
                        if(i+j>n) continue;

                        dp[node][disabled][i+j]+=(dp2[x][disabled][j]+dp[x][disabled][j])*old[i]%mod*nck(i+j-1, i-1);
                        dp[node][disabled][i+j]%=mod;
                        if(node==1 && disabled==0 && x==2 && i==1 && j==0) {
                            cout << "GOT HERE " << dp[node][disabled] << endl;
                            cout << dp2[x][disabled][j] << " " << dp[x][disabled][j] << " " << old[i] << endl;
                        }
                    }
                }
                if(anc[node][disabled]) {
                    F0R(i, n+1) dp[node][disabled][i]=0;
                }
            }
        };
            // cout << node << dp2 << endl;
        dfs(dfs, 0, -1);
        cout << anc << endl;
        cout << dp << endl << dp2 << endl;

        F0R(i, n) cout << i << " " << dp2[0][i] << endl;
        // cout << dp[0] << endl;
        int ans = 0;
        F0R(i, n) F0R(j, n) {
            if(anc[i][j]) F0R(k, n+1) {
                ans+=dp2[i][j][k]*k;
                ans%=mod;
            }
            else {
                F0R(k, n+1) {
                ans+=dp[i][j][k]*k;
                ans%=mod;
                }
            }
            cout << i << " " << j << " " << ans << endl;
        }
        F0R(i, n) F0R(j, n) {
            cout << i << " " << j << " " << dp[i][j] << " " << dp2[i][j] << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
2 1
3 1
2 3 1
3 2 1
*/