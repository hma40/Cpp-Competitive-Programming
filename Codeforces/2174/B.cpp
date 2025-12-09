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
// your original is_iterable (unchanged)
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// detect std::basic_string<...>
template <typename T>
struct is_string : std::false_type {};

template <typename CharT, typename Traits, typename Alloc>
struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type {};

// optionally also detect string_view (C++17)
template <typename CharT, typename Traits>
struct is_string<std::basic_string_view<CharT, Traits>> : std::true_type {};

// now enable the generic container printer only when T is iterable AND not a string
template <typename T>
typename std::enable_if<
    is_iterable<T>::value && !is_string<T>::value,
    std::ostream&
>::type
operator<<(std::ostream& os, const T& container) {
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
#define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
template<typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>; //defines min_pq

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rand_num(int l, int r) {
    return rnd()%(r-l+1)+l;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<pair<int,int>> b;
        int mx = -1;
        F0R(i, n) {
            if(a[i]>mx) {
                mx=a[i];
                b.add({i,a[i]});
            }
        }
        //dp[index][mx][sum]
        // n=b.size();
        vt<vt<int>> dp(k+1, vt<int>(k+1, -inf));
        dp[0][0]=0;
        vt<int> dpMax(k+1, -inf);
        dpMax[0]=0;
        // cout << b << endl;
        F0R(i, b.size()) {
            int sz;
            if(i==b.size()-1) sz=n-b[i].f;
            else sz=b[i+1].f-b[i].f;
            vt<vt<int>> ndp(k+1, vt<int>(k+1,-inf));
            vt<int> nDpMax(k+1, -inf);
            F0R(mx, k+1) {
                FOR(sum, mx, k+1) {
                    if(i==1 && mx==1 && sum==1) {
                        // cout << "LINE 152" << endl;
                    }
                    ndp[mx][sum]=dp[mx][sum]+sz*mx;
                    if(b[i].s>=mx) {
                                            if(i==1 && mx==1 && sum==1) {
                        // cout << "LINE 157 " << dpMax << " " << sz*mx <<  endl;
                    }
                        ndp[mx][sum]=max(ndp[mx][sum], dpMax[sum-mx]+sz*mx);
                    }
                    nDpMax[sum]=max(nDpMax[sum], ndp[mx][sum]);
                }
            }

            swap(ndp,dp);
            swap(nDpMax, dpMax);
            // cout << i << " " << dp << dpMax << endl;
        }
        int ans = 0;
        F0R(i, k+1) ans=max(ans, dpMax[i]);
        cout << ans << endl;
    }
    return 0;
}