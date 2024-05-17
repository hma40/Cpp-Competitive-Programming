#include <iostream>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    int fj[n];
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if(s=="P") {
            fj[i]=1;
        } else if(s=="S") {
            fj[i]=2;
        } else {
            fj[i]=0;
        }
    }
    int function[n][k+1][3];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            for(int m = 0; m < 3; m++) {
                if(j>i) {
                    function[i][j][m]=-1;
                    //cout << "line 30 " << i << " " << j << " " << m << " " << function[i][j][m] << endl;
                    continue;
                }
                if(i==0) {
                    if((fj[i]+1)%3==m) {
                        function[i][j][m]=1;
                    } else {
                        function[i][j][m]=0;
                    }
                    //cout << "line 39 " << i << " " << j << " " << m << " " << function[i][j][m] << endl;
                    continue;
                }
                int score = 0;
                if((fj[i]+1)%3==m) {
                    score = 1;
                }
                if(j==0) {
                    function[i][j][m]=score+function[i-1][j][m];
                    //cout << "line 48: " << function[i-1][j][m] << " score: " << score << endl;
                } else {
                    function[i][j][m] = score + max(max(function[i-1][j-1][(m+1)%3], function[i-1][j-1][(m+2)%3]), function[i-1][j][m]);
                    //cout << "line 48: " << function[i-1][j-1][(m+1)%3] << " " << function[i-1][j-1][(m+2)%3] << " " << function[i-1][j][m] << " score: " << score << endl;
                }
                //cout << "i: " << i << " j: " << j << " m: " << m << " f[i][j][m]: " << function[i][j][m] << endl;
            }
        }
    }
    int ans = 0;
    for(int j = 0; j <= k; j++) {
        for(int m = 0; m < 3; m++) {
            ans = max(ans, function[n-1][j][m]);
        }
    }
    cout << ans << endl;
}