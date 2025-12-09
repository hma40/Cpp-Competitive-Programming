
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
#define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
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
#define Z long long
const int MOD = 998244353;
Z power(Z base, long long exp) {
    Z res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (1LL * res * base) % MOD;
        base = (1LL * base * base) % MOD;
        exp /= 2;
    }
    return res;
}
 
Z modInverse(Z n) {
    return power(n, MOD - 2);
}

const int MAX_FACT = 1000005;
Z fact[MAX_FACT];
Z invFact[MAX_FACT];
int MAX = 1000005;
void precompute_factorials(int max_val) {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= max_val; i++) {
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}
 
int nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (((1LL * fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
}
int solve_good(vt<int> &a, vt<int> &pos, int suf) {
    int n = a.size();
    int lnext = suf, hnext = a[pos[0]]+1, ans=1;
    FOR(i, 1, pos.size()) {
        // cout << pos[i] << " " << lnext << " " << hnext << " " << ans << endl;
        int free = pos[i]-pos[i-1]-1;
        if(a[pos[i]]>a[pos[0]] && a[pos[i]]<hnext) {
            ans=0;
        } else if(a[pos[i]]<lnext) {
            ans=0;
        } else if(a[pos[i]]>a[pos[0]]) {
            int up = a[pos[i]]-hnext;
            ans*=nCr_mod_p(free, up);
            ans%=mod;
            hnext=a[pos[i]]+1;
            lnext+=free-up;
        } else {
            int up = a[pos[i]]-lnext;
            // cout << free << " " << up << endl;
            ans*=nCr_mod_p(free, up);
            lnext=a[pos[i]]+1;
            hnext+=free-up;
        }
        ans%=mod;
    }
    ans*=nCr_mod_p(n-hnext+a[pos[0]]-lnext, a[pos[0]]-lnext);
    ans%=mod;
    return ans;
}
int solve(vector<int> &a_vec,
          const vector<int> &b_vec,
          int L,
          int R) {
                int n = (int)a_vec.size();
 
    Z min_diff = LLONG_MAX, max_neg_b = LLONG_MIN;
 
    for (int i = 0; i < n; i++) {
        Z diff = (Z)a_vec[i] - b_vec[i];
        min_diff = min(min_diff, diff);
        max_neg_b = max(max_neg_b, -(Z)b_vec[i]);
    }
    Z eff_l = max((Z)L, max_neg_b);
    Z eff_r = min((Z)R, min_diff);
    if (eff_l > eff_r) return 0;
    swap(L,eff_l);
    swap(R, eff_r);
        cerr << "LINE 291: " << a_vec.size() << " " <<R-L+1 << endl;
        assert((int)a_vec.size()*(R-L+1)<=MAX);
    int an = 0;
    for(int i = L; i <= R; i++) {
        int here = 1;
        for(int j = 0; j < a_vec.size(); j++) {
            here*=nCr_mod_p(a_vec[j], b_vec[j]+i);
            here%=MOD;
        }
        an+=here;
        an%=MOD;
    }
    return an;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    precompute_factorials(1000005);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        MAX=n;
        vt<int> pos;
        vt<int> a(n);
        vt<int> reg;
        F0R(i, n) reg.add(i);
        vt<bool> used(n+1);
        F0R(i, n) {
            cin >> a[i];
            if(a[i]!=-1) a[i]--;
            if(a[i]!=-1) used[a[i]]=1;
            if(a[i]!=-1) pos.add(i);
        }
        bool REG_OK = true;
        F0R(i, n) {
            if(a[i]!=-1 && a[i]!=reg[i]) {
                REG_OK=false;
            }
        }
        if(REG_OK) {
            int ans = 1;
            int prev = 0;
            trav(x, pos) {
                ans+=bexpo(2, x-prev)-(x-prev+1);
                ans%=mod;
                prev=x+1;
            }
            ans+=bexpo(2, n-prev)-(n-prev+1);
            cout << ans%mod << enld;
            continue;
        }
        int till = -1;
        while(till<n-1) {
            if(a[till+1]!=-1 && a[till+1]!=till+1) {
                break;
            } else if(a[till+1]==till+1) {
                till++;
            } else if(used[till+1]) {
                break;
            } else {
                till++;
            }
        }
        int ans = 1;
        int suf = 0;
        trav(x, pos) {
            if(a[x]!=x) {
                break;
            }
            suf=x+1;
        }   
        reverse(begin(pos),end(pos));
        while(pos.size() && pos.back()<=suf-1) pos.pop_back();
        reverse(begin(pos),end(pos));
        if(pos.size()==0) {
            ans*=bexpo(2, n-suf)-(n-suf);
            ans%=mod;
            cout << ans << enld;
            continue;
        }
        // cout << pos << enld;
        // cout << ans << " " << suf << endl;
        if(pos[0]==suf) {

            cout << ans*solve_good(a, pos, suf)%mod << endl;
            continue;
        } else {
            auto CPY = a;
            F0R(i, pos[0]) CPY[i]=i;
            int tot = solve_good(CPY, pos, pos[0]);
            int lb = 0, ub = n-1;
            trav(x, pos) {
                if(a[x]==x) {
                    ub=min(ub,x-1);
                } else if(a[x]>x) {
                    ub=min(ub,a[x]-1);
                } else {
                    lb=max(lb,a[x]+1);
                }
            }
            // cerr << lb << " " << ub << enld;
            // cout << "LINE 263 " << ans << " " << tot << endl;
            vector<int> aa, bb;
            int all = 1;
            pair<int,int> low_line = {0,suf};
            pair<int,int> high_line = {1,0};
            trav(x, pos) {
                int free = x-suf;
                // cerr << "LINE 551: " << x << low_line << high_line << endl;
                if(a[x]>ub) {
                    /*
                    currently next high = high_line.f * a[0] + high_line.s
                    want to get it up to a[x]-1
                    a[x]-hl.f*a[0]-hl.s
                    so we have C(free, a[x]-x0-hl.s)
                    same as C(free, free-a[x]+x0+hl.s)

                    want to go from x0 to 4
                    so choosing 4-x0+1 numbers
                    C(free, 5-x)
                    C(free, a[x]-x0+1)
                    C(free, free-a[x]+x0-1)
                    */
                    if(high_line.f==1) {
                        bb.add(free-a[x]+high_line.s);
                        /*
                        giving a[x]-x0-hl.s to second
                        so free-a[x]+x0+hl.s to first
                        */
                                           aa.add(free);

                        low_line.f=1;
                        low_line.s+=free-a[x]+high_line.s;
                        high_line.f=0;
                        high_line.s=a[x]+1;
                    } else {
                        all*=nCr_mod_p(free, a[x]-high_line.s);
                        low_line.s+=free-a[x]+high_line.s;
                        high_line.s=a[x]+1;
                    }

                } else {
                    // assert(a[x]<lb);
                    /*
                    currently next high = high_line.f * a[0] + high_line.s
                    want to get it up to a[x]-1
                    a[x]-hl.f*a[0]-hl.s
                    so we have C(free, a[x]-x0-hl.s)
                    same as C(free, free-a[x]+x0+hl.s)
                    */
                    if(low_line.f==1) {
                        /*
                        C(10, 10-2+x-6-1)
                        C(free, free-(a[x]-1)+x)
                        */
                        bb.add(free-a[x]+low_line.s);
                        /*
                        giving a[x]-x0-hl.s to second
                        so free-a[x]+x0+hl.s to first
                        */
                        aa.add(free);

                        high_line.f=1;
                        high_line.s+=free-a[x]+low_line.s;
                        low_line.f=0;
                        low_line.s=a[x]+1;
                    } else {
                        all*=nCr_mod_p(free, a[x]-low_line.s);
                        high_line.s+=free-a[x]+low_line.s;
                        low_line.s=a[x]+1;
                    }

                }
                suf=x+1;
                all%=mod;
            }
            /*
            at the end, we want high to be n-1

            */
            // cerr << low_line << high_line << all << endl;
            /*
            
            */
            int free = n-suf;
            if(high_line.f==1) {
                bb.add(free-n+high_line.s);
                /*
                giving a[x]-x0-hl.s to second
                so free-a[x]+x0+hl.s to first
                */
                                    aa.add(free);

                low_line.f=1;
                // low_line.s+=free-a[x]+high_line.s;
                high_line.f=0;
                // high_line.s=a[x]+1;
            } else {
                all*=nCr_mod_p(free, n-high_line.s);
                // low_line.s+=free-a[x]+high_line.s;
                // high_line.s=a[x]+1;
            }
            all%=mod;
            // cout << aa << bb << all << endl;
            int OUT = (tot+solve(aa, bb, lb, ub)*all)%mod;
            OUT%=mod;
            cout << OUT << endl;
        }
    }
    return 0;
}
/*
-1 4 -1 -1 -1 -1
if a[0]=3: C(1,0)
if a[0]=4: C(1,1) (but not possible)

1
20
-1 -1 -1 -1 11 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 4 -1 -1 -1 -1 
-1 -1 -1 -1 10 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 3 -1 -1 -1 -1 

C(4, 9-x0+1) = C(4, 4-9-1+x0)
now:
high = 11
low = x-6
want to bring it up to 2
2-x+6+1 = 2-x+6+1
C(10, 2-x+6+1
C(10, 10-2+x-6-1)

6 7 8 9 10 0 1 2 11 12 13 14 15 16 17 3 18 19 4 5
7 8 9 0 10 1 2 

C(4, 2)*C(1, 0)*C(3,0) = 6
C(4,3) * C(1,1) * C(3, 1) = 12
*/