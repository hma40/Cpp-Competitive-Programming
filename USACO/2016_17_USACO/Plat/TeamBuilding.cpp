#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll mod = 1000000009;
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    //cout << 3 << endl;
    int n,m,k;
    cin >> n >> m >> k;
    int fj[n];
    int fp[m];
    for(int i = 0; i < n; i++) cin >> fj[i];
    for(int i = 0; i < m; i++) cin >> fp[i];
    sort(fj, fj+n);
    sort(fp, fp+m);
    int numValid[m];
    int fjIndex = 0;
    for(int i = 0; i < m; i++) {
        while(fjIndex<n&&fj[fjIndex]<=fp[i]) {
            fjIndex++;
        }
        numValid[i]=n-fjIndex;
        //cout << numValid[i] << endl;
    }
    ll function[k][m][n];
    ll prefSum[k][m][n] = {{{0}}};
    for(int i = m-1; i >= 0; i--) {
        for(int j = n-1; j >= 0; j--) {
            if(i==m-1) {
                function[0][i][j] = 0;
            } else {
                function[0][i][j] = function[0][i+1][j];
            }
            if(j+numValid[i]<=n) {
                function[0][i][j]+=numValid[i];
            } else {
                function[0][i][j]+=n-j;
            }
            function[0][i][j]%=mod;
            //cout << i << " " << j << " " << function[0][i][j] << endl;
        }
    }
    //int lastDifferent = -1;
    //int lastFJIndex = -1;
    for(int l = 1; l < k; l++) {
        for(int i = m-1; i >= 0; i--) {
            for(int j = n-1; j >= 0; j--) {
                if(numValid[i]<=l||i+l>=m||j+l>=n) {
                    function[l][i][j]=0;
                    //cout << l << " " << i << " " << j << " " << function[l][i][j] << endl;
                    continue;
                }
                function[l][i][j]=function[l][i+1][j] + function[l][i][j+1] - function[l][i+1][j+1];
                /*
                if(fp[i]==fp[i+1]) {
                    cout << "got here" << endl;
                    if(numValid[i]+j<n) {
                        function[l][i][j]=function[l][i][j+1];
                    } else {
                        function[l][i][j]+=function[l-1][i+1][j+1];
                    }
                } else {
                    function[l][i][j]+=function[l-1][i+1][j+1] * (min(numValid[i], n-j)-l);
                }
                */
                if(fj[j]>fp[i]) {
                    function[l][i][j]+=function[l-1][i+1][j+1];
                }
                function[l][i][j]+=mod;
                function[l][i][j]%=mod;
                //cout << l << " " << i << " " << j << " " << function[l][i][j] << endl;
            }
        }
    }
    cout << function[k-1][0][0] << endl;
}