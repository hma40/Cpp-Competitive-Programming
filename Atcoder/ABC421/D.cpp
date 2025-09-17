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
    int rt, ct, ra, ca;
    int n,m,la;
    cin >> rt >> ct >> ra >> ca >> n >> m >> la;
    if(abs((rt+ct)%2)!=abs((ra+ca)%2)) {
        cout << 0 << endl;
        return 0;
    }
    vt<pair<char,int>> a(m), b(la);
    F0R(i, m) {
        cin >> a[i].f >> a[i].s;
    }
    F0R(i, la) {
        cin >> b[i].f >> b[i].s;
    }
    int ans = 0;
    int l = 0, r = 0;
    while(l<m) {
        // cout << r << endl;
        pair<int,int> mpoint = {-inf, -inf};
        if(a[l].f=='U' || a[l].f=='D') {
            if(b[r].f=='U' || b[r].f=='D') {
                if(ct==ca && a[l].f!=b[r].f) {
                    // int steps = abs(ra-rt)/2;
                    mpoint = {(rt+ra)/2, ct};
                    // if(steps!=0 && min(a[l].s, b[r].s)>=steps) ans++;
                }
            } else {
                mpoint = {ra, ct};
            }
        } else {
            if(b[r].f=='L' || b[r].f=='R') {
                if(rt==ra && a[l].f!=b[r].f) {
mpoint = {(rt+ra)/2, (ct+ca)/2};
                }
            } else {
                mpoint = {rt, ca};
            }
        }
        pair<int,int> nt = {rt, ct}, na = {ra, ca};
        int steps = min(a[l].s, b[r].s);
        // cout << l << " " << r << " " << mpoint << nt << na << " " << ans << endl;
        if(a[l].f=='U') {
            nt.f-=steps;
        } else if(a[l].f=='D') {
            nt.f+=steps;
        } else if(a[l].f=='R') {
            nt.s+=steps;
        } else {
            nt.s-=steps;
        }
        if(b[r].f=='U') {
            na.f-=steps;
        } else if(b[r].f=='D') {
            na.f+=steps;
        } else if(b[r].f=='R') {
            na.s+=steps;
        } else {
            na.s-=steps;
        }
        pair<int,int> oldt = {rt, ct}, olda = {ra, ca};
        if(oldt!=mpoint && min(oldt, nt)<=mpoint && mpoint<=max(oldt, nt)) {
            if(olda!=mpoint && min(olda, na)<=mpoint && mpoint<=max(olda, na)) {
                int tsteps = abs(oldt.f-mpoint.f) + abs(oldt.s-mpoint.s);
                int asteps = abs(olda.f-mpoint.f) + abs(olda.s-mpoint.s);
                if(tsteps==asteps) {
                    ans++;
                }
            }
        }
        if(a[l].f==b[r].f && oldt==olda) {
            ans+=steps;
        }
        // cout << "LINE 169 " << ans << " " << nt << " " << na << endl;
        a[l].s-=steps;
        if(a[l].s==0) l++;
        b[r].s-=steps;
        if(b[r].s==0) r++;
        rt = nt.f;
        ct = nt.s;
        ra = na.f;
        ca = na.s;
    }
    cout << ans << endl;
    return 0;
}
/*
2 -2 3 -3
6 4 4
L 1
U 1
D 1
U 1

D 1
D 1
U 1
U 1

*/