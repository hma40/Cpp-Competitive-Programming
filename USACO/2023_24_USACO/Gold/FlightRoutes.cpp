#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> bits(n-1);
    for(int i = 1; i < n; i++) {
        cin >> bits[i-1];
    }
    vector<vector<bool>> hasFlight(n, vector<bool>(n));
    vector<vector<int>> dp(n, vector<int>(n));
    for(int d = 1; d < n; d++) {
        for(int left = 0; left < n-d; left++) {
            int right = left+d;
            for(int d2 = d-1; d2 > 0; d2--) {
                int left2 = right-d2;
                if(hasFlight[left2][right]) {
                    dp[left][right]+=dp[left][left2];
                    dp[left][right]%=2;
                }
            }
            if(dp[left][right]!=bits[left][d-1]-'0') {
                dp[left][right]++;
                dp[left][right]%=2;
                hasFlight[left][right]=true;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(hasFlight[i][j]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}