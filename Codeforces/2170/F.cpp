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
// #define int long long
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
const int MAXN = 9;
// int dp[MAXN][4096][13];
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n;
    cin >> n;
    vt<int> a(n);
    F0R(i, n) cin >> a[i];
    vt<vt<int>> dp(4096, vt<int>(13, 1e9));
    dp[a[n-1]][1]=n-1;
    int q;
    cin >> q;
    vt<array<int,4>> qu(q);
    F0R(i, q) {
        cin >> qu[i][0] >> qu[i][1] >> qu[i][2];
        qu[i][0]--;
        qu[i][1]--;
        qu[i][3]=i;
    }
    vt<int> anss(q);
    auto calc_dp = [&](int i)->void{
        vt<vt<int>> ndp(4096, vt<int>(13, 1e9));
        FOR(j, 1, 4096) FOR(k, 1, 13) ndp[j][k]=min(dp[j][k], dp[j^a[i]][k-1]);
        ndp[a[i]][1]=i;
        dp=ndp;
        // F0R(j, 4096) F0R(k, 13) {
            // if(dp[j][k]!=1e9) {
                // cout << i << " " << j << " " << k << " " << dp[j][k] << endl;
            // }
        // }
    };
    sort(rbegin(qu),rend(qu));
    int ind = n-2;
    trav(x, qu) {
        while(ind>=x[0]) {
            calc_dp(ind);
            ind--;
        }
        // cout << "line 155: " << x << endl;
        int ans = 1e9;
        FOR(i, 1, 13) {
            if(dp[x[2]][i]<=x[1]) ans=min(ans, i);
        }
        if(ans==1e9) ans=0;
        anss[x[3]]=ans;
    }
    F0R(i, q) cout << anss[i] << " ";
    cout << endl;
    return 0;
}
/*
dp[start][value we want][number of numbers we use]
*/