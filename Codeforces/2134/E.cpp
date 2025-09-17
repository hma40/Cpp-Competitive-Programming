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
        vt<int> ans(n+1);
        auto DOTWO = [&](int fir, int base)->bool{
            //implies same
            cout << "throw " << fir << endl;
            int a;
            cin >> a;
            if(a==base+1) {
                ans[fir]=2;
            } else {
                ans[fir]=1;
            }
            cout << "swap " << fir << endl;
            cout << "throw " << fir << endl;
            cin >> a;
            if(a==base+1) {
                ans[fir+1]=2;
                return true;
            } else {
                ans[fir+1]=1;
                return false;
            }
        };
        auto DO1 = [&](int fir, int base)->bool{
            //implies diff
            cout << "throw " << fir << endl;
            int a;
            cin >> a;
            if(a==base+1) {
                ans[fir]=1;
                return false;
            } else {
                ans[fir]=2;
                return true;
            }
        };
        int where = n, base=0;
        bool same = true;
        while(true) {
            if(where==3) {
                if(same) {
                    cout << "throw " << 2 << endl;
                    int a;
                    cin >> a;
                    if(a==base+1) {
                        ans[2]=2;
                    } else {
                        ans[2]=1;
                    }
                    cout << "swap " << 1 << endl;
                    cout << "throw " << 2 << endl;
                    cin >> a;
                    if(a==base+1) {
                        ans[1]=2;
                    } else {
                        ans[1]=1;
                    }
                    cout << "swap 2" << endl;
                    cout << "throw 2" << endl;
                    cin >> a;
                    if(a==base+1) {
                        ans[3]=2;
                    } else {
                        ans[3]=1;
                    }
                    break;
                }else {
                    same = DO1(3, base);
                    where=2;
                    if(!same) {
                        base++;
                    } 
                }
            } else if(where==2) {
                if(same) {
                    DOTWO(1, base);
                } else {
                    cout << "throw 2" << endl;
                    int a;
                    cin >> a;
                    if(a==base+1) {
                        ans[2]=1;
                    } else {
                        ans[2]=2;
                    }
                    cout << "swap 1" << endl;
                    cout << "throw 2" << endl;
                    cin >> a;
                    if(a==base+1) {
                        ans[1]=1;
                    } else {
                        ans[1]=2;
                    }
                }
                break;
            } else {
                if(same) {
                    same = DOTWO(where-1, base);
                    where-=2;
                    if(!same) base+=2;
                    else base++;
                } else {
                    same = DO1(where, base);
                    where--;
                    if(!same) base++;
                }
            }
        }
        cout << "! ";
        F0R(i, n) cout << ans[i+1] << " ";
        cout << endl;
    }
    return 0;
}
/*
what if we go backwards instead
ask(n-2)
if ans=1: a[n-2]=2
else a[n-2]=1

we can swap(n-1,n-2) and get n-1
this gets us n-2 and n-1 in 3 queries

now after this n-2 is either 1 or 2
if its 2 its simple (we are now doing the problem with base ans = 1)
if its 1

now back 2 is 
1 ?
i think we can just figure out what the last one is?
depending on answer is 2 or 3

? 2 2

1 2 1 2
*/