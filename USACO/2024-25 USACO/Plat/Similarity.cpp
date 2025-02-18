#include <bits/stdc++.h>

using namespace std;
#define int long long
int mod = 1000000007; 
int bexpo(int b, int e=mod-2) {
    int a = 1;
    while(e) {
        if(e&1) a=a*b%mod;
        b=b*b%mod;
        e>>=1;
    }
    return a;
}
signed main() {
    int n,k;
    cin >> n >> k;
    vector<int> freq(1048576);
    vector<int> a(n);
    int largest = 1;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
        a[i]=x;
        while(largest<=a[i]) largest*=2;
    }
    /*
    for each possible bitwise OR: 
    for each possible bitwise AND:
    
    */
    vector<int> ans(1048576);

    for(int i = 0; i < n; i++) cout << ans[a[i]] << "\n";
}