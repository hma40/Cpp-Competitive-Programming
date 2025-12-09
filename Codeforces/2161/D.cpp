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
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];

        a.add(0);
        n++;
        vt<vt<int>> inv(n+1);
        F0R(i, n) inv[a[i]].add(i);
        vt<int> dp(n, inf);
        // cout << inv << endl;
        dp[n-1]=0;
        priority_queue<int> pq;
        FOR(i, 1, n+1) {
            // cout << "line 138 " << i << inv[i] << endl;
            int mn_sec = dp[n-1]; //dp[n-1] = removes all of that number
            // trav(x, inv[a[i]-1]) mn_sec=min(mn_sec, dp[x]);
            int is_rem = inv[i].size();
            trav(x, inv[i-1]) pq.push(x);
            trav(x, inv[i]) pq.push(x);
            int ad = 0;
            while(pq.size()) {
                auto tp = pq.top();
                pq.pop();
                // cout << "line 148 " << tp << endl;
                if(a[tp]==i) {
                    ad++;
                    is_rem--;
                    dp[tp]=mn_sec+is_rem;
                } else {
                    mn_sec = min(mn_sec, dp[tp]+ad);
                }
            }
            // cout << "line 156" << endl;
            int last = dp[n-1];
            trav(x, inv[i-1]) last=min(last, dp[x]);
            last+=inv[i].size();
            dp[n-1]=last;
        }
        // cout << dp << endl;
        int ans = dp[n-1];
        trav(x, inv[n]) ans=min(ans, dp[x]);
        cout << ans << endl;
    }
    return 0;
}
/*
in our final array, lets suppose first[x] and last[x] as first and last positions with x active
now we should have
first[x]>last[x+1]
in other words, if we consider numbers from smallest to largest, the only thing that matters after this number is first[i]
so lets say dp[i][j] = min number of elements we have to remove if we consider numbers 1...i, and first[i]>=j
transition? dp[i][j] = (number of i's before j) + min(dp[i-1][k]+(number of i's after k)). 
*/