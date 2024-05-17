#include <iostream>
using namespace std;
using ll = long long;

ll pow2[100002];
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    ll mod = 1000000007;
    ll power2 = 1;
    for(int i = 0; i < 100002; i++) {
        pow2[i]=power2;
        power2<<=1;
        power2%=mod;
    }
    int change[200001];
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a,b;
        cin >> a >> b;
        change[a]=-1;
        change[b]=1;
    }
    int k = n;
    ll ans = 0;
    for(int i = 1; i <= 2*n; i++) {
        k+=change[i];
        if(change[i]==-1) {
            ans+=pow2[k];
            ans%=mod;
        }
    }
    cout << ans << endl;
}