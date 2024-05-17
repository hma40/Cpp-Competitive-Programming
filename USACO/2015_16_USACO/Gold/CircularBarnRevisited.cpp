#include <iostream>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
    int n,k;
    cin >> n >> k;
    ll r[n];
    ll prefSum[n+1];
    prefSum[0]=0;
    for(int i = 0; i < n; i++) {
        cin >> r[i];
        prefSum[i+1]=r[i]+prefSum[i];
    }
    /*
    cout << "prefSum:\n";
    for(int i = 0; i <= n; i++) {
        cout <<"i: " << i <<" prefSum: " << prefSum[i] << endl;
    }
    */
    ll ntimes[n][n];
    for(int i = 0; i < n; i++) {
        ll hm = 0;
        for(int j = i; j < n; j++) {
            hm+=r[j] * (j-i+1);
            ntimes[i][j] = hm;
        }
    }
    /*
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "i: " << i << " j: " << j << " ntimes: " << ntimes[i][j] << endl;
        }
    }
    */
    ll ans = 1000000000000;
    for(int i = 0; i < n-k; i++) {
        ll backlines[n];
        ll backlineCount = 0;
        for(int j = 0; j < i; j++) {
            backlineCount+=(j+1) * r[j];
        }
        for(int j = n-1; j > i; j--) {
            backlines[j]=backlineCount;
            backlineCount+=prefSum[i] + prefSum[n] - prefSum[j];
        }
        if(k==1) {
            ans = min(ans, backlines[i+1] + prefSum[n] - r[i]);
            continue;
        }
        /*
        cout << i << " " << ans << endl;

        cout << "---i: " << i << " -----\n";
        for(int j = i+1; j < n; j++) {
            cout << "j: " << j << " backlines: " << backlines[j] << endl;
        }
                */
        ll function[k][n] = {{1000000000000}};
        function[1][i+1] = 0;
        for(int j = i+2; j < n; j++) {
            function[1][j] = function[1][j-1] + r[j-1] * (j-1-i);
            //cout << "i: " << i << " j: " << j << " function: " << function[1][j] << endl;
        }
        for(int l = 2; l < k; l++) {
            if(i+l<n) {
                function[l][i+l]=0;
            }
        }
        for(int l = 2; l < k; l++) {
            for(int j = i+l+1; j < n; j++) {
                ll temp = 1000000000000;
                for(int m = i+l-1; m < j; m++) {
                    temp = min(temp, function[l-1][m] + ntimes[m+1][j-1]);
                }
                function[l][j]=temp;
            }
        }
        /*
        std::cout << "i: " << i << endl;
        for(int j = 0; j < k; j++) {
            for(int l = 0; l < n; l++) {
                std::cout << "j: " << j << " l: " << l << " function: " << function[j][l] << endl;
            }
        }
        */

        for(int j = i+k; j < n; j++) {
            ans = min(ans, function[k-1][j] + backlines[j]);
        }
    }
    std::cout << ans << endl;    
}
/*
6 3 2 5 4 2 6 2
*/