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
ll mod = 998244353;
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
vector<ll> factorials(200000);
vector<ll> invFactorials(200000);
ll binomExpo(ll base, ll power) {
    ll ans = 1;
    while(power>0) {
        if(power%2) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        power/=2;
    }
    return ans;
}
ll combo(ll a, ll b) {
    return factorials[a]*invFactorials[b]%mod*invFactorials[a-b]%mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    factorials[0]=1;
    invFactorials[0]=1;
    FOR(i, 1, 200000) {
        factorials[i]=factorials[i-1]*i%mod;
        invFactorials[i]=binomExpo(factorials[i], mod-2);
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> answers(n+1);
        FOR(i, 2, n+1) {
            if(n-2*i+3<0||n-i-1<i-2) break;
            answers[i]=combo(n-i-1, i-2)*factorials[2*i-2]%mod*factorials[n-2*i+3]%mod;
        }
        cout << answers[1];
        FOR(i, 2, n+1) {
            cout << " " << answers[i];
        }
        cout << endl;
    }

    return 0;
}