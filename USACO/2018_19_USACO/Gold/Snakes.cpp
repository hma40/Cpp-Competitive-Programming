#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    int n,k;
    cin >> n >> k;
    int size[n];
    ll prefSum[n+1];
    prefSum[0]=0;
    for(int i = 0; i < n; i++) {
        cin >> size[i];
        prefSum[i+1]=prefSum[i]+size[i];
    }
    int maxSize[n][n];
    for(int i = 0; i < n; i++) {
        int currentMax = size[i];
        for(int j = i; j < n; j++) {
            currentMax=max(currentMax, size[j]);
            maxSize[i][j]=currentMax;
        }
    }
    /*
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "i: " << i << " j: " << j << " max: " << maxSize[i][j] << endl;
        }
    }
    */
    ll minWaste[k+1][n];
    //ll function[k+1][n][n]; // function[times changed][last time changed start][last time changed end] = min wasted space so far
    for(int i = 0; i < k+1; i++) {
        for(int j = 0; j < n; j++) {
            /*
            for(int k = 0; k < n; k++) {
                function[i][j][k]=4000000000;
            }
            */
            minWaste[i][j]=4000000000;
        }
    }
    for(int i = 0; i < n; i++) {
        //function[0][0][i]=maxSize[0][i] * (i+1) - prefSum[i+1];
        //cout << function[0][0][i] << endl;
        minWaste[0][i]=maxSize[0][i] * (i+1) - prefSum[i+1];
    }
    /*
    for(int i = 0; i <= n; i++) {
        cout << i << " " << prefSum[i] << endl;
    }
    */
    for(int i = 1; i < k+1; i++) {
        for(int j = 1; j < n; j++) {
            for(int l = j; l < n; l++) {
                //function[i][j][l] = minWaste[i-1][j-1] + maxSize[j][l] * (l-j+1) - prefSum[l+1] + prefSum[j];
                ll temp = minWaste[i-1][j-1] + maxSize[j][l] * (l-j+1) - prefSum[l+1] + prefSum[j];
                //cout << "i: " << i << " j: " << j << " l: " << l << " " << minWaste[i-1][j-1] << " " << maxSize[j][l] << " " << (j-l+1) << " " << prefSum[l+1] << " " << prefSum[j] << endl;
                minWaste[i][l]=min(minWaste[i][l], temp);
            }
        }
    }
        /*
    for(int i = 0; i < k+1; i++) {
        for(int j = 0; j < n; j++) {
            cout << "i: " << i << " j: " << j << " minWaste: " << minWaste[i][j] << endl;
            cout << "maxSize: " << maxSize[i][j] << endl;
        }
    }

    for(int i = 0; i < k+1; i++) {
        for(int j = 0; j < n; j++) {
            for(int l = 0; l < n; l++) {
                cout << "i: " << i << " j: " << j << " l: " << l << " function: " << function[i][j][l] << endl;
            }
        }
    }
    */
    ll ans = 4000000000;
    for(int i = 0; i <= k; i++) {
        ans = min(ans, minWaste[i][n-1]);
    }
    cout << ans << endl;
}