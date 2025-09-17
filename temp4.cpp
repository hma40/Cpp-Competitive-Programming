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
const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<int> perm(1005), iperm(1005);
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        b=b*b%mod;
        e>>=1;
    }
    return ans;
}
int nck(int n, int k ){
    return perm[n]*iperm[k]%mod*iperm[n-k]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // cout << 3 << endl;
    // return 0;
    perm[0]=iperm[0]=1;
    FOR(i, 1, 1005) {
        perm[i]=perm[i-1]*i%mod;
        iperm[i]=bexpo(perm[i], mod-2);
    }
    int n;
    cin >> n;
    bool ok = true;
    vt<int> a(n);
    F0R(i, n) cin >> a[i];
    int zc = 0;
    F0R(i, n) {
        if(a[i]>n-1) zc+=2;
        if(a[i]==0) zc++;
        if(a[i]!=i) ok=false;
    }
    if(zc!=1) {
        cout << 0 << endl;
        return 0;
    }
    vt<vt<int>> dp(n, vt<int>(n));
    F0R(i, n) {
        bool left = (i!=0 && a[i-1]+1==a[i]);
        bool right = (i!=n-1 && a[i+1]+1==a[i]);
        dp[i][i]=left+right;
    }
    F0R(l, n) {
        F0R(r, l) {
            dp[l][r]=1;
        }
    }
    auto GET_DP = [&](int l, int r)->int{
        if(l>r) return 1;
        else return dp[l][r];
    };
    FOR(diff, 1, n) {
        FOR(left, 0, n-diff) {
            int right = left+diff;

            int l = -inf;
            if(left!=0) l=a[left-1];
            int r = -inf;
            if(right!=n-1) r=a[right+1];
            // cout << left << " " << right << " " << l << " " << r << endl;
            FOR(i, left, right+1) {
                if(a[i]==l+1) {
                    // cout << left << " " << right << " " << i << endl;
                    dp[left][right]+=nck(right-left, i-left)*GET_DP(left, i-1)%mod*GET_DP(i+1, right)%mod;
                    dp[left][right]%=mod;
                }
                if(a[i]==r+1) {
                    dp[left][right]+=nck(right-left, i-left)*GET_DP(left, i-1)%mod*GET_DP(i+1, right)%mod;
                    dp[left][right]%=mod;
                }
            }
            assert(dp[left][right]>=0 && dp[left][right]<mod);
        }
    }
    // assert(false);
    // cout << dp << endl;
    // cout << mod << endl;
    F0R(i, n) {
        if(a[i]==0) {
            int ans = nck(n-1, i)*GET_DP(0, i-1)%mod*GET_DP(i+1, n-1)%mod;
            assert(0<=ans && ans<mod);
            cout << ans << endl;
        }
    }
    return 0;
    // cout << "LINE 131" << endl;
    // auto solve = [&](int l, int r, int left, int right, auto self)->int{
    //     if(l>r) return 1;
    //     int ans = 0;
    //     FOR(i, l, r+1) {
    //         if(a[i]==left+1) {
    //             ans+=nck(r-l, i-l)*self(l, i-1, left, left+1, self)%mod*self(i+1, r, left+1, right, self);
    //             ans%=mod;
    //         }
    //     }
    //     FOR(i, l, r+1) {
    //         if(a[i]==right+1) {
    //             ans+=nck(r-l, i-l)*self(l, i-1, left, right+1, self)%mod*self(i+1, r, right+1, right, self);
    //             ans%=mod;
    //         }
    //     }
    //     return ans;
    // };
    // auto left = [&](int l, int r, int out, auto self)->int{
    //     if(l>r) return 1;    
    //     // cout << "GOT HERE " << l << " " << r << endl;
    //     int ans = 0;
    //     FOR(i, l, r+1) {
    //         if(a[i]==out+1) {
    //             ans+=nck(r-l, i-l)*self(l, i-1, out+1, self)%mod*solve(i+1, r, out+1, out, solve);
    //             ans%=mod;
    //         }
    //     }
    //     return ans;
    // };
    // auto right = [&](int l, int r, int out, auto self)->int{
    //     if(l>r) return 1;
    //     int ans = 0;
    //     FOR(i, l, r+1) {
    //         if(a[i]==out+1) {
    //             ans+=nck(r-l, i-l)*self(i+1, r, out+1, self)%mod*solve(l, i-1, out, out+1, solve);
    //             ans%=mod;
    //         }
    //     }
    //     return ans;
    // };

    // F0R(i, n) {
    //     if(a[i]==0) {
    //         cout << nck(n-1, i)*left(0, i-1, 0, left)%mod*right(i+1, n-1, 0, right)%mod << endl;
    //     }
    // }
    return 0;
}
/*
1 2 1 0
0 -> 1 0 -> 1 1 0 -> 1 2 1 0
0 -> 1 0 -> 1 1 0 -> 1 2 1 0
*/