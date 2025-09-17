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
        int n;
        cin >> n;
        vt<pair<int,int>> points(n);
        F0R(i, n) cin >> points[i].f >> points[i].s;
        //(dx, dy, distance)
        vt<array<int,3>> v;
        int dx = 0, dy = 0;
        cout << "? L 1000000000" << endl;
        int ans;
        cin >> ans;
        dx-=1000000000;
        v.add({dx, dy, ans});
        cout << "? L 1000000000" << endl;
        cin >> ans;
        dx-=1000000000;
        v.add({dx, dy, ans});
        cout << "? D 1000000000" << endl;
        cin >> ans;
        dy-=1000000000;
        v.add({dx, dy, ans});
        cout << "? D 1000000000" << endl;
        cin >> ans;
        dy-=1000000000;
        v.add({dx, dy, ans});
        cout << "? R 1000000000" << endl;
        cin >> ans;
        dx+=1000000000;
        v.add({dx, dy, ans});
        cout << "? R 1000000000" << endl;
        cin >> ans;
        dx+=1000000000;
        v.add({dx, dy, ans});
        cout << "? R 1000000000" << endl;
        cin >> ans;
        dx+=1000000000;
        v.add({dx, dy, ans});
        cout << "? R 1000000000" << endl;
        cin >> ans;
        dx+=1000000000;
        v.add({dx, dy, ans});
        cout << "? U 1000000000" << endl;
        cin >> ans;
        dy+=1000000000;
        v.add({dx, dy, ans});
        cout << "? U 1000000000" << endl;
        cin >> ans;
        dy+=1000000000;
        v.add({dx, dy, ans});
        /*
        3: x1-(X-2e9)+y1-(Y-2e9) = ans1
        7: (X+2e9)-x2+y2-(Y-2e9) = ans2

        3+7: 
        x1+2e9+2e9-x2+y1+y2-2Y+4e9 = ans1+ans2
        2Y = x1-x2+y1+y2+8e9-ans1-ans2

        7-3:
        2X-x2-x1+y2-y1=ans2-ans1
        */
        vt<pair<int,int>> possAns;
        F0R(i, n) F0R(j, n) {
            int x1 = points[i].f, x2 = points[j].f, y1 = points[i].s, y2 = points[j].s;
            int ans1 = v[3][2], ans2 = v[7][2];
            if((x1-x2+y1+y2+8000000000LL-ans1-ans2)%2) continue;
            if((ans2-ans1+x2+x1+y1-y2)%2) continue;
            possAns.add({(ans2-ans1+x2+x1+y1-y2)/2, (x1-x2+y1+y2+8000000000LL-ans1-ans2)/2});
        }
        if(possAns.size()==0) return 0;
        auto DIST = [&](pair<int,int> cur)->int{
            int an = inf;
            F0R(i, n) {
                an = min(an, abs(cur.f-points[i].f)+abs(cur.s-points[i].s)); 
            }
            return an;
        };
        // cout << v << endl;
        bool done = false;
        trav(x, possAns) {
            bool ok = true;
            F0R(i, 10) {
                if(DIST({x.f+v[i][0], x.s+v[i][1]})!=v[i][2]) {
                    ok=false;
                    break;
                }
            }
            if(ok) {
                done=true;
                cout << "! " << x.f << " " << x.s << endl;
                break;
            }
        }
        assert(done);
    }
    return 0;
}