#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> colors(n);
    for(int i = 0; i < n; i++) cin >> colors[i];
    vector<vector<int>> minSeconds(n, vector<int>(n));
    for(int i = 0; i < n; i++) minSeconds[i][i]=1;
    for(int i = 1; i < n; i++) {
        for(int j = i-1; j >= 0; j--) {
            minSeconds[j][i]=minSeconds[j+1][i]+1;
            if(colors[j]==colors[j+1]) {
                if(j+2>=n) {
                    minSeconds[j][i]=1;
                } else {
                    minSeconds[j][i]=min(minSeconds[j][i], 1+minSeconds[j+2][i]);
                }
            }
            if(colors[j]==colors[i]&&i!=j+1) minSeconds[j][i]=min(minSeconds[j][i], minSeconds[j+1][i-1]);
            for(int k = j+2; k < i; k++) {
                if(colors[j]==colors[k]) {
                    minSeconds[j][i]=min(minSeconds[j][i], minSeconds[j+1][k-1]+minSeconds[k+1][i]);
                }
            }
            //cout << i << " " << j << " " << minSeconds[j][i] << endl;
        }
    }
    cout << minSeconds[0][n-1] << endl;
}