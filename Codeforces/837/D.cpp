#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct num {
    int numTwos=0, numFives=0;
};


int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    int n,l;
    cin >> n >> l;
    //int func[n+1][l+1][5500];
    vector<num> numbers(n);
    for(int i = 0; i < n; i++) {
        ll temp;
        cin >> temp;
        while(temp%2==0) {
            numbers[i].numTwos++;
            temp/=2;
        }
        while(temp%5==0) {
            numbers[i].numFives++;
            temp/=5;
        }
    }
    int fun[l+1][5500];
    for(int j = 0; j <= l; j++) {
        for(int k = 0; k < 5500; k++) {
            fun[j][k]=-1;
        }
    }
    int ans = 0;
    fun[0][0]=0;
    for(int i = 1; i <= n; i++) {
        int fun2[l+1][5500];
        for(int j = 0; j <= l; j++) {
            for(int k = 0; k < 5500; k++) {
                fun2[j][k]=-1;
            }
        }
        fun2[0][0]=0;
        for(int j = 1; j <= l; j++) {
            for(int k = 0; k < 5500; k++) {
                //if(i==2&&j==1&&k==0) cout << "got here 1";
                if(j>i) continue;
                fun2[j][k]=fun[j][k];
                //if(i==2&&j==1&&k==0) cout << "got here 2";
                if(k<numbers[i-1].numFives) {
                    continue;
                }
                
                //if(i==2&&j==1&&k==0) {
                    //cout << "got here 3" << endl;
                    //cout << j-1 << " " << k-numbers[i-1].numFives << fun[j-1][k-numbers[i-1].numFives] << endl;
                //}
                if(fun[j-1][k-numbers[i-1].numFives]==-1) { 

                    continue;
                }
                
                //if(i==2&&j==1&&k==0) cout << "got here 4";
                fun2[j][k]=max(fun2[j][k], fun[j-1][k-numbers[i-1].numFives]+numbers[i-1].numTwos);
            }
        }
        for(int j = 0; j <= l; j++) {
            for(int k = 0; k < 5500; k++) {
                //if(j==1&&k==0) {
                    //cout << "GOT HERE i: " << i << " fun: " << fun[j][k] << " " << fun2[j][k] << endl;
                //}
                fun[j][k]=fun2[j][k];

                //cout << "i: " << i << " j: " << j << " k: " << k << " fun: " << fun[j][k] << endl;
                ans=max(ans, min(k, fun[j][k]));
            }
        }
    }
    cout << ans << endl;
}
/*

*/