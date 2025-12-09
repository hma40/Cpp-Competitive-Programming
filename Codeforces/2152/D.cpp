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
    set<int> p2;
    F0R(i, 35) p2.insert(1LL<<i);
    set<int> wtf;
    F0R(i, 35) wtf.insert((1LL<<i)*2+1);
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> threes(n+1);
        vt<int> bad(n+1);
        vt<int> moves(n+1);
        F0R(i, n) {
            if(wtf.count(a[i])) {
                threes[i+1]=threes[i]+1;
                bad[i+1]=bad[i];
            } else if(p2.count(a[i])) {
                threes[i+1]=threes[i];
                bad[i+1]=bad[i]+1;
            } else {
                threes[i+1]=threes[i];
                bad[i+1]=bad[i];
            }
            int here = 0;
            for(int j = a[i]; j!=1; j/=2) here++;
            moves[i+1]=moves[i]+here;
        }
        while(q--) {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            int ans = moves[r+1]-moves[l];
            int tot = threes[r+1]-threes[l];
            int bads = bad[r+1]-bad[l]+(tot+1)/2;
            // cout << l << " " << r << " " << bads << " " << tot << endl;
            ans+=(r-l+1)-bads;
            cout << ans << endl;
        }
    }
    return 0;
}
/*
If you can bring number to 2 its bad (they cant make you spend extra move)
3: good
4: bad
5: good
6: good
7: good
8: bad
9: good
*/