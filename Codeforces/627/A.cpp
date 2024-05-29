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
ll mod = 1000000007;
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
void printArray(vector<int> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
void printArray(vector<ll> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    ll sum, xr;
    cin >> sum >> xr;
    ll ans = 1;
    ll diff = sum-xr;
    if(diff%2==1) {
        cout << 0 << endl;
        return 0;
    }
    diff/=2;
    ll bitCount=0;
    ll xxr = xr;
    while(xxr) {
        bitCount++;
        xxr-=xxr&-xxr;
    }
    if(diff==0) {
        cout << ((ll)1<<bitCount)-2 << endl;
        return 0;
    }
    while(diff) {
        ll temp = diff&-diff;
        //cout << diff << " " << temp << endl;
        if(xr&temp) {
            cout << 0 << endl;
            return 0;
        }
        diff-=temp;
    }
    cout << ((ll)1<<bitCount) << endl;
    return 0;
}