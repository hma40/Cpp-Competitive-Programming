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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
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
        string s;
        cin >> s;
        if(k==n) {
            F0R(i, n) cout << "-";
            cout << endl;
            continue;
        }
        int zeroes = 0, ones = 0, twos = 0;
        trav(x, s) if(x=='0') zeroes++; else if(x=='1') ones++;
        else twos++;
        // cout << s << zeroes << " " << ones << " " << twos << endl;
        // return 0;
        // string s;
        s.clear();
        F0R(i, n) s+='+';
        // cout << s << endl;
        F0R(i, twos+zeroes) s[i]='?';
        F0R(i, twos+ones) s[n-1-i]='?';
        F0R(i, zeroes) s[i]='-';
        F0R(i, ones) s[n-1-i]='-';
        cout << s << endl;
    }
    return 0;
}