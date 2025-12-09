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
    vt<int> fact(5005), ifact(5005);
    fact[0]=ifact[0]=1;
    FOR(i, 1, 5005) {
        fact[i]=fact[i-1]*i%mod;
        ifact[i]=bexpo(fact[i], mod-2);
    }
    auto nck = [&](int n, int k)->int{
        if(k<0 || k>n) return 0;
        return fact[n]*ifact[k]%mod*ifact[n-k]%mod;
    };
    int t;
    cin >> t;
    
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> chil(n);
        FOR(i, 1, n) {
            int p;
            cin >> p;
            p--;
            chil[p].add(i);
        }
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> ord;
        ord.add(0);
        vt<vt<int>> adj(n);
        // cout << chil << endl;
        auto dfs = [&](auto self, int node)->void{
            // cout << node << " " << ord << endl;
            trav(x, chil[node]) {
                // cout << "line 121: " << node << " " << x << endl;
                ord.insert(ord.begin()+a[x], x);
                if(a[x]==0) {
                    adj[x].add(ord[1]);
                } else if(a[x]+1==ord.size()) {
                    adj[ord[ord.size()-2]].add(x);
                } else if(find(begin(adj[ord[a[x]-1]]), end(adj[ord[a[x]-1]]), ord[a[x]+1])!=adj[ord[a[x]-1]].end()) {
                    adj[ord[a[x]-1]].erase(find(begin(adj[ord[a[x]-1]]), end(adj[ord[a[x]-1]]), ord[a[x]+1]));
                    adj[ord[a[x]-1]].add(x);
                    adj[x].add(ord[a[x]+1]);
                } else {
                    adj[ord[a[x]-1]].add(x);
                    adj[x].add(ord[a[x]+1]);
                }
                self(self,x);
                ord.erase(find(begin(ord),end(ord),x));
            }
        };
        dfs(dfs,0);
        // cout << adj << endl;
        vt<vt<bool>> reach(n, vt<bool>(n));
        F0R(i, n) {
            deque<int> dq;
            dq.add(i);
            reach[i][i]=true;
            while(dq.size()) {
                auto tp = dq.front();
                dq.pop_front();
                trav(x, adj[tp]) {
                    if(reach[i][x]) continue;
                    reach[i][x]=true;
                    dq.add(x);
                }
            }
        }
        // deque<int> dq;
        // int ans = 1;
        vt<vt<int>> invadj(n);
        F0R(i, n) trav(x, adj[i]) invadj[x].add(i);
        auto solve = [&](auto self, vt<bool> consider)->int{
            // cout << "line 179: " << consider << endl;
            int count = 0;
            F0R(i, n) if(consider[i]) count++;
            if(count==0) {
                // cout << "line 183: returning 1 for " << consider << endl;
                return 1;
            }
            int ans = 1;
            vt<int> in(n);
            F0R(i, n) if(consider[i]) trav(x, adj[i]) if(consider[x]) in[x]++;
            vt<int> beg;
            F0R(i, n) if(consider[i] && in[i]==0) beg.add(i);
            // cout << consider << beg << endl;
            vt<bool> after = consider;
            if(beg.size()==1) {
                after[beg[0]]=false;
                int bruh = self(self, after);
                // cout << "line 191: returning " << bruh << " for " << consider << endl;
                return bruh;
            }
            vt<bool> bad(n);
            F0R(i, n) {
                if(!consider[i]) continue;
                bool ok = true;
                trav(x, beg) if(!reach[x][i]) {
                    ok=false;
                    break;
                }
                if(ok) bad[i]=true;
            }
            deque<int> dq;
            vt<bool> nConsider(n);
            vt<int> sizes;
            int sum = 0;
            trav(x, beg) {
                if(!consider[x] || !after[x]) continue;

                int size = 0;
                // deque<int> dq;
                dq.add(x);
                // cout << "line 221: " << x << endl;
                vt<int> her;
                nConsider[x]=true;
                while(dq.size()) {
                    auto tp = dq.front();
                    dq.pop_front();
                    // nConsider[tp]=true;
                    size++;
                    her.add(tp);
                    after[tp]=false;
                    trav(xx, invadj[tp]) {
                        if(!consider[xx] || nConsider[xx]) continue;
                        
                        nConsider[xx]=true;
                        dq.add(xx);
                    }
                    trav(xx, adj[tp]) {
                        if(bad[xx] || !after[xx] || !consider[xx] || nConsider[xx]) continue;
                        nConsider[xx]=true;
                        dq.add(xx);
                    }
                }
                size = her.size();
                sizes.add(size);
                sum+=size;
                // cout << "line 238: " << consider << " " << nConsider << her << endl;
                ans*=self(self, nConsider);
                ans%=mod;
                trav(xx, her) nConsider[xx]=false;
            }
            // cout << "line 245: " << consider << sizes << " " << endl;
            // cout << "line 236: " << consider << " " << after << endl;
            ans*=self(self, after);
            ans%=mod;
            // cout << "line 239: " << consider << sum << " " << ans << " " << sizes << endl;
            trav(x, sizes) {
                ans*=nck(sum, x);
                sum-=x;
                ans%=mod;
            }
            // cout << "line 241: returning " << ans << " for " << consider << endl;
            return ans;
        };
        vt<bool> consider(n,1);
        cout << solve(solve, consider) << endl;
    }
    return 0;
}
/*
1
4
1 2 2
0 1 1 1

1
5
1 2 2 1
0 0 1 1 0

5
1 1 3 3 
0 0 0 0 0 

1
8
1 2 1 1 4 3 3 
0 1 2 1 1 1 2 2 

*/