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
// template <typename T, typename = void>
// struct is_iterable : std::false_type {};

// // template <typename T>
// // struct is_iterable<T, std::void_t<
// //     decltype(std::begin(std::declval<T>())),
// //     decltype(std::end(std::declval<T>()))
// // >> : std::true_type {};

// // // Generic container printer (vector, set, deque, array, map, etc.)
// // template <typename T>
// // typename std::enable_if<is_iterable<T>::value, ostream&>::type
// // operator<<(ostream& os, const T& container) {
// //     os << "{ ";
// //     for (auto it = std::begin(container); it != std::end(container); ++it) {
// //         os << *it;
// //         if (std::next(it) != std::end(container)) os << ", ";
// //     }
// //     os << " }";
// //     return os;
// // }

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
    int n;
    string s;
    cin >> n >> s;
    string cpy = s;
    set<int> a,b;
    FOR(i, 1, 2*n) {
        if(s[i]=='A') a.insert(i);
        else b.insert(i);
    }
    int ans = 0;
    
    FOR(i, 1, 2*n) {
        if(s[i]==s[i-1]) {
            if(s[i-1]=='A') {
                auto low = *b.begin();
                ans+=low-i;
                a.erase(i);
                b.erase(low);
                a.insert(low);
                swap(s[i], s[low]);
            } else {
                auto low = *a.begin();
                ans+=low-i;
                b.erase(i);
                a.erase(low);
                b.insert(low);
                swap(s[i], s[low]);
            }
        } else {
            if(s[i]=='A') {
                a.erase(i);
            } else {
                b.erase(i);
            }
        }
    }
    swap(s, cpy);
    a.clear();
    b.clear();
    FOR(i, 1, 2*n) {
        if(s[i]=='A')
        a.insert(i);
        else b.insert(i);
    }
    int ans2 = 0;
    if(s[0]=='A') {
        auto low = *b.begin();
        b.erase(low);
        a.insert(low);
        ans2+=low;
        swap(s[low], s[0]);
    } else {
        auto low = *a.begin();
        a.erase(low);
        b.insert(low);
        ans2+=low;
        swap(s[low], s[0]);
    }
    FOR(i, 1, 2*n) {
        if(s[i]==s[i-1]) {
            if(s[i-1]=='A') {
                auto low = *b.begin();
                ans2+=low-i;
                a.erase(i);
                b.erase(low);
                a.insert(low);
                swap(s[i], s[low]);
            } else {
                auto low = *a.begin();
                ans2+=low-i;
                b.erase(i);
                a.erase(low);
                b.insert(low);
                swap(s[i], s[low]);
            }
        } else {
            if(s[i]=='A') {
                a.erase(i);
            } else {
                b.erase(i);
            }
        }
    }
    cout << min(ans2, ans) << endl;
    return 0;
    for(int i = 0; i < 2*n; i+=2) {
        if(s[i]!=s[i+1]) {
            if(s[i]=='A') {
                a.erase(i);
                b.erase(i+1);
            } else {
                b.erase(i);
                a.erase(i+1);
            }
            continue;
        }
        if(s[i]=='A') {
            a.erase(i);
            auto fb = *b.begin();
            a.erase(i+1);
            b.erase(fb);
            a.insert(fb);
            // b.insert(i+1);
            swap(s[i+1], s[fb]);
            ans+=fb-i-1;
        } else {
            b.erase(i);
            auto fb = *a.begin();
            b.erase(i+1);
            a.erase(fb);
            b.insert(fb);
            // a.insert(i+1);
            swap(s[i+1], s[fb]);
            ans+=fb-i-1;
        }
        cout << i << " " << s << " " << ans << endl;
    }        
    cout << ans << endl;
    return 0;
}