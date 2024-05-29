#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
using ll = long long;
using pi = pair<int, int>;

ll factorials[200001];
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
ll combo(ll a, ll b, ll mod) {
    //cout << a << " " << b << endl;
    if(b>a) return 0;
    return factorials[a] * fastExp(factorials[b], mod-2, mod) % mod * fastExp(factorials[a-b], mod-2, mod) % mod;
}
int main() {
    ll mod = 1000000007;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll hm = 1;
    factorials[0]=1;
    for(int i = 1; i <= 200000; i++) {
        hm*=i;
        hm%=mod;
        factorials[i]=hm;
    }
    int t;
    cin >> t;
    string anss = "";
    for(;t>0;t--) {
        ll ans = 0;
        int n,m,k;
        cin >> n >> m >> k;
        vector<ll> numbers(n);
        for(int i = 0; i < n; i++) {
            cin >> numbers[i];
        }
        sort(begin(numbers), end(numbers));
        int left = 0; 
        int right = 0;
        
        //cout << "-----" << endl;
        while(left<numbers.size()) {
            while(right<numbers.size()) {

                if(numbers[right]-numbers[left]>k) {
                    break;
                }
                right++;
            }
            right--;
            left++;
            //cout << "about to call combo: " << left << " " << right << endl;
            ans+=combo(right-left+1, m-1, mod);
            ans%=mod;
        }
        anss+=to_string(ans)+"\n";
    }
    cout<<anss;
}