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
int rand_num(int a, int b) {
    return rnd()%(b-a+1)+a;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    int B = 200;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<array<int,3>> qu(q);
        int nxt = 0;
        map<int,int> mpmp;
        vt<int> invmp;
        trav(x, a) {
          if(mpmp.count(x)) continue;
          mpmp[x]=nxt++;
          invmp.add(x);
        }
        F0R(i, n) a[i]=mpmp[a[i]];
        // cout << a << endl;
        // return 0;
        vt<int> freq(n);
        vt<vt<int>> ans(q);
        F0R(i, q) {
            cin >> qu[i][0];
            cin >> qu[i][1];
            qu[i][2]=i;
            qu[i][0]--;
            qu[i][1]--;
        }

        sort(begin(qu),end(qu),[&](auto x, auto y)->bool{
            if(x[0]/B<y[0]/B) return true;
            else if(x[0]/B>y[0]/B) return false;
            return x[1]<y[1];
        });
        int l = 0, r = -1;
        // cout << qu << endl;
        // assert(false);
        vt<bool> marked(n);
        trav(x, qu) {
            // cout << s << endl;
            while(r<x[1]) {
                r++;
                freq[a[r]]++;
            }
            while(r>x[1]) {
                freq[a[r]]--;
                r--;
            }
            while(l<x[0]) {
              freq[a[l]]--;
                l++;
            }
            while(l>x[0]) {
                l--;
                freq[a[l]]++;
                // l++;
            }
            // cout << s << endl;
            int sz = x[1]-x[0]+1;
            
            F0R(i, 40) {
              int rr = rand_num(x[0],x[1]);
              if(freq[a[rr]]>sz/3) {
                if(!marked[a[rr]]) {
                  marked[a[rr]]=true;
                  ans[x[2]].add(invmp[a[rr]]);
                }
              }
            }
            trav(xx, ans[x[2]]) marked[mpmp[xx]]=false;
        }
        // cout << ans << endl;
        F0R(i, q) {
            sort(begin(ans[i]),end(ans[i]));
            if(ans[i].size()==0) cout << -1;
            else trav(x, ans[i]) cout << x << " ";
            cout << endl;
        }
    }
    return 0;
}