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
// your original is_iterable (unchanged)
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// detect std::basic_string<...>
template <typename T>
struct is_string : std::false_type {};

template <typename CharT, typename Traits, typename Alloc>
struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type {};

// optionally also detect string_view (C++17)
template <typename CharT, typename Traits>
struct is_string<std::basic_string_view<CharT, Traits>> : std::true_type {};

// now enable the generic container printer only when T is iterable AND not a string
template <typename T>
typename std::enable_if<
    is_iterable<T>::value && !is_string<T>::value,
    std::ostream&
>::type
operator<<(std::ostream& os, const T& container) {
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
ll mod = 998244353;
const ll inf = 1e18;
template<typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>; //defines min_pq

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rand_num(int l, int r) {
    return rnd()%(r-l+1)+l;
}
int bexpo(int b, int e) {
    if(e<0) return bexpo(bexpo(b, -e), mod-2);
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        b=b*b%mod;
        e>>=1;
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
        cin >> n >> m >> mod;
        if(n==1) {
            cout << 1 << endl;
            continue;
        }
        int ans = 0;
        /*
        different parity
        (n-f+1) * (n-s+1) * m^(ceil((f+1)/2)+ceil((s+1)/2)+n-f-s)
        with f fixed, sum over s
        say we fix parity of s
        when s+=2: this term is /m/(n-s+1)*(n-s-1)
        x, x(n-s-1)/m/(n-s+1), x(n-s-3)/m/(n-s+1)
        here, x = 
        x/(n-s+1) * ((n-s+1)/m^0 + (n-s-1)/m^1 + (n-s-3)/m^2 + ...)
        
        y = n-s+1

        we want: 
        y/m^0+(y-2)/m+(y-4)/m^2+...
        but wait this term is constant for all

        Same parity:
        Above, but - min(n-fir+1, n-sec+1) * m^(ceil((f+1)/2)+ceil((s+1)/2)+n-f-s)
        now: fix max(fir,sec)
        sum s from M * m^((f+1)/2+n-f) * m^((s+1)/2-s)
                
        */
        vt<int> bexpos(n+5);
        bexpos[0]=1;
        for(int i = 1; i < n+5; i++) bexpos[i]=bexpos[i-1]*m%mod;
        vt<int> negBexpos(n+5, 1);
        int inv = bexpo(m, mod-2);
        for(int i = 1; i < n+5; i++) negBexpos[i]=negBexpos[i-1]*inv%mod;
        auto bexpo = [&](int exp)->int{
            if(exp<0) return negBexpos[-exp];
            else return bexpos[exp];
        };
        int c = 0;
        for(int sec = 2; sec <= n; sec+=2) {
            c+=(n-sec+1)*bexpo(1-sec/2);
            c%=mod;
        }
        for(int fir = 1; fir <= n; fir+=2) {
            int x = (n-fir+1)%mod*bexpo((fir+1)/2+n-fir-1)%mod;
            int here = x*c%mod*2%mod;
            ans+=here;
            ans%=mod;
        }
        for(int fir = 2; fir <= n; fir+=2) {
            int x = (n-fir+1)%mod*bexpo((fir+1)/2+n-fir-1)%mod;
            int here = x*c%mod;
            ans+=here;
            ans%=mod;
        }
        c = 0;
        for(int sec = 1; sec <= n; sec+=2) {
            c+=(n-sec+1)*bexpo(-sec/2);//bexpo(bexpo(m, sec/2), mod-2);
            c%=mod;
        }

        for(int fir = 1; fir <= n; fir+=2) {
            int x = (n-fir+1)*bexpo((fir+1)/2+n-fir)%mod;
            int here = x*c%mod;
            ans+=here;
        }
        vt<int> v(n+1);
        for(int i = 1; i <= n; i++) {
            v[i]+=bexpo((i+1)/2-i);
            v[i]%=mod;
            if(i+2<=n) v[i+2]=v[i]+bexpo((i+1)/2-i);
        }
        FOR(mx, 1, n+1) {
            int M = n+1-mx;
            int temp = M*v[mx]%mod*bexpo((mx+1)/2-mx+n);
            ans-=temp;
            ans%=mod;
            ans+=mod;
            ans%=mod;
        }
        FOR(larger, 1, n+1) {
            int choices = (larger+1)/2*2-1;
            int here = choices*bexpo(n-larger+(larger+1)/2)%mod*(n-larger+1);
            ans+=here;
            ans%=mod;
            ans+=mod;
            ans%=mod;
        }
        ans*=bexpo(-n);//bexpo(bexpo(m, n), mod-2);
        ans%=mod;
        ans+=mod;
        ans%=mod;
        cout << ans << endl;
    }
    return 0;
}