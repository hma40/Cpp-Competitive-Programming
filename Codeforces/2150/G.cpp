#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
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
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop_front();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
const int N = 10005;
int NCK[N][N], pNCK[N][N];
#define int long long
#define vt vector
#define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// int N = 1e4+5;
vt<int> fact(N), invfact(N);
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
int nck(int n, int k) {
    if(n<k) return 0;
    if(n<0 || k<0) return 0;
    return NCK[n][k];
}
ll getv(ll x,ll y,ll k){
  if(min(x,y)<=-1){
    return 0ll;
  }
  if(max(x,y)>=k){
    return nck(x+y,x);
  }
  return nck(x+y,k);
}
int get2(int x, int y, int lnds_0, int lnds_1, int k) {
    if(lnds_1+y>=k) {
        return nck(x+y,y);
    }
    if(lnds_0+x>=k) {
        return nck(x+y,y);
    }

    if(lnds_1+y<k && lnds_0+x+y<k) {
        return 0;
    }
    int zz = k-lnds_0;
    return nck(x+y,zz);
}
int get_exactly(int x, int y, int lnds_0, int lnds_1, int k) {
    return get2(x,y,lnds_0,lnds_1,k)-get2(x,y,lnds_0,lnds_1,k+1);
}
int get_less(int x, int y, int lnds_0, int lnds_1, int k) {
    return nck(x+y,x)-get2(x,y,lnds_0,lnds_1,k);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    F0R(i, N) F0R(j, N) {
        if(j>i) NCK[i][j]=0;
        else if(j==0 || j==i) NCK[i][j]=1;
        else NCK[i][j]=(NCK[i-1][j-1]+NCK[i-1][j])%mod;
    }
    F0R(i, N) {
        pNCK[i][0]=0;
        F0R(j, N-1) {
            pNCK[i][j+1]=(pNCK[i][j]+NCK[i][j])%mod;
        }
    }
    auto sum_nck = [&](int n, int i, int j)->int{
        if(i>j) return 0ll;
        i=max(0LL,i);
        j=max(0LL,j);
        return (pNCK[n][j+1]-pNCK[n][i])%mod;
    };
    fact[0]=1;
    invfact[0]=1;
    FOR(i, 1, N) {
        fact[i]=fact[i-1]*i%mod;
        invfact[i]=bexpo(fact[i], mod-2);
    }
    int t;
    cin >> t;
    while(t--) {
        int x,y,k;
        cin >> x >> y >> k;
        string s;
        cin >> s;
        vt<int> lnds_0(x+y+1), lnds_1(x+y+1);
        F0R(i, x+y) {
            if(s[i]=='0') {
                lnds_0[i+1]=lnds_0[i]+1;
                lnds_1[i+1]=max(lnds_1[i], lnds_0[i+1]);
            } else {
                lnds_0[i+1]=lnds_0[i];
                lnds_1[i+1]=1+lnds_1[i];
            }
        }

        int ans = 0;
        int zl = x, ol = y;
        F0R(i, x+y) {    
            if(s[i]=='0') zl--;
            else ol--;
            if(lnds_1[i+1]==k) {
                int l_0 = 0, l_1 = 0;          
                FOR(j, i+1, x+y) {
                    if(s[j]=='0') {
                        l_1++;
                        ol--;
                        ans+=get2(zl, ol, l_0, l_1, k);
                        ol++;
                        zl--;
                        l_1--;
                        l_0++;
                        l_1=max(l_0, l_1);
                    } else {
                        l_1++;
                        ol--;
                    }
                }
                break;
            }

        }
        zl=x;
        ol=y;
        F0R(diff, x+y) {
            if(s[diff]=='1') {
                ol--;
                continue;
            }
            ol--;
            int l_0 = lnds_0[diff], l_1 = lnds_1[diff]+1;
            if(lnds_1[diff]>=k) {
                break;
            }
            if(l_1==k) {
                ans+=getv(zl,ol,k);
                ans%=mod;
            }
            if(l_1>k) break;
            FOR(eq_k, diff, x+y) {
                int positions = eq_k-diff;
                int zzz = k-l_0;
                int ooo = positions-zzz;
                ans+=get_less(zzz-1, ooo, l_0, l_1, k)*getv(zl-zzz, ol-ooo, k);
                ans%=mod;
                int zeroEnd = positions-(k-l_1)-1;
                auto calc_one = [&](int zeroes)->void{
                    int ones = positions-zeroes;
                    ans+=get_exactly(zeroes, ones-1, l_0, l_1, k-1)*getv(zl-zeroes, ol-ones, k);
                    ans%=mod;
                };
                zeroEnd=max(zeroEnd, -1LL);
                zeroEnd=max(zeroEnd, positions-ol-1);
                calc_one(zeroEnd+1);
                int zeroStart = k-l_0;
                zeroStart = min(zeroStart, zl+1);
                if(zeroEnd+2<zeroStart) calc_one(zeroStart-1);
                if(zeroEnd+2<zeroStart-1) {
                  // cout << endl;
                    int con = nck(positions-1, k-1-l_0)-nck(positions-1, k-l_0);
                    /*
                    need zl-zeroes>=0 and ol-ones>=0
                    zeroes<=zl
                    zeroes>=positions-ol

                    whats the condition for NCK(zl+ol-positions, k)?
                    if(max(x,y)>=k){
                        return nck(x+y,x);
                    }
                    so x>=k or y>=k
                    whats x and y here?
                    x is zl-zeroes
                    y is ol-ones
                    zl-zeroes>=k
                    or 
                    ol-ones>=k
                    ol-(positions-zeroes)>=k
                    ol-positions+zeroes>=k
                    zeroes>=k-ol+positoins
                    
                    if zeroes<=zl-k then return C(x+y,x)
                    if zeroes>=k-ol+positions then return C(x+y,x)

                    C(zl+ol-positions, zl-zeroes)
                    zero inc -> zl-zeroes dec
                    */
                    int bad_end = zl-k;
                    int bad_start = k-ol+positions;
                    // cout << zeroEnd+2 << " " << zeroStart-2 << " " << bad_end << " " << bad_start << endl;
                    if(bad_end>=zeroStart-2 || bad_start<=zeroEnd+2 || bad_end>bad_start) {
                        ans+=sum_nck(ol+zl-positions, zl-(zeroStart-2), zl-(zeroEnd+2))*con;
                        // cout << "OUT OF LOOP 0: " << sum_nck(ol+zl-positions, zl-(zeroStart-2), zl-(zeroEnd+2)) << endl;
                        ans%=mod;
                    } else {
                        bad_end = max(bad_end, zeroEnd+1);
                        bad_end = min(bad_end, zeroStart-2);
                        bad_start = min(bad_start, zeroStart-1);
                        bad_start = max(bad_start, zeroEnd+2);
                        ans+=sum_nck(ol+zl-positions, zl-bad_end, zl-zeroEnd-2)*con;
                        // cout << zl << " " << zl-bad_end << " " << zl-zeroEnd-2 << endl;
                        // cout << "OUT OF LOOP1: " << sum_nck(ol+zl-positions, zl-bad_end, zl-zeroEnd-2) << endl;
                        ans%=mod;
                        // cout << bad_start << " " << bad_end << " " << zeroEnd+2 << " " << zeroStart-1 << endl;
                        ans+=sum_nck(ol+zl-positions, zl-zeroStart+2, zl-bad_start)*con;
                        // cout << zl-zeroStart+1 << " " << zl-bad_start << endl;
                        // cout << "OUT OF LOOP2: " << sum_nck(ol+zl-positions, zl-zeroStart+2, zl-bad_start) << endl;
                        ans%=mod;
                        int kk = bad_start-bad_end-1;
                        ans+=con*nck(ol+zl-positions, k)%mod*kk%mod;
                        // cout << "OUT OF LOOP 3: " << kk << " " << nck(ol+zl-positions, k) << endl;
                        ans%=mod;
                    }
                }
                // FOR(zeroes, zeroEnd+2, zeroStart-1) {
                //     // cout << "IN LOOP: " << positions << " " << getv(zl-zeroes, ol-(positions-zeroes), k) << " " << zl+ol-positions << " " << k << endl;
                //     sum-=getv(zl-zeroes, ol-(positions-zeroes), k);
                //     // calc_one(zeroes);
                //     // sum-=calc_one(zeroes);
                //     // sum%=mod;
                //     // if(zeroes==zeroStart-2) cout << endl;
                // }
                // if(sum!=0) {
                //   cout << "PROBLEM DETECTED" << endl;
                //   cout << outOfLoop << endl;
                //   FOR(zeroes, zeroEnd+2, zeroStart-1) {
                //     cout << "IN LOOP: " << positions << " " << getv(zl-zeroes, ol-(positions-zeroes), k) << " " << zl+ol-positions << " " << k << endl;

                //     cout << "IN LOOP: " << calc_one(zeroes) << endl;

                //   }
                //   return 0;
                // }
                // calc_one(zeroStart-1);
            }
            // cout << endl;

            ol++;
            zl--;
        }
        ans%=mod;
        ans+=mod;
        ans%=mod;
        cout << ans << endl;
    }
    return 0;
}
/*
1
1 4 2
10000

11???
1x 0, 2x 1, 

10111
11011
11101
11110
*/