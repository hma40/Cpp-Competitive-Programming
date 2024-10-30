#include <bits/stdc++.h>
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
#define int long long
#define vt vector
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rand_num(int l, int h) {
    return rnd()%(h-l+1)+l;
}
struct TestCase {
    int n,k,mod;

};
void fill_rand(vt<int> &v, int lo, int hi) {
    for(auto &x: v) {
        x=rnd()%(hi-lo+1)+lo;
    }
}
void rand_tree(vt<vt<int>> &adj) {
    for(int i = 1; i < adj.size(); i++) {
        int par = rnd()%i;
        adj[par].add(i);
        adj[i].add(par);
    }
}
void print_TC(TestCase tc) {
	cout << tc.n << " " << tc.k << " " << tc.mod << endl;
}
TestCase randTC() {
    TestCase tc;
	tc.mod=998244353;
	tc.n=rand_num(1,3);
	tc.k=rand_num(1,5);
	tc.n=2;
	tc.k=5;
    return tc;
}
struct WrongSol {
    int solve(TestCase tc) {
       	int n,k;
        // cin >> n >> k >> mod;
		n=tc.n;
		k=tc.k;
        vt<int> pow2(501);
        pow2[0]=1;
        FOR(i, 1, 501) {
            pow2[i]=pow2[i-1]*2%mod;
        }   
        vt<vt<int>> pref(501, vt<int>(501));//pref[i][j] = number of ways to put i score or less in 2^j-1 nodes
        F0R(i, 501) pref[i][1]=i+1;
        F0R(i, 501) pref[0][i]=1;
        FOR(i, 1, 501) {
            FOR(j, 2, 501) {
                pref[i][j]=pref[i-1][j]*(pow2[j]-1)%mod+pref[i-1][j];
                pref[i][j]%=mod;
            }
        }
        // cout << pref[1][2] << endl;
        // cout << pref[1][1] << endl;
        vt<vt<int>> dp(n, vt<int>(k+1));
        dp[0][k]=1;
        FOR(layer, 1, n) {
            FOR(score, 1, k+1) {
                FOR(parscore, score, k+1) {
                    int maxother = min(parscore-score, score-1);
                    int layersLeft = n-layer;
                    dp[layer][score]+=dp[layer-1][parscore]*2*pref[maxother][layersLeft];
                    dp[layer][score]%=mod;
                }
            }
        }
        int ans = 0;
        // cout << dp << endl;
        F0R(score, k+1) ans = (ans+dp[n-1][score])%mod;
        // cout << ans << endl;
		return ans;
    }
};
struct CorrectSol {
	int binpow(ll a, ll b, ll p) {
  ll c = 1;
  while(b) {
    if (b & 1) c = c * a % p;
    a = a * a % p, b >>= 1;
  }
  return c;
}
    int solve(TestCase tc) {
    int n, k, p;
	n=tc.n;
	k=tc.k;
	p=mod;

    vector<ll> fac(k + 1, 1);
    for(int i = 1; i <= k; i++) fac[i] = fac[i - 1] * i % p;

    vector<ll> faci(k + 1);
    faci[k] = binpow(fac[k], p - 2, p);
    for(int i = k - 1; i >= 0; i--) faci[i] = faci[i + 1] * (i + 1) % p;

    vector<ll> pow2(n + 1, 1);
    for(int i = 1; i <= n; i++) pow2[i] = pow2[i - 1] * 2 % p;

    vector<ll> dp(k + 1, 1);
    for(int i = 1; i < n; i++) {
      vector<ll> binom(k + 1, 1);
      for(int j = 1; j <= k; j++) binom[j] = binom[j - 1] * (pow2[i] + j - 2 + p) % p;
      for(int j = 0; j <= k; j++) binom[j] = binom[j] * faci[j] % p;

      vector<ll> nxt(k + 1);
      for(int j = 0; j <= k; j++)
        for(int x = 0; x < j and j + x <= k; x++)
          nxt[j + x] = (nxt[j + x] + dp[j] * binom[x] % p) % p;

      for(int j = 1; j <= k; j++)
        nxt[j] = (nxt[j - 1] + nxt[j]) % p;
      dp.swap(nxt);
    }

    return dp[k] * pow2[n - 1] % p;

    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        WrongSol w;
        CorrectSol c;
        auto wa = w.solve(tc);
        auto cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}