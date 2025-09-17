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
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        sort(begin(a),end(a));
        int sum = 0;
        F0R(i, n) sum+=a[i];
        int ans = sum;
        vt<int> p(n+1);
        F0R(i, n) p[i+1]=p[i]+a[i];
        auto getSum = [&](int lo, int hi)->int{
            return p[hi+1]-p[lo];
        };
        FOR(i, 1, n-1) {
            // cout << i << endl;
            int mxX = min(n-i-1, i/k);
            if(mxX!=n-i-1) {
                int here = i*a[i]-getSum(0, i)-getSum(i+1, i+mxX+1)+a[i]*(mxX+1);
                ans=max(ans, sum+here);
            }
            int lo = 1, hi = mxX+1;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(a[i]*k-getSum((mid-1)*k, mid*k-1)>a[i+mid]-a[i]) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            int here = k*lo*a[i]-getSum(0, k*lo-1)-getSum(i+1, i+lo)+a[i]*lo;
            ans=max(ans, sum+here);
        }
        cout << ans << endl;
    }
    return 0;
}
/*
x=1
lose: a[i+1]-a[i]
gain: sum(a[0], a[min(i-1),x-1])


*/