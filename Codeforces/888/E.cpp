#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> firstHalf, secondHalf;
ll m;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];
    firstHalf.push_back(0);
    secondHalf.push_back(0);
    for(int i = 0; i < n/2; i++) {
        int sz = firstHalf.size();
        for(int j = 0; j < sz; j++) {
            firstHalf.push_back((firstHalf[j]+arr[i])%m);
        }
    }
    for(int i = n/2; i < n; i++) {
        int sz = secondHalf.size();
        for(int j = 0; j < sz; j++) {
            secondHalf.push_back((secondHalf[j]+arr[i])%m);
        }
    }
    sort(begin(firstHalf), end(firstHalf));
    sort(begin(secondHalf), end(secondHalf));
    ll ans = 0;
    for(ll x: firstHalf) {
        ll need = m-x;
        ll lb = lower_bound(begin(secondHalf), end(secondHalf), need)-begin(secondHalf);

        if(lb==secondHalf.size()||secondHalf[lb]>=need) {
            lb--;
        }
        if(lb<0) {
            ans=max(ans, x);
        } else {
            ans=max(ans, x+secondHalf[lb]);
        }
    }
    cout << ans << endl;
}