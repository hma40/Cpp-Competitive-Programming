#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, mod;
ll permut[7550][7550];
unordered_map<ll, ll> prod;
vector<ll> primes;
void generate_primes() {
    vector<bool> notPrime(7501);
    for(int i = 2; i <= 7500; i++) {
        if(notPrime[i]) continue;
        primes.push_back(i);
        for(int j = i*i; j <= 7500; j+=i) notPrime[j]=true;
    }
}
ll binExp(ll base, ll exp) {
    ll ans = 1;
    while(exp>0) {
        if(exp%2==1) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        exp/=2;
    }
    return ans;
}
ll count(ll number) {
    vector<ll> arr(n/number+1);
    arr[0]=-1;
    for(int i = 1; i <= n/number; i++) {
        for(int j = 1; j <= i; j++) {
            ll change = permut[i*number-1][j*number-1] * arr[i-j] % (mod-1);
            arr[i]-=change;
            arr[i]%=mod-1;
            //cout << i << " " << j << " " << change << " " << arr[i] << endl;
            if(arr[i]<0) arr[i]+=mod-1;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n/number; i++) {
        ans+=permut[n][n-i*number] * arr[i];
        ans%=mod-1;
    }
    return ans;
}
int main() {
    generate_primes();
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    cin >> n >> mod;
    for(int i = 1; i < 7550; i++) {
        for(int j = 0; j <= i; j++) {
            if(j==0){
                permut[i][j]=1;
            } else {
                permut[i][j]=permut[i][j-1]*(i-j+1);
                permut[i][j]%=mod-1;
            }
        } 
    }
    for(ll prime: primes) {
        //cout << prime << endl;
        if(prime>n) break;
        ll primePower = prime;
        while(primePower<=n) {
            prod[prime]+=count(primePower);
            //cout << primePower << " " << count(primePower) << endl;
            primePower*=prime;
        }
    }
    ll final_ans = 1;
    for(pair<ll, ll> p: prod) {
        //cout << p.first << " " << p.second << endl;
        final_ans*=binExp(p.first, p.second);
        final_ans%=mod;
    }
    cout << final_ans << endl;
}