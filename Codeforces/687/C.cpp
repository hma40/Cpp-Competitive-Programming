#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 1000000007;
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vector<int> coins(n);
    F0R(i, n) cin >> coins[i];
    vector<vector<vector<bool>>> canMake(k+1, vector<vector<bool>>(n, vector<bool>(k+1)));
    //canMake[a][b][c]: whether or not you can make value a with some subset of the first b coins that sum to c
    F0R(i, n) {
        canMake[0][i][0]=true;
    }
    F0R(i, k+1) {
        F0R(j, n) {
            F0R(m, k+1) {
                //cout << i << " " << j << " " << m << endl;
                if(j==0) {
                    if(m==coins[0]) {
                        if(i==0||i==coins[0]) canMake[i][j][m]=true;
                    }
                } else {
                    canMake[i][j][m]=canMake[i][j-1][m];
                    if(m>=coins[j]) {
                        canMake[i][j][m]=canMake[i][j][m]||canMake[i][j-1][m-coins[j]];
                        if(i>=coins[j]) {
                            canMake[i][j][m]=canMake[i][j][m]||canMake[i-coins[j]][j-1][m-coins[j]];
                        }
                    }
                }
            }
        }
    }
    vector<int> v;
    F0R(i, k+1) {
        if(canMake[i][n-1][k]) {
            v.push_back(i);
        }
    }
    cout << v.size() << endl << v[0];
    FOR(i, 1, v.size()) {
        cout << " " << v[i];
    }
    cout << endl;
    return 0;
}