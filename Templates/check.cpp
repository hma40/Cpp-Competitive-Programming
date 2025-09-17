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
    int n;
    string s;
    string ss;
    cin >> n >> s >> ss;
    auto good = [&](string sss)->bool{
        // cout << sss << endl;
        int sum = 0;
        trav(x, sss) {
            if(x=='(') sum++;
            else sum--;
            if(sum<0) return false;
        }
        return sum==0;
    };
    set<string> st;
    deque<string> dq;
    dq.push_back(s);
    st.insert(s);
    while(dq.size()) {
        auto tp = dq.front();
        dq.pop_front();
        FOR(i, 1, n) {
            if(tp[i-1]=='(' && tp[i]=='(') {
                auto cpy = tp;
                cpy[i-1]=cpy[i]=')';
                if(!st.count(cpy)) {
                    st.insert(cpy);
                    dq.add(cpy);
                }
            }
            if(tp[i-1]==')' && tp[i]==')') {
                auto cpy = tp;
                cpy[i-1]=cpy[i]='(';
                if(!st.count(cpy)) {
                    st.insert(cpy);
                    dq.add(cpy);
                }
            }
        }
    }
    bool found = false;
    trav(x, st) {
        // cout << x << endl;
        if(good(x)) found=true;
    }
    // cout << found << endl;
    // cout << ss << found << endl;
    if(ss=="-1") {
        if(found) {
            cout << "WA" << endl;
        } else {
            cout << "OK" << endl;
        }
    } else {
        if(good(ss) && st.count(ss)) {
            cout << "OK" << endl;
        } else {
            cout << "WA" << endl;
        }
    }
    return 0;
}
/*
10
)))(()))((
(())))))((
*/