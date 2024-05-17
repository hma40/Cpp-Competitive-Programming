#include <iostream>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    int n;
    cin >> n;
    int arr[n+1];
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int function[n+1][n+1];
    for(int i = 0; i < n+1; i++) {
        for(int j = 0; j < n+1; j++) {
            function[i][j]=150;
        }
    }
    if(arr[1]==0) {
        function[1][1]=0;
    } else {
        function[1][1]=1;
    }
    for(int i = 2; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            int minn = 150;
            for(int k = i-1; k < j; k++) {
                int here = function[i-1][k];
                for(int l = k+1; l < j; l++) {
                    if(arr[l]!=l-k) {
                        here++;
                    }
                }
                minn=min(minn, here);
            }
            if(arr[j]!=0) {
                minn++;
            }
            function[i][j]=minn;
        }
    }
    string ans = "";
    for(int i = 1; i <= n; i++) {
        int min_ans = 150;
        for(int j = i; j <= n; j++) {
            int here = function[i][j];
            for(int k = j+1; k <= n; k++) {
                if(arr[k]!=k-j) {
                    here++;
                }
            }
            min_ans=min(min_ans, here);
        }
        ans+=to_string(min_ans)+"\n";
    }
    cout << ans;
}