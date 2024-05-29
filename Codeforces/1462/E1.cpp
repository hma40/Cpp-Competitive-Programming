#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
ll factorials[200001];
long long fastExp(long long a, long long b, long long mod) {
    long long remainder[31];
    remainder[0]=a;
    long long bruh = a;
    for(ll i = 1; i <= 30; i++) {
        bruh*=bruh;
        //cout << i << " " << bruh << " ";
        bruh%=mod;
        //cout << bruh << endl;
        remainder[i]=bruh;
    }
    long long answ = 1;
    while(b>0) {
        ll x = (ll)(log(b)/log(2));
        answ *= remainder[x];
        answ%=mod;
        b -= 1 << x;
        //cout << b << " " << answ << endl;
    }
    return answ;
}
signed main() {
    ll mod = 1000000007;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll hm = 1;
    factorials[0]=1;
    for(ll i = 1; i <= 200000; i++) {
        hm*=i;
        hm%=mod;
        factorials[i]=hm;
    }
    ll t;
    cin >> t;
    string anss = "";
    for(;t>0;t--) {
        ll ans = 0;
        ll n,m,k;
        cin >> n;
        m=3;
        k=2;
        vector<ll> numbers(n);
        for(ll i = 0; i < n; i++) {
            cin >> numbers[i];
        }
        sort(begin(numbers), end(numbers));
        ll left = 0; 
        ll right = 0;
        
        //cout << "-----" << endl;
        ll sz = numbers.size();
        while(left<sz) {
            while(right<sz) {

                if(numbers[right]-numbers[left]>k) {
                    break;
                }
                right++;
            }
            right--;
            left++;
            ans+=(right-left+1)*(right-left)/2;
        }
        anss+=to_string(ans)+"\n";
    }
    cout<<anss;
}