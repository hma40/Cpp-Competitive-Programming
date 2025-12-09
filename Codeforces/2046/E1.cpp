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
const ll mod = 998244353;
const ll inf = 1e18;
template<typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>; //defines min_pq

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rand_num(int l, int r) {
    return rnd()%(r-l+1)+l;
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
        set<int> unused;
        FOR(i, 1, 6*n+5) unused.insert(i);
        vt<array<int,3>> a(n);
        F0R(i, n) {
            cin >> a[i][0] >> a[i][1] >> a[i][2];
            swap(a[i][1], a[i][2]);
            unused.erase(a[i][1]);
        }
        vt<vt<int>> teams(m);
        F0R(i, m) {
            int k;
            cin >> k;
            F0R(j, k) {
                int x;
                cin >> x;
                teams[i].add(x-1);
            }
        }

        int mxStrength2 = 0;
        trav(x, teams[1]) {
            mxStrength2=max(mxStrength2, a[x][0]);
        }
        int min_cannot = mxStrength2+1;
        map<int,int> mp2, mp3;
        int mn_0 = inf;
        trav(x, teams[0]) {
            mn_0=min(mn_0, a[x][0]);
            if(a[x][0]<=mxStrength2) {
                // addInterval()
                min_cannot = min(min_cannot, a[x][0]+1);
                if(mp2.count(a[x][1])) {
                    mp2[a[x][1]]=min(mp2[a[x][1]], a[x][2]);
                    mp3[a[x][1]]=min(mp3[a[x][1]], a[x][0]);
                } else {
                    mp2[a[x][1]]=a[x][2];
                    mp3[a[x][1]]=a[x][0];
                }
            }
        }
        map<int,int> maxSpecialization;
        map<int,int> maxStrength;
        trav(x, teams[1]) {
            if(a[x][0]>=mn_0) maxSpecialization[a[x][1]]=max(maxSpecialization[a[x][1]], a[x][2]);
            maxStrength[a[x][1]]=max(maxStrength[a[x][1]], a[x][0]);
        }
        vt<pair<int,int>> ans;
        bool bad = false;
        //map: topic -> difficulty range
        
        // set<pair<int,int>> iv, ivBack;
        // auto addInterval = [&](int lo, int hi)->void{
        //     auto lb = iv.upper_bound({lo,hi});
        //     if(lb!=iv.end() && (*lb).f<=hi) {
        //         hi=(*lb).s;
        //         ivBack.erase({(*lb).s, (*lb).f});
        //         iv.erase(*lb);
        //     }
        //     lb = ivBack.lower_bound({lo,0});
        //     if(lb!=ivBack.end() && (*lb).s<=hi) {
        //         lo=(*lb).s;
        //         iv.erase({(*lb).s,(*lb).f});
        //         ivBack.erase(*lb);
        //     }
        //     iv.insert({lo,hi});
        //     ivBack.insert({hi,lo});
        // };
        // assert(false);
        

        trav(x, mp2) {
            int lower_limit = max(mxStrength2+1, maxSpecialization[x.f]+1);
            // cout << x << endl;
            if(mxStrength2+1>x.s) {
                // cout << "line 196: bad because of " << x << endl;
                bad=true;
            } else if(lower_limit>x.s) {
                if(mn_0>maxStrength[x.f]) {
                    ans.add({mxStrength2+1, x.f});
                } else {
                    // cout << "line 201: bad because of " << x << endl;
                    bad=true;
                }
            } else {
            //need to find a number [lower_limit, x.s]
                ans.add({lower_limit, x.f});
            }
        }
        // cout << unused << endl;
        // return 0;
        // assert(false);
        int done = 0;
        while(ans.size()<5*n) {
            // cout << unused << " " << ans.size() << endl;
            if(done==0) {
                ans.add({mn_0, (*unused.begin())});
                unused.erase((*unused.begin()));
            } else {
                ans.add({mxStrength2+1, (*unused.begin())});
                unused.erase((*unused.begin()));
            }
            done++;
        }
        if(bad) {
            cout << -1 << endl;
        } else {
            // cout << 0 << endl;
            cout << ans.size() << endl;
            trav(x, ans) cout << x.f << " " << x.s << endl;
        }
        // solve();
    }
    return 0;
}
/*
1
9 2
4 9 2
3 10 1
10 10 8

1 10 2
6 8 2
4 4 8
1 2 3
5 6 1
4 4 7

3 1 6 7 
6 2 3 4 5 8 9 
*/