#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;
ll n,m,k;
bool outOfBounds(int x, int y) {
    return x<0||y<0||x>=n||y>=m;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);

    cin >> n >> m >> k;
    vector<vector<ll>> grid(n, vector<ll>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<vector<ll>> resultsLeft(n);
    vector<vector<ll>> resultsRight(n);
    for(int i = 0; i < 1<<((n+m-2)/2); i++) {
        int down = 0;
        int x=0,y=0;
        bool oob = false;
        ll xr = grid[0][0];
        for(int j = 0; j < (n+m-2)/2; j++) {
            if(i&(1<<j)) {
                down++;
                x++;
                if(outOfBounds(x,y)){
                    oob=true;
                    break;
                }  
                xr^=grid[x][y];
            } else {
                y++;
                if(outOfBounds(x,y)) {
                    oob=true;
                    break;
                }
                xr^=grid[x][y];
            }
        }
        if(oob) continue;
        resultsLeft[down].push_back(xr);
    }   
    for(int i = 0; i < 1<<(n+m-2-((n+m-2)/2)); i++) {
        int up = 0;
        int x=n-1, y=m-1;
        bool oob = false;
        ll xr = grid[x][y];
        for(int j = 0; j < n+m-2-((n+m-2)/2); j++) {
            if(i&(1<<j)) {
                up++;
                x--;
                if(outOfBounds(x,y)) {
                    oob=true;
                    break;
                }
                xr^=grid[x][y];
            } else {
                y--;
                if(outOfBounds(x,y)) {
                    oob=true;
                    break;
                }
                xr^=grid[x][y];
            }
        }
        if(oob) continue;
        resultsRight[up].push_back(xr);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        sort(begin(resultsRight[i]), end(resultsRight[i]));
    }
    for(int i = 0; i < n; i++) {
        for(ll j: resultsLeft[i]) {
            ll xr = j^k^grid[i][(n+m-2)/2-i];
            int lb = lower_bound(begin(resultsRight[n-1-i]), end(resultsRight[n-1-i]), xr)-begin(resultsRight[n-1-i]);
            int rb = upper_bound(begin(resultsRight[n-1-i]), end(resultsRight[n-i-1]), xr)-begin(resultsRight[n-1-i])-1;
            if(lb<resultsRight[n-1-i].size()&&resultsRight[n-1-i][lb]==xr) {
                ans+=rb-lb+1;
            }
        }
    }
    cout << ans << endl;
}
