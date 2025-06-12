#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main() {
    int l,n;
    cin >> l >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    if(l==1) {
        int m = 0, ans = 0;
        multiset<int> st;
        for(int i = 0; i < n; i++) if(s[i]=='M') m++; else st.insert(a[i]);
        for(int i = 0; i < m; i++) cout << "0\n";
        while(st.size()) {
            ans+=(*st.begin());
            st.erase(st.find(*st.begin()));
            cout << ans << "\n";
        }
    } else if(n<=5000&&l==3) {
        vector<vector<int>> dp(n+1, vector<int>(n+1, (int)1e18));//dp[i][j] = min cost so that 0...i has j copies of MOO
        for(int i = 0; i <= n; i++) dp[i][0]=0;
        for(int i = 3; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                dp[i][j]=dp[i-1][j];
                int here = dp[i-3][j-1];
                if(s[i-3]=='O') here+=a[i-3];
                if(s[i-2]=='M') here+=a[i-2];
                if(s[i-1]=='M') here+=a[i-1];
                dp[i][j]=min(dp[i][j], here);
            }
            for(int j = n-1; j >= 0; j--) {
                dp[i][j]=min(dp[i][j], dp[i][j+1]);
            }
        }
        for(int i = 1; i <= n/l; i++) {
            cout << dp[n][i] << "\n";
        }
    }
}