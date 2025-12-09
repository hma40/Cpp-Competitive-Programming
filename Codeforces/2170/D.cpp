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
        int n,q;
        cin >> n >> q;
        string s;
        cin >> s;
        int free_neg = 0;
        int ques = 0;
        int after_one = 0;
        int max_pairs = 0;
        int streak = 0, neg=0;
        int val = 0;
        int universal = 0;
        FOR(i, 1, n-1) {
            if(s[i-1]=='I' && s[i]=='?' && (s[i+1]=='X' || s[i+1]=='V')) universal++;
        }
        F0R(i, n) {
            if(s[i]=='?') {
                ques++;
                streak++;
            } else {
                max_pairs+=(streak-neg)/2;
                neg=0;
                streak=0;
            }
            if(s[i]=='V') val+=5;
            else if(s[i]=='X') val+=10;
            else if(s[i]=='I') {
                if(i!=n-1 && (s[i+1]=='V' || s[i+1]=='X')) val--;
                else val++;
            }
            if(i!=n-1) {
                if(s[i]=='?' && (s[i+1]=='V' || s[i+1]=='X')) {
                    neg++;
                    free_neg++;
                }
                if(s[i]=='I' && s[i+1]=='?') neg++, after_one++;
            }
        }
        free_neg-=universal;
        after_one-=universal;
        max_pairs+=(streak-neg)/2;
        while(q--) {
            int a,b,c;
            cin >> a >> b >> c;
            a=max(0LL, ques-b-c);
            b=max(0LL, min(b,ques-c));
            c=min(c, ques);
            // cout << a << " " << b << " " << c << endl;
            int ans = val;
            ans-=min(c, free_neg);
            c-=min(c, free_neg);
            ans+=10*a+5*b;
            // cout << "line 171: " << ans << endl;
            int bruh = min(max_pairs, min(c, a+b));
            ans-=bruh;
            c-=bruh;
            if(b>bruh) {
                b-=bruh;
            } else {
                a-=(bruh-b);
                b=0;
            }
            // c-=min(max_pairs, min(c,a+b));
            ans+=c;
            ans-=2*min(after_one, a+b);
            ans-=2*universal;
            cout << ans << endl;
        }
    }
    return 0;
}
/*
1
5 1
V??I?
1 0 2

*/