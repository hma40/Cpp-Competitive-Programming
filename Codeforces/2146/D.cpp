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
    set<int> good;
    for(int i = 0; i < (1LL<<50); i=i*2+1) good.insert(i);
    while(t--) {
        int l,r;
        cin >> l >> r;
        vt<int> ans(r-l+1);
        vt<int> inv(r-l+1);//inv[i+l]
        int times = 0;
        auto DO = [&](auto self, int lx, int rx)->void{
            // cout << lx << " " << rx << endl;
            times++;
            if(lx>rx) return;
            if(lx==rx) {
                ans[lx-l]=lx;
                inv[lx-l]=lx-l;
                return;
            }
            int bruh = 0;
            R0F(i, 31) {
                if((lx&(1LL<<i)) != (rx&(1LL<<i))) {
                    bruh+=1LL<<i;
                    // change=1LL<<i;
                    break;
                } else {
                    bruh+=lx&(1LL<<i);
                }
            }
            int nxt = bruh;
            ROF(i, lx, bruh) {
                ans[i-l]=nxt++;
                if(nxt>rx) {
                    self(self, lx, i-1);
                    break;
                }
            }
            nxt = bruh-1;
            FOR(i, bruh, rx+1) {
                ans[i-l]=nxt--;
                if(nxt<lx) {
                    self(self, i+1, rx);
                    break;
                }
            }
        };  
        DO(DO, l, r);
        int sum = 0;
        FOR(i, l, r+1) {
            sum+=i|ans[i-l];
        }
        // cerr << times << endl;
        // cout << times << endl;
        cout << sum << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}
/*
DO(0,3)
DO(0,1), DO(2,3)
DO(0,0), DO(1,1), DO(2,2), DO(3,3)
[0,1,2,3]
[1,0,3,2]
[3,2,1,0]


6 7 8 9 10
DO(6,7)
DO(8,10)



6 7 8 9 10
9 8 7 6 10
*/