#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;
//vector<vector<int>> gc(8, vector<int>(300005));
vector<ll> factorial(300005);
vector<ll> invFactorial(300005);
vector<int> times(300005);
ll binExp(ll base, ll exp) {
    base%=mod;
    ll ans = 1;
    while(exp>0) {
        if(exp%2==1) {
            ans=ans*base%mod;
        }
        base=base*base%mod;
        exp/=2;
    }
    return ans;
}
ll combo(ll a, ll b) {
    if(a<b) return 0;
    return factorial[a]*invFactorial[b]%mod*invFactorial[a-b]%mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> arr(n);
    ll maxx = 0;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        maxx=max(maxx, arr[i]);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 1; j * j <= arr[i]; j++) {
            if(arr[i]%j==0) {
                times[j]++;
                if(j!=arr[i]/j) {
                    times[arr[i]/j]++;
                }
            }
        }
    }

    invFactorial[0]=factorial[0]=1;
    for(int i = 1; i <300005; i++) {
        factorial[i]=factorial[i-1]*i%mod;
        invFactorial[i]=binExp(factorial[i], mod-2);
    }
    //cout << "combo: " << combo(0,0) << endl;
    for(int i = 1; i < 8; i++) {
        vector<ll> gc(300005);
        //cout << i << endl;
        for(int j = 300005; j >= 1; j--) {
            ll temp = combo(times[j], i);
            //cout << i << " " << j << " " << times[j] << " " << temp << endl;
            for(int k = j*2; k <= 300005; k+=j) {
                temp=(temp-gc[k]+mod)%mod;
            }
            //cout << i << " " << j << " " << times[j] << " " << temp << endl;
            gc[j]=temp;
        }
        for(int a = 0; a < 17; a++) {
            //cout << a << " " << gc[a] << endl;
        }
        if(gc[1]>0) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}