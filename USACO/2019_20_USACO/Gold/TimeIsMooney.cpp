#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int n,m,c;
    cin >> n >> m >> c;
    ll moonis[n];
    for(int i = 0; i < n; i++) {
        cin >> moonis[i];
    }
    vector<vector<int>> destinations(n);
    for(int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        destinations[b].push_back(a);
    }
    ll function[n][1001];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 1001; j++) {
            if(j==0) {
                function[i][j] = -222;
            } else {
                function[i][j] = moonis[i];
            }
        }
    }

    function[0][0]=0;
    for(int j = 1; j < 1001; j++) {
        for(int i = 0; i < n; i++) {
            ll maxx = -1000000000;
            for(int k: destinations[i]) {
                if(function[k][j-1]==-222) continue;
                maxx = max(maxx, function[k][j-1]);
            }

            if(maxx!=-1000000000) {
                function[i][j]+=maxx;
            } else {
                function[i][j]=-222;
            }
            //cout << i << " " << j << " " << maxx << " " << function[i][j] << endl;
        }
    }
    ll ans = 0;
    for(int i = 0; i < 1001; i++) {
        ans = max(ans, function[0][i]-i*i*c);
    }
    cout << ans << endl;
}