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
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
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
        int ans = 0;
        vt<bool> active(n, 1);
        int nxt = 1;
        int left = n;
        bool bef = true;
        vt<bool> ans_poss(n+1, 1);
        while(true) {
            // cout << active << endl;
            left=0;
            F0R(i, n-1) if(active[i]) left++;
            left++;
            if(left==1) break;
            int exp_no = 0, exp_yes = 0;
            FOR(i, 1, n+1) if(ans_poss[i]) if(i&nxt) exp_yes++; else exp_no++;
            // cout << active << exp_no << " " << exp_yes << endl;
            vt<bool> res(n);
            
            F0R(i, n-1) {
                if(active[i]) {
                    cout << "? " << i+1 << " " << nxt << endl;
                    int x;
                    cin >> x;
                    if(x) {
                        exp_yes--;
                        res[i]=1;
                    }
                    else exp_no--;
                }
            }
            // cout << "LINE 128: " << exp_no << " " << exp_yes << endl;
            if(exp_yes) {
                ans+=nxt;
                F0R(i, n) if(!res[i]) active[i]=false;
                FOR(i, 1, n+1) {
                    if(!(i&nxt)) ans_poss[i] = false;
                }
                bef=false;
            } else {
                bef=true;
                F0R(i, n) if(res[i]) active[i]=false;
                FOR(i, 1, n+1) {
                    if((i&nxt)) ans_poss[i] = false;
                }
            }
            nxt*=2;
            if(nxt>n) break;
        }
        // cout << "! " << ans << endl;
        FOR(i, 1, n+1) if(ans_poss[i]) cout << "! " << i << endl;
    }
    return 0;
}
/*
9
9 8 5 3 6 7 4 2 1
*/