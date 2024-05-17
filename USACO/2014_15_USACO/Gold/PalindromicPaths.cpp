#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
    int n;
    cin >> n;
    vector<string> maze(n);
    for(int i = 0; i < n; i++) {
        cin >> maze[i];
    }
    ll func[n][n];
    for(int j = 0; j < n; j++) {
        for(int k = 0; k < n; k++) {
            func[j][k]=0;
        }
    }
    func[0][n-1]=1;
    for(int i = 1; i < n; i++) {
        ll tempFunc[n][n];
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                tempFunc[j][k]=0;
            }
        }
        for(int j = 0; j < n; j++) {
            for(int k = n-1; k >= 0; k--) {
                int firstY = i-j, secondY=-k+2*n-2-i;
                if(firstY<0||secondY<0||firstY>n-1||secondY>n-1) continue;
                if(maze[j][firstY]!=maze[k][secondY]) continue;
                ll result = 0;
                if(j>0) {
                    if(k<n-1) {
                        result+=func[j-1][k+1];
                    }
                    if(secondY<n-1) {
                        result+=func[j-1][k];
                    }
                }
                if(firstY>0) {
                    if(k<n-1) {
                        result+=func[j][k+1];
                    } 
                    if(secondY<n-1) {
                        result+=func[j][k];
                    }
                }
                result%=mod;
                tempFunc[j][k]=result;
            }
        }
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                func[j][k]=tempFunc[j][k];
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans+=func[i][i];
        ans%=mod;
    }
    cout << ans << endl;
}