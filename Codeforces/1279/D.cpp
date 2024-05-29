#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll gcd(ll a, ll b) {
    if(b>a) return gcd(b, a);
    if(a%b==0) return b;
    return gcd(b,a%b);
}
pair<ll, ll> simplify(pair<ll, ll> orig) {
    ll gcdd = gcd(orig.first, orig.second);
    orig.first/=gcdd;
    orig.second/=gcdd;
    return orig;
}
long long fastExp(long long a, long long b, long long mod) {
    long long remainder[31];
    remainder[0]=a;
    long long bruh = a;
    for(int i = 1; i <= 30; i++) {
        bruh*=bruh;
        //cout << i << " " << bruh << " ";
        bruh%=mod;
        //cout << bruh << endl;
        remainder[i]=bruh;
    }
    long long answ = 1;
    while(b>0) {
        int x = (int)(log(b)/log(2));
        answ *= remainder[x];
        answ%=mod;
        b -= 1 << x;
        //cout << b << " " << answ << endl;
    }
    return answ;
}
ll calcThing(pair<ll, ll> thing, ll mod) {
    return fastExp(thing.second, mod-2, mod) * thing.first % mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    ll mod = 998244353;
    int n;
    ll ans = 0;
    cin >> n;
    vector<vector<int>> children(n);
    int numPeopleWant[1000001] = {0};
    for(int t = 0; t < n; t++) {
        int ki;
        cin >> ki;
        for(int j = 0; j < ki; j++) {
            int temp;
            cin >> temp;
            numPeopleWant[temp]++;
            children[t].push_back(temp);
        }
    }
    //for(int i: numPeopleWant) cout << i << endl;
    for(const vector<int> &v: children) {
        for(const int &x: v) {
            pair<ll, ll> fraction;
            fraction.first=numPeopleWant[x];
            fraction.second = n * (ll)v.size() % mod * n % mod;
            //fraction = simplify(fraction);
            //cout << fraction.first << " " << fraction.second << endl;
            ans+=calcThing(fraction, mod);
            ans%=mod;
        }
    }
    cout << ans << endl;
}