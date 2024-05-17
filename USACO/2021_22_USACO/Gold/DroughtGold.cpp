#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll mod = 1000000007;
int n;
ll solve(int arr[]) {
    for(int i = 0; i < n; i++) {
        arr[i]-=1;
    }
    //cout << endl;
    ll function[n][1001] = {{0}};
    ll prefSum[n][1001] = {{0}};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 1001; j++) {
            if(arr[i] < j) {
                function[i][j] = 0;
            } else if(i==0) {
                function[i][j]=1;
            } else {
                function[i][j] = prefSum[i-1][arr[i]-j];
            }
            if(j==0) {
                prefSum[i][j] = function[i][j];
                continue;
            }
            prefSum[i][j] = prefSum[i][j-1] + function[i][j];
            prefSum[i][j] %= mod;
        }
    }
    return function[n-1][0];
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //int n;
    cin >> n;

    int arr[n];
    int minn = 1000000;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]++;
        minn = min(minn, arr[i]);
    }
    if(n%2==0) {
        cout << solve(arr) << endl;
    } else {
        ll ans = 0;
        for(int j = 0; j < minn; j++) {
            ans+=solve(arr);
            ans%=mod;
        }
        cout << ans << endl;
    }
}