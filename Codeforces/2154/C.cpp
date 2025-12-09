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
    vt<vt<int>> facts(2e5+5);
    FOR(i, 2, 2e5+5) {
        for(int j = i; j < 2e5+5; j+=i) {
            facts[j].add(i);
        }
    }
    vt<int> count(2e5+5);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> v(n);
        F0R(i, n) cin >> v[i].s;
        F0R(i, n) cin >> v[i].f;
        sort(begin(v),end(v));   
        vt<int> here;
        F0R(i, n) {
            trav(x, facts[v[i].s]) {
                here.add(x);
                count[x]++;
            }
        }
        int ans = inf;
        trav(x, here) {
            if(count[x]>1) {
                ans=0;
            }
        }
        if(ans==0) {
            cout << 0 << endl;
            trav(x, here) count[x]=0;
            continue;
        }
        ans=min(ans, v[0].f+v[1].f);
        F0R(i, n) {
            trav(x, facts[v[i].s+1]) {
                // cout << i << " " << x << " " << count[x] << endl;
                if(count[x]) ans=min(ans, v[i].f);
            }
        }
        trav(x, here) {
            if(v[0].s%x==0) continue;
            int cost = x-v[0].s%x;
            ans=min(ans, cost*v[0].f);
        }
        cout << ans << endl;
        trav(x, here) count[x]=0;
    }
    return 0;
}