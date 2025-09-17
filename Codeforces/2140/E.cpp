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
// #define int long long
#define vt vector
// #define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
long long bexpo(long long b, long long e) {
    long long ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        int k;
        cin >> k;
        vt<int> nPrime(k);
        F0R(i, k) cin >> nPrime[i];
        // vt<int> nPrime = {1,4,6,8,9,10,12,14,15,16,18,20};
        vt<vt<int>> adp(1<<n, vt<int>(n+1)), bdp(1<<n, vt<int>(n+1));
        adp[0][1]=1;
        adp[1][1]=2;
        bdp[0][1]=1;
        bdp[1][1]=2;
        vt<int> aa;
        trav(x, nPrime) {
            int here = 0;
            F0R(j, x-1) here+=1<<j;
            aa.add(here);
        }
        FOR(sz, 2, n+1) {
            F0R(mask, 1<<sz) {
                int maxHere = 1, minHere = 2;
                F0R(irmv, nPrime.size()) {
                    int rmv = nPrime[irmv];
                    int andVal = aa[irmv];
                    if(rmv>sz) continue;
                    int nmask = andVal&mask;
                    // F0R(i, rmv-1) if(mask&(1<<i)) nmask+=1<<i;
                    int left = mask-nmask;
                    if(left&(1<<(rmv-1))) left-=(1<<(rmv-1));
                    left>>=1;
                    nmask+=left;
                    maxHere = max(maxHere, bdp[nmask][sz-1]);
                    minHere = min(minHere, adp[nmask][sz-1]);

                }
                adp[mask][sz]=maxHere;
                bdp[mask][sz]=minHere;
            }
        }
        vt<vt<vt<long long>>> dpdp(n+1, vt<vt<long long>>(n+1, vt<long long>(2)));//len, popcount, answer
        F0R(len, n+1) {
            F0R(i, 1<<len) {
                if(adp[i][len]==0) continue;
                dpdp[len][__builtin_popcount(i)][adp[i][len]-1]++;
            }
        }
        long long ans = 0;
        FOR(i, 1, m+1) {
            // cout << i << endl;
            int atLeast = m-i+1;
            int less = i-1;
            F0R(ix, n+1) {
                // cout << ix << endl;
                ans+=bexpo(less, n-ix)*bexpo(atLeast, ix)%mod*dpdp[n][ix][1];
                ans%=mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}