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
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
bool sq(int x) {
    int s = sqrt(x);
    while((s+1)*(s+1)<=x) s++;
    while(s*s>x) s--;
    return s*s==x;
}
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
        if(n==2) {
            cout << -1 << enld;
            continue;
        }
        if(n==3) {
            cout << "1 3\n2 3\n";
            continue;
        }
        if(n==4) {
            cout << "1 2\n1 3\n1 4\n";
            continue;
        }
        if(n==5) {
            cout << "3 1\n3 2\n3 4\n3 5\n";
            continue;
        }
        auto build = [&](int m, int k)->void{
            FOR(i, 2, n+1) {
                if(i==k) continue;
                cout << 1 << " " << i << endl;
            }
            cout << m << " " << k << endl;
        };
        int x = n*(n+1)/2-1;
        // cout << x << endl;
        bool done = false;
        pair<int,int> mk = {-1,-1};
        for(int i = sq(x); true; i++) {
            if(i*i<=x) continue;
            int diff = i*i-x;
            for(int j = 1; j*j<=diff; j++) {
                if(diff%j!=0) continue;
                int m = j+1, k = diff/j;
                if(m==k) continue;
                if(m>n || k>n) continue;
                if(m<=1 || k<=1) continue;
                build(m,k);
                done=true;
                break;
            }
            if(done) break;
        }
        // assert(done);
    }
    return 0;
}