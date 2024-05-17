#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 1000000007;
ll binExp(ll base, ll exp) {
    if(exp==-1) return 0;
    ll ans = 1;
    while(exp) {
        if(exp%2) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        exp/=2;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int d;
    cin >> d;
    ll ans = 0;
    set<tuple<int, ll, ll>> demands;
    demands.insert({0,0,0});
    demands.insert({1e7,0,0});
    string an = "";
    FOR(i, 0, d) {
        int m;
        ll b;
        cin >> m >> b;
        tuple<int,ll,ll> here = {m,b,0};
        auto itt = demands.upper_bound(here);
        auto it=prev(itt);
        ll afterTime = get<0>(*itt)-get<0>(*it);
        ll afterWork = get<1>(*itt)-get<1>(*it);
        ll herTime = m-get<0>(*it);
        ll herWork = b-get<1>(*it);
        if(get<0>(*itt)!=1e7&&herWork*afterTime<=herTime*afterWork) {
            cout << ans << '\n';
            continue;
        }
        if(it!=demands.begin()) {
            if(get<1>(*it)>=b) {
                cout << ans << '\n';
                continue;
            }
        }
        vector<tuple<int, ll, ll>> del;
        for(auto it2 = itt; get<0>(*it2)!=1e7; it2++) {
            auto it2t = *it2;
            if(get<1>(here)>=get<1>(it2t)) {
                del.add(it2t);
                continue;
            }
            auto after = *next(it2);
            if(get<0>(after)==1e7) break;
            ll time2 = get<0>(it2t)-m;
            ll work2 = get<1>(it2t)-b;
            ll timeHere = get<0>(after)-m;
            ll workHere = get<1>(after)-b;
            if(time2*workHere>=timeHere*work2) {
                del.add(it2t);
            }
        }
        for(auto it2 = it; it2!=demands.begin(); it2--) {
            auto bef = *prev(it2);
            auto it2t = *it2;
            ll time2 = get<0>(it2t)-get<0>(bef);
            ll work2 = get<1>(it2t)-get<1>(bef);
            ll timeHere = m-get<0>(bef);
            ll workHere = b-get<1>(bef);
            if(time2*workHere>=timeHere*work2) {
                del.add(it2t);
            } else {
                break;
            }
        }
        for(auto r: del) {
            demands.erase(r);
            ans-=get<2>(r);
        }
        auto aft = demands.upper_bound(here);
        auto after = *aft;
        auto before = *--aft;
        if(get<0>(after)!=1e7) {
            demands.erase(after);
            ans-=get<2>(after);
            ll time = get<0>(after)-m;
            ll work = get<1>(after)-b;
            if(work%time==0) {
                ll each = binExp(3, work/time-1);
                each*=time;
                each%=mod;
                get<2>(after)=each;
                ans+=each;
            } else {
                ll each0 = binExp(3, work/time-1);
                ll each1 = binExp(3, work/time);
                ll need1 = work%time;
                ll need0 = time-need1;
                ll invest = each0*need0+each1*need1;
                invest%=mod;
                get<2>(after)=invest;
                ans+=invest;
            }
            demands.insert(after);
        }
        ll time = m-get<0>(before);
        ll work = b-get<1>(before);
        if(work%time==0) {
            ll each = binExp(3, work/time-1);
            each*=time;
            each%=mod;
            demands.insert({m,b,each});
            ans+=each;
        } else {
            ll each0 = binExp(3, work/time-1);
            ll each1 = binExp(3, work/time);
            ll need1 = work%time;
            ll need0 = time-need1;
            ll invest = each0*need0+each1*need1;
            invest%=mod;
            demands.insert({m,b,invest});
            ans+=invest;
        }
        ans%=mod;
        ans+=mod;
        ans%=mod;
        cout << ans << '\n';
    }
    return 0;
}