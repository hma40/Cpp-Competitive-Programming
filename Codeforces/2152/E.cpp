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
        vt<bool> seen(n*n+1);
        vt<pair<int,int>> edges;
        auto qu = [&](vt<int> here)->vt<int>{
            cout << "? " << here.size() << " ";
            trav(x, here) cout << x+1 << " ";
            cout << endl;
            vt<int> res;
            int m;
            cin >> m;
            F0R(i, m) {
                int x;
                cin >> x;
                res.add(x-1);
            }
            return res;
        };
        vt<vt<int>> greater(n*n+1), less(n*n+1);
        F0R(i, n) {
            vt<int> here;
            F0R(j, n*n+1) if(!seen[j]) here.add(j);
            // cout << "LINE 124 " << here << endl;
            if(here.size()==0) break;
            auto res = qu(here);
            F0R(j, res.size()-1) {
                edges.add({res[j], res[j+1]});
            }
            F0R(j, res.size()) {
                int nxt = n*n+1;
                // cout << "LINE 132: " << j << " " << nxt << endl;
                if(j!=res.size()-1) nxt=res[j+1];
                FOR(k, res[j]+1, nxt) if(!seen[k]) edges.add({k, res[j]});
            }
            trav(x, res) seen[x]=true;
        }
        trav(x, edges) {
            if(x.s>x.f) {
                greater[x.f].add(x.s);
            } else {
                less[x.s].add(x.f);
            }
        }
        // cout << greater << less << endl;
        // cout << edges << endl;
        vt<int> dp1(n*n+1, 1), from1(n*n+1, -1), dp2(n*n+1, 1), from2(n*n+1, -1);
        bool found = false;
        F0R(i, n*n+1) {
            if(dp1[i]==n+1 || dp2[i]==n+1) found=true;
            trav(x, greater[i]) {
                if(dp1[i]+1>dp1[x]) {
                    dp1[x]=dp1[i]+1;
                    from1[x]=i;
                }
            }
            trav(x, less[i]) {
                if(dp2[i]+1>dp2[x]) {
                    dp2[x]=dp2[i]+1;
                    from2[x]=i;
                }
            }
        }
        // cout << dp1 << dp2 << endl;
        F0R(i, n*n+1) {
            if(dp1[i]==n+1) {
                cout << "! ";
                vt<int> here;
                for(int j = i; j!=-1; j=from1[j]) here.add(j);
                reverse(begin(here),end(here));
                trav(x, here) cout << x+1 << " ";
                cout << endl;
                break;
            } 
            if(dp2[i]==n+1) {
                cout << "! ";
                vt<int> here;
                for(int j = i; j!=-1; j=from2[j]) here.add(j);
                reverse(begin(here),end(here));
                trav(x, here) cout << x+1 << " ";
                cout << endl;
                break;
            }
        }
    }
    return 0;
}