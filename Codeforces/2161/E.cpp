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
int bexpo(int b, int e) {
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
    const int N = 100005;
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> fact(N), ifact(N);
    fact[0]=ifact[0]=1;
    FOR(i, 1, N) {
        fact[i]=fact[i-1]*i%mod;
        ifact[i]=bexpo(fact[i], mod-2);
    }    
    auto nck = [&](int n, int k)->int{
        if(k<0 || k>n) return 0;
        return fact[n]*ifact[k]%mod*ifact[n-k]%mod;
    };  
    vt<vt<int32_t>> precomp(N);
    const int B = 300;
    int inv_2 = bexpo(2, mod-2);
    precomp[0].add(1);
    FOR(i, 1, N) {
        for(int j = 0; j < i; j+=B) {
            int bruh = precomp[i-1][j/B];
            //F(i-1, j)
           
            /*
            2B(l,r,n) = C(n,l)+C(n,r)-C(n+1,l)+B(l,r,n+1)
            when l=0
            2B(n,r) = C(n,r)+B(r,n+1)
            B(r,n+1)=2B(n,r)-C(n,r)
            */
            bruh*=2;
            bruh-=nck(i-1, j);
            bruh%=mod;
            bruh+=mod;
            bruh%=mod;
            precomp[i].add(bruh);
        }
        if(i%B==0) {
            precomp[i].add(bexpo(2, i));
        }
    }
    // cout << precomp << endl;
    // return 0;
    auto get_pref = [&](int n, int r)->int{
        if(r<0) return 0;
        int ans = 0;
        int nxt = 0;
        for(int j = 0; j <= r; j+=B) {
            ans=precomp[n][nxt];
            nxt++;
        }
        // cout << "LINE 156: " << ans << endl;
        // cout << ans << " " << r/B*B << endl;
        FOR(i, r/B*B+1, r+1) {
            // cout << i << endl;
            ans+=nck(n, i);
            ans%=mod;
        }
        return ans;
    };
    auto get_sum = [&](int n, int l, int r)->int{
        if(l>r) return 0;
        return get_pref(n,r)-get_pref(n,l-1);
    };
    // int a,b;
    // cin >> a >> b;
    // cout << get_pref(a,b) << endl;
    // cout << get_pref(9,5) << endl;
    // return 0;
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        string s;
        cin >> n >> k >> s;
		// if(k==1) {

		// }
        vt<bool> pz(n), po(n);
        if(s[0]=='0') pz[0]=true;
        else if(s[0]=='1') po[0]=true;
        FOR(i, 1, n) {
            if(s[i]=='0') pz[i]=true;
            if(s[i]=='1') po[i]=true;
            pz[i]=pz[i-1]||pz[i];
            po[i]=po[i]||po[i-1];
        }
        vt<int> ord(k-1, -1);
        bool bad = false;
        int ans = 0;
        int fzero = 0, fone = 0;
        // cout << pz << po << endl;
        if(!pz[n-1]) ans++;
        if(!po[n-1]) ans++;
        int tot = 0;
        // cout << "line 196 " << ans << endl;
        ROF(i, 1, n) {
			// cout << i << endl;
            tot++;
            tot=min(tot, k);

            if(s[i]=='0') {
                if(ord[i%(k-1)]==1) {
                    bad=true;
                } else if(ord[i%(k-1)]==-1) {
                    fzero++;
                }
                ord[i%(k-1)]=0;
            }
            if(s[i]=='1') {
                if(ord[i%(k-1)]==0) {
                    bad=true;
                } else if(ord[i%(k-1)]==-1) {
                    fone++;
                }
                ord[i%(k-1)]=1;
            }
            if(bad) break;
            if(tot<=k-1) {
                //fzero zeroes, fone ones
                if(!pz[i-1] && ord[i%(k-1)]!=1) {
                    //we can make prefix all 1's
                    //this one is zero
                    int nfzero = fzero;
                    if(ord[i%(k-1)]==-1) nfzero++;
                    //nfzero 0's, fone 1's
                    int unassigned = tot-fone-nfzero;
                    int max_ones = min(unassigned, k/2-nfzero);
                    // cout << "LINE 231 " << unassigned << " " << max_ones << endl;

                    ans+=get_sum(unassigned, 0, max_ones);
                }
                if(!po[i-1] && ord[i%(k-1)]!=0) {
                    //we can make prefix all 0's 
                    int nfone = fone;
                    if(ord[i%(k-1)]==-1) nfone++;
                    int unassigned = tot-fzero-nfone;
                    int max_ones = min(unassigned, k/2-nfone);
                    // cout << "LINE 231 " << unassigned << " " << k/2-nfone << " " << max_ones << endl;
                    ans+=get_sum(unassigned, 0, max_ones);
                }
                // ans+=
            } else {
                // cout << "GOT HERE" << endl;
                if(!pz[i-1] && ord[i%(k-1)]!=1) {
                    int nfzero = fzero;
                    if(ord[i%(k-1)]==-1) nfzero++;
                    //nfzero 0's, fone 1's
                    int unassigned = k-nfzero-fone-1;
                    int ones = k/2-fone;
                    ans+=nck(unassigned, ones);
                }
                if(!po[i-1] && ord[i%(k-1)]!=0) {
                    int nfone = fone;
                    if(ord[i%(k-1)]==-1) nfone++;
                    //nfzero 0's, fone 1's
                    int unassigned = k-nfone-fzero-1;
                    int ones = k/2-fzero;
                    ans+=nck(unassigned, ones);
                }
            }
            ans%=mod;
            //check how many 0 and 1
            // cout << i << " " << ans << " " << tot << endl;

        }
        cout << ans << endl;
    }
    return 0;
}
/*
000010
*/