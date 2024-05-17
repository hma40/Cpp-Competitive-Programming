#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    int n,k;
    cin >> n >> k;
    int skill[n+1];
    for(int i = 1; i <= n; i++) {
        cin >> skill[i];
    }
    ll function[n+1][k+1];
    ll maxGroup[n+1][k+1];
    ll maxx[n+1];
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            function[i][j] = 0;
            maxGroup[i][j] = 0;
        }
        maxx[i]=0;
    }
    function[1][1]=skill[1];
    maxx[1]=skill[1];
    maxGroup[1][1]=skill[1];
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            if(j>i) {
                continue;
            }
            if(j==1) {
                function[i][j]=maxx[i-1]+skill[i];
                maxGroup[i][j]=skill[i];
                maxx[i]=function[i][j];
                //cout << "i: " << i << " j: " << j << " function: " << function[i][j] << " max group: " << maxGroup[i][j] << " maxx: " << maxx[i] << endl;
                continue;
            } 
            if(skill[i]>maxGroup[i-1][j-1]) {
                ll calc = function[i-1][j-1];
                calc -= (j-1) * maxGroup[i-1][j-1];
                maxGroup[i][j]=skill[i];
                calc += j * maxGroup[i][j];
                function[i][j]=calc;
            } else {
                maxGroup[i][j]=maxGroup[i-1][j-1];
                function[i][j]=function[i-1][j-1]+maxGroup[i-1][j-1];
            }
            maxx[i]=max(maxx[i], function[i][j]);
            //cout << "i: " << i << " j: " << j << " function: " << function[i][j] << " max group: " << maxGroup[i][j] << " maxx: " << maxx[i] << endl;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= k; i++) {
        ans=max(ans, function[n][i]);
    }
    cout << ans << endl;
}