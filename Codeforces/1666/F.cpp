#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll factorials[6001];
ll inverseFactorials[6001];
long long fastExp(long long a, long long b, long long mod) {
    long long power[31];
    power[0]=a;
    long long number = a;
    for(int i = 1; i <= 30; i++) {
        number*=number;
        number%=mod;
        power[i]=number;
    }
    long long answ = 1;
    while(b>0) {
        int x = (int)(log(b)/log(2));
        answ *= power[x];
        answ%=mod;
        b -= 1 << x;
    }
    return answ;
}
ll combo(ll a, ll b, ll mod) {
    if(a<b) return 0;
    return factorials[a] * inverseFactorials[b] % mod * inverseFactorials[a-b] % mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll mod = 998244353;
    factorials[0]=1;
    inverseFactorials[0] = 1;
    for(int i = 1; i < 6001; i++) {
        factorials[i]=factorials[i-1] * i % mod;
        inverseFactorials[i] = fastExp(factorials[i], mod-2, mod);
    }
    //cout << combo(3, 2, mod);
    int t;
    cin >> t;
    string ans = "";
    for(;t>0;t--) {
        int n;
        cin >> n;

        vector<int> uniqueHeights;

        int prev = -1;

        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if(x!=prev) {
                uniqueHeights.push_back(i);
                prev=x;
            }
        }
        if(n==2) {
            if(uniqueHeights.size()==1) {
                ans+="0\n";
                continue;
            }
            ans+="1\n";
            continue;
        }
        if(uniqueHeights[uniqueHeights.size()-1]!=n-1||uniqueHeights[uniqueHeights.size()-2]!=n-2) {
            ans+="0\n";
            continue;
        }

        ll function[n+1][n/2+1];
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n/2; j++) {
                function[i][j]=0;
            }
        }
        function[2][2]=1;

        for(int i = uniqueHeights.size()-3; i >= 0; i--) {
            int diff = uniqueHeights[i+1]-uniqueHeights[i];
            int x = n-uniqueHeights[i];
            int lastX = n-uniqueHeights[i+1];
            for(int j = 2; j <= n/2; j++) {
                ll answ;
                if(j==n/2) {
                    answ = function[lastX][j] * combo(2 * j - lastX, diff, mod) % mod;
                } else {
                    answ = function[lastX][j] * combo(2*j-1-lastX, diff, mod) % mod;
                }
                answ+=function[lastX][j-1] * combo(2*j-3-lastX, diff-1, mod) % mod;
                answ%=mod;
                function[x][j]=answ;
            }
        }
        ans+=to_string(function[n][n/2])+"\n";
    }   
    
    cout << ans;
}