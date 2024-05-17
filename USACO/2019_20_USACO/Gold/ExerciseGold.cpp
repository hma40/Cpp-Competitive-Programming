#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> primes;
void generate_primes(int n) {
    vector<bool> visited(n+1);
    for(int i = 2; i <= n; i++) {
        if(visited[i]) continue;
        primes.push_back(i);
        for(int j = i*i; j <= n; j+=i) {
            visited[j]=true;
        }
    }
}
int n,mod;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    cin >> n >> mod;
    generate_primes(n);
    ll func[n+1][primes.size()+1];
    ll total[n+1][primes.size()+1];
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= primes.size(); j++) {
            func[i][j]=1;
            total[i][j]=0;
        }
    }
    for(int i = 0; i <= primes.size(); i++) {
        total[0][i]=1;
        total[1][i]=1;
    }
    for(int i = 0; i <= n; i++) {
        total[i][0]=1;
    }
    ll ans = 1;
    for(int i = 2; i <= n; i++) {   
        for(int j = 1; j <= primes.size(); j++) {
            ll current = 0;

            ll curPow = primes[j-1];
            while(true) {
                int temp = i;
                temp-=curPow;
                if(temp<0) break;
                current+=total[temp][j-1] * curPow % mod;
                curPow*=primes[j-1];
                curPow%=mod;
            }
            func[i][j]=current;
            total[i][j]=total[i][j-1]+func[i][j];
            total[i][j]%=mod;
        }
    }
    /*
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= primes.size(); j++) {
            cout << "i: " << i << " j: " << j << " f: " << func[i][j] << " total: " << total[i][j] << endl; 
        }
    }
    */
    cout << total[n][primes.size()] << endl;
}