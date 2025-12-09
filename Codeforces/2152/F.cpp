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
        int n,z;
        cin >> n >> z;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> nxt(n, -1);
        F0R(i, n) {
            int lb = lower_bound(begin(a),end(a),a[i]+z+1)-begin(a);
            if(lb==n) continue;
            nxt[i]=lb;
        }
        // cout << nxt << endl;
        vt<vt<int>> leap1(n, vt<int>(19));
        F0R(i, n) leap1[i][0]=nxt[i];
        FOR(i, 1, 19) {
            F0R(j, n) {
                if(leap1[j][i-1]==-1) leap1[j][i]=-1;
                else leap1[j][i]=leap1[leap1[j][i-1]][i-1];
            }
        }
        vt<pair<int,int>> where(n, {-1,-1});
        F0R(i, n-1) {
            if(a[i]+z<a[i+1]) {
                if(i==n-2) {
                    where[i]={-1, 2};
                    continue;
                }
                where[i]={i+1, 1};
                continue;
            }
            // cout << i << endl;
            pair<int,int> p = {i,i+1};
            int here = 2;
            R0F(j, 19) {
                // cout << p << endl;
                if(leap1[p.f][j]==leap1[p.s][j]) continue;
                p.f=leap1[p.f][j];
                p.s=leap1[p.s][j];
                here+=2*(1<<j);
                if(p.s==-1) break;
            }
            if(p.s==-1) here--;
            where[i]={nxt[p.f], here};
        }
        F0R(i, n) {
            if(nxt[i]==-1) continue;
            int here = 3;
            pair<int,int> p = {i+1, nxt[i]};
            if(p.f==p.s) continue;
            R0F(j, 19) {
                if(leap1[p.f][j]==leap1[p.s][j]) {
                    continue;
                }
                p.f=leap1[p.f][j];
                p.s=leap1[p.s][j];
                here+=2*(1<<j);
                if(p.s==-1) break;
            }
            if(p.s==-1) here--;
            if(where[i].s==-1 || where[i].s>here) where[i]={nxt[p.f],here};
        }
        // cout << where << endl;
        vt<vt<pair<int,int>>> leap2(n, vt<pair<int,int>>(19));
        F0R(i, n) leap2[i][0]=where[i];
        FOR(i, 1, 19) {
            F0R(j, n) {
                if(leap2[j][i-1].f==-1) {
                    leap2[j][i]=leap2[j][i-1];
                } else {
                    leap2[j][i].f=leap2[leap2[j][i-1].f][i-1].f;
                    leap2[j][i].s=leap2[j][i-1].s+leap2[leap2[j][i-1].f][i-1].s;
                }
            }
        }
        // F0R(i, n) cout << leap2[i][1] << " ";
        // cout << endl;
        // return 0;
        // return 0;
        int q;
        cin >> q;
        while(q--) {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            if(l==r) {
                cout << 1 << endl;
                continue;
            }
            int ans = 0, cur = l;
            R0F(j, 19) {
                if(leap2[cur][j].f==-1 || leap2[cur][j].f>=r) continue;
                ans+=leap2[cur][j].s;
                cur=leap2[cur][j].f;
            }
            pair<int,int> p = {cur,cur+1};
            // cerr << p << ans << endl;
            // if(cur!=l) ans+=2;
            R0F(j, 19) {
                if(leap1[p.s][j]<=r && leap1[p.s][j]!=-1) {
                    ans+=2*(1<<j);
                    p.f=leap1[p.f][j];
                    p.s=leap1[p.s][j];
                }
            }
            if(nxt[p.f]!=-1 && nxt[p.f]<=r) {
                if(nxt[p.f]==p.s) {
                    if(nxt[p.f]+1<=r) ans++;
                } else {
                    ans++;
                }
            }
            if(p.f==p.s) ans--;
            // cerr << p << ans << endl;
            cout << ans+2 << endl;
        }
    }
    return 0;
}
/*
1
4 1
1 2 2 4
1
1 4

6
6
2
4
2
2
5
3
2
2
2
2
2
6
4
5
2
3
2
2

construct the leap table
leap[i][k] = where we are after 2^k leaps
now we leap two at a time

f[i] = how many leaps until i and i+1 go to same one
now I think we can leap again on f[i]?

12 15
4 5 15 24 27 32 36 39 40 46 48 48

15 24 32

15 24 32 40 48 ? 

4 5 24 27 40 46
*/