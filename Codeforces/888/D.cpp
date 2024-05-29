#include <iostream>
#include <math.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll derangements[] = {1,0,1,2,9};    
ll factorials[1001];
long long fastExp(long long a, long long b, long long mod) {
    long long remainder[31];
    remainder[0]=a;
    long long bruh = a;
    for(int i = 1; i <= 30; i++) {
        bruh*=bruh;
        remainder[i]=bruh;
    }
    long long answ = 1;
    while(b>0) {
        int x = (int)(log(b)/log(2));
        answ *= remainder[x];
        b -= 1 << x;
        //cout << b << " " << answ << endl;
    }
    return answ;
}
ll combo(ll a, ll b, ll mod) {
    ll ans = 1;
    for(int i = 0; i < b; i++) {
        ans*=a-i;
    }
    for(int i = 1; i <= b; i++) {
        ans/=i;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    ll ans = 0;
    //cout << combo(5,3,mod);
    for(int i = 0; i <= k; i++) {
        ans += combo(n, i, 1) * derangements[i];
    }
    cout << ans;
}