#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct player {
    int aud;
    vector<int> pos;
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,p,k;
    cin >> n >> p >> k;
    vector<player> players(n);
    for(int i = 0; i < n; i++) {
        cin >> players[i].aud;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            int temp;
            cin >> temp;
            players[i].pos.push_back(temp);
        }
    }
    sort(begin(players), end(players), [](const player a, const player b) -> bool{
        return a.aud>b.aud;
    });
    vector<vector<ll>> arr(k+1, vector<ll>(1<<p, -1));
    arr[0][0]=0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 1<<p; j++) {
            int numAud = i;
            for(int l = 0; l < p; l++) {
                if((j&(1<<l))!=0) numAud--;
            }
            if(numAud<0) continue;
            if(numAud>k) numAud=k;
            if(arr[numAud][j]==-1) continue;
            //cout << i << " " << j << endl;
            if(numAud!=k) {
                //cout << "into loop" << endl;
                arr[numAud+1][j]=max(arr[numAud+1][j], arr[numAud][j]+players[i].aud);
            }
            for(int l = 0; l < p; l++) {
                if((j&(1<<l))==0) {
                    arr[numAud][j|(1<<l)]=max(arr[numAud][j|(1<<l)], arr[numAud][j]+players[i].pos[l]);
                }
            }
            /*
            cout << "i: " << i << " j: " << j << endl;
            for(int i = 0; i <= k; i++) {
                for(int j = 0; j < 1<<p; j++) {
                    cout << i << " " << j << " " << arr[i][j] << endl;
                }
            }
            */
        }
    }
    cout << arr[k][(1<<p)-1] << endl;
}