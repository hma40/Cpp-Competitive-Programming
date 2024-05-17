//c++ sucks ig
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;    
ll factorial[1100000];
ll invFactorial[1100000];
ll binExp(ll base, ll expo) {
    ll binExps[33];
    binExps[0]=base;
    for(int i = 1; i < 33; i++) {
        binExps[i]=binExps[i-1]*binExps[i-1]%mod;
    }
    ll result = 1;
    while(expo>0) {
        int temp = log(expo)/log(2);
        expo-=1<<temp;
        result*=binExps[temp];
        result%=mod;
    }
    return result;
}
ll choose(ll a, ll b) {
    return factorial[a] * invFactorial[b] % mod * invFactorial[a-b] % mod;
}
int main() {
    factorial[0]=invFactorial[0]=factorial[1]=invFactorial[1]=1;
    for(int i = 2; i < 1100000; i++) {
        factorial[i]=factorial[i-1]*i%mod;
        invFactorial[i]=binExp(factorial[i], mod-2);
        if(i%10000==0) cout << i << endl;
    }
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    int first, last;
    cin >> first;
    ll ans = 1;
    for(int i = 1; i < n; i++) {
        cin >> last;
        first/=2;
        last/=2;
        if(last>first) {
            ans*=choose(last-1, first-1);
        } else {
            ans*=choose(first, last);
        }
        ans%=mod;
        first=last*2;
    }
    cout << ans << endl;
}