#include <iostream>
#include <math.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll factorials[501];
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
    //cout << a << " " << b << " " << endl;
    //return 1;
    return factorials[a] * fastExp(factorials[b], mod-2, mod) % mod * fastExp(factorials[a-b], mod-2, mod) % mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll mod = 998244353;
    int expo[501][501];
    int combos[501][501];
    for(int i = 1; i <= 500; i++) {
        ll total = 1;
        for(int j = 0; j < 501; j++) {
            expo[i][j]=total;
            total*=i;
            total%=mod;
        }
    }
    //cout << expo[200][200] << endl;
    ll factoria = 1;
    factorials[0]=1;
    for(int i = 1; i <= 500; i++) {
        factoria*=i;
        factoria%=mod;
        factorials[i]=factoria;

    }
    for(int i = 1; i <= 500; i++) {
        for(int j = 0; j <= i; j++) {
            combos[i][j] = combo(i, j, mod);
        }
    }
    //cout << combos[3][2] << "got here " << endl;
    //cout << expo[1][3] << "got here" << endl;
    int function[501][501];
            
    for(int i = 0; i < 501; i++) {
        for(int j = 0; j < 501; j++) {
            function[i][j]=0;
        }
    }
    //cout << expo[500][500] << endl;
    //cout << combos[500][255] << endl;
    for(int i = 2; i <= 500; i++) {
        //cout << i << endl;
        for(int j = 1; j <= 500; j++) {
            if(i==2) {
                function[i][j]=j;
                continue;
            }
            if(j<i) {
                function[i][j]=expo[j][i];
                continue;
            }
            //cout << i << " " << j << " " << endl;
            ll sum = expo[i-1][i];
            //cout << sum << endl;
            for(int k = 2; k <= i; k++) {
                //cout << "k: " << k << endl;
                sum+=(ll)function[k][j-i+1] * (ll)expo[i-1][i-k] % mod * (ll)combos[i][k] % mod;
                sum%=mod;
                //cout << sum << endl;
            }
            function[i][j]=sum;
        }
    }
    //cout << function[13][37] << endl;
    int n,x;
    cin >> n >> x;
    cout << function[n][x] << endl;
}   