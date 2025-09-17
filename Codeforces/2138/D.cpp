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
const ll mod = 1000000007;
ll inf = 1e18;
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    vt<int> fact(10005), ifact(10005);
    fact[0]=ifact[0]=1;
    FOR(i, 1, 10005) {
        fact[i]=fact[i-1]*i%mod;
        ifact[i]=bexpo(fact[i], mod-2);
    }
    auto nck = [&](int n, int k)->int{
        if(k<0 || k>n) return 0;
        return fact[n]*ifact[k]%mod*ifact[n-k]%mod;
    };
    while(t--) {
        int n,m,q;
        cin >> n >> m >> q;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<pair<int,int>> qu(q);
        F0R(i, q) {
            cin >> qu[i].f >> qu[i].s;
            qu[i].f--;
        }
        sort(begin(qu),end(qu));
        // auto getLess = [&](vt<int> &v, int what) -> int{
        //     return lower_bound(begin(v),end(v),what)-begin(v);
        // };
        // auto getMore = [&](vt<int> &v, int what)->int{
        //     /*
        //     1 2 3
        //     */
        //     return v.size()-(upper_bound(begin(v),end(v), what)-begin(v));
        // };
        // auto getEq = [&](vt<int> &v, int what) -> int{
        //     return v.size()-getLess(v,what)-getMore(v,what);
        // };
        F0R(i, n) {
            vt<int> chmax, chmin, seteq;
            bool good = false;
            F0R(j, q) {
                if(qu[j].f<i) {
                    chmax.add(i-qu[j].f+qu[j].s);
                    if(chmax.back()>a[i]) good=true;
                } else if(qu[j].f==i) {
                    seteq.add(qu[j].s);
                    good=true;
                } else {
                    chmin.add(qu[j].s-qu[j].f+i);
                    if(chmin.back()<a[i]) good=true;
                }
                // cout << "LINE 157: " << good << endl;
            }
            if(!good) {
                cout << fact[q]*a[i]%mod << " ";
                continue;
            }
            sort(begin(chmax),end(chmax));
            sort(begin(chmin),end(chmin));
            sort(begin(seteq),end(seteq));
            vt<array<int,9>> chmaxInfo, chminInfo, seteqInfo;
            int i0 = -1, i1 = -1, i2 = -1, i3 = -1, i4 = -1, i5 = -1;
            F0R(j, chmax.size()) {
                while(i0+1<chmax.size() && chmax[i0+1]<chmax[j]) {
                    i0++;
                }
                while(i1+1<chmax.size() && chmax[i1+1]<=chmax[j]) {
                    i1++;
                }
                while(i2+1<chmin.size() && chmin[i2+1]<chmax[j]) {
                    i2++;
                }
                while(i3+1<chmin.size() && chmin[i3+1]<=chmax[j]) {
                    i3++;
                }
                while(i4+1<seteq.size() && seteq[i4+1]<chmax[j]) {
                    i4++;
                }
                while(i5+1<seteq.size() && seteq[i5+1]<=chmax[j]) {
                    i5++;
                }
                array<int,9> temp = {i0+1, i1-i0, chmax.size()-i1-1, i2+1, i3-i2, chmin.size()-i3-1, i4+1, i5-i4, seteq.size()-i5-1};
                chmaxInfo.add(temp);
            }
            i0=i1=i2=i3=i4=i5=-1;
            F0R(j, chmin.size()) {
                while(i0+1<chmax.size() && chmax[i0+1]<chmin[j]) {
                    i0++;
                }
                while(i1+1<chmax.size() && chmax[i1+1]<=chmin[j]) {
                    i1++;
                }
                while(i2+1<chmin.size() && chmin[i2+1]<chmin[j]) {
                    i2++;
                }
                while(i3+1<chmin.size() && chmin[i3+1]<=chmin[j]) {
                    i3++;
                }
                while(i4+1<seteq.size() && seteq[i4+1]<chmin[j]) {
                    i4++;
                }
                while(i5+1<seteq.size() && seteq[i5+1]<=chmin[j]) {
                    i5++;
                }
                array<int,9> temp = {i0+1, i1-i0, chmax.size()-i1-1, i2+1, i3-i2, chmin.size()-i3-1, i4+1, i5-i4, seteq.size()-i5-1};
                chminInfo.add(temp);
            }
            i0=i1=i2=i3=i4=i5=-1;

            F0R(j, seteq.size()) {
                while(i0+1<chmax.size() && chmax[i0+1]<seteq[j]) {
                    i0++;
                }
                while(i1+1<chmax.size() && chmax[i1+1]<=seteq[j]) {
                    i1++;
                }
                while(i2+1<chmin.size() && chmin[i2+1]<seteq[j]) {
                    i2++;
                }
                while(i3+1<chmin.size() && chmin[i3+1]<=seteq[j]) {
                    i3++;
                }
                while(i4+1<seteq.size() && seteq[i4+1]<seteq[j]) {
                    i4++;
                }
                while(i5+1<seteq.size() && seteq[i5+1]<=seteq[j]) {
                    i5++;
                }
                array<int,9> temp = {i0+1, i1-i0, chmax.size()-i1-1, i2+1, i3-i2, chmin.size()-i3-1, i4+1, i5-i4, seteq.size()-i5-1};
                seteqInfo.add(temp);
            }            
            // cout << chmax << " " << chmin << " " << seteq << seteqInfo << endl;
            /*
            say we want chmax(x) to be the last useful one
            what are requirements?
            
            group 2: chmax(<x)
            group 3: chmin(>x) 
            group 1: chmax(>x) / seteq(>x)
            group 4: chmin(<=x) / seteq(<=x) 
            group 5: other chmax(x)
            
            rules
            - last of group 1 must come last of group 4
            - last of group 4 must come before chmax(x)
            - group 2 and 3 can be wherever they want
            - group 5: must come before chmax(x), but other than that no restrictions
            so say we have a[1],a[2],a[3],a[4],a[5] of these 5 groups
            
            - choose a member of group 4 to be the last one. The other a[1]+a[4]-1 can be permuted in any way (a[1]+a[4]-1)! * a[4]
            - now we have a[5]! * C(a[5]+a[1]+a[4], a[5]) to place a[5]
            - then place our chmax(x)
            - then we have C(q, a[2]+a[3])*(a[2]+a[3])!
            */
            int ans = 0;
            int ans2 = 0;
            F0R(j, seteq.size()) {
                int anywhere = seteqInfo[j][5]+seteqInfo[j][0];
                int before = q-1-anywhere;
                int here2 = fact[before]%mod*fact[anywhere]%mod*nck(q, anywhere)%mod;
                ans2+=here2;
                ans+=here2*seteq[j];
                ans%=mod;
                ans2%=mod;

            }
            F0R(j, chmax.size()) {
                int x = chmax[j];
                int g1 = chmaxInfo[j][2]+chmaxInfo[j][8];
                int g23 = chmaxInfo[j][0]+chmaxInfo[j][5];//getLess(chmax, x)+getMore(chmin, x);
                int g5 = chmaxInfo[j][1]-1;
                int g4 = q-1-g1-g23-g5;
                if(g4==0) {
                    if(g1==0) {
                        if(x<a[i]) continue;
                        int here2 = fact[g5];
                        here2*=nck(q, g23);
                        here2%=mod;
                        here2*=fact[g23];
                        here2%=mod;
                        ans2+=here2;
                        ans2%=mod;
                        ans+=here2*x;
                        ans%=mod;
                        continue;
                    } else {
                        continue;
                    }
                }
                int here2 = g4*fact[g1+g4-1]%mod;
                here2*=fact[g5];
                here2%=mod;
                here2*=nck(g5+g1+g4, g5);
                here2%=mod;
                here2*=nck(q, g23);
                here2%=mod;
                here2*=fact[g23];
                here2%=mod;
                ans2+=here2;
                ans2%=mod;
                ans+=here2*x;
                ans%=mod; 
                // cout << "LINE 230: " << x << " " << ans2 << endl;
            }
            /*
            say we want chmax(x) to be the last useful one
            what are requirements?
            
            group 2: chmax(<x)
            group 3: chmin(>x) 
            group 4: chmax(>=x) / seteq(>=x)
            group 1: chmin(<x) / seteq(<x) 
            group 5: other chmin(x)
            
            rules
            - last of group 1 must come last of group 4
            - last of group 4 must come before chmax(x)
            - group 2 and 3 can be wherever they want
            - group 5: must come before chmax(x), but other than that no restrictions
            so say we have a[1],a[2],a[3],a[4],a[5] of these 5 groups
            
            - choose a member of group 4 to be the last one. The other a[1]+a[4]-1 can be permuted in any way (a[1]+a[4]-1)! * a[4]
            - now we have a[5]! * C(a[5]+a[1]+a[4], a[5]) to place a[5]
            - then place our chmax(x)
            - then we have C(q, a[2]+a[3])*(a[2]+a[3])!
            */
            F0R(j, chmin.size()) {
                int x = chmin[j];
                int g1 = chminInfo[j][3]+chminInfo[j][6];//getLess(chmin, x)+getLess(seteq, x);
                int g23 = chminInfo[j][0]+chminInfo[j][5];//getLess(chmax, x)+getMore(chmin, x);
                int g5 = chminInfo[j][4]-1;//getEq(chmin, x)-1;
                int g4 = q-1-g1-g23-g5;
                // cout << x << " " << g1 << " " << g23 << " " << g4 << " " << g5 << endl;
                if(g4==0) {
                    if(g1==0) {
                        if(x>a[i]) continue;
                        int here2 = fact[g5];
                        here2*=nck(q, g23);
                        here2%=mod;
                        here2*=fact[g23];
                        here2%=mod;
                        ans2+=here2;
                        ans2%=mod;
                        ans+=here2*x;
                        ans%=mod;
                        continue;
                    } else {
                        continue;
                    }
                }
                int here2 = g4*fact[g1+g4-1]%mod;
                here2*=fact[g5];
                here2%=mod;
                here2*=nck(g5+g1+g4, g5);
                here2%=mod;
                here2*=nck(q, g23);
                here2%=mod;
                here2*=fact[g23];
                here2%=mod;
                ans2+=here2;
                ans2%=mod;
                ans+=here2*x;
                ans%=mod; 
                // cout << "LINE 290: " << x << " " << ans2 << endl;
            }            // cout << i << " " << chmax << " " << seteq << " " << chmin << endl;
            // assert(ans2==fact[q]);
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}