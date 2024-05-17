#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;
using ll = long long;
ll mod = 1000000007;
long long fastExp(long long a, long long b, long long mod=mod) {
    if(b==0) return 1;
    if(b==1) return a;
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
ll total[5001] = {0};
ll finalThing[5001] = {0};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    clock_t clockStart, clockFinish;
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    int n,m,k;
    cin >> n >> m >> k;
    int length[n], rhymeclass[n];
    for(int i = 0; i < n; i++) {
        cin >> length[i] >> rhymeclass[i];
        rhymeclass[i]--;
    }
    //function[a][b]=c: length a, ends in rhyme class b, c ways
    clockStart = clock();
    for(int i = 0; i < n; i++) {
        if(length[i]==k) {
            finalThing[rhymeclass[i]]++;
        } else {
            total[length[i]]++;
        }
    }
    for(int i = 0; i <= k; i++) {
        for(int j = 0; j < n; j++) {
            int temp = length[j]+i;
            if(temp==k) {
                finalThing[rhymeclass[j]]+=total[i];
                finalThing[rhymeclass[j]]%=mod;
            } else if(temp<k) {
                total[temp]+=total[i];
                total[temp]%=mod;
            }    
        }
    }
    //for(int i: total) cout << i << endl;
    clockFinish = clock();
    //cout << clockFinish - clockStart << endl;
    int count[26] = {0};
    clockStart = clock();
    for(int i = 0; i < m; i++) {
        char c;
        cin >> c;
        count[c-'A']++;
    }
    ll ans = 1;
    for(int i = 0; i < 26; i++) {
        ll temp = 0;
        if(count[i]==0) continue;
        for(int j = 0; j < n; j++) {
            temp+=fastExp(finalThing[j], count[i]);
            temp%=mod;
        }
        ans*=temp;
        ans%=mod;
    }
    cout << ans << endl;
    clockFinish = clock();
    //cout << clockFinish - clockStart << endl;
}