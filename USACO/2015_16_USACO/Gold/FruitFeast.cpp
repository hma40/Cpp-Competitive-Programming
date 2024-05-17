#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    ll t,a,b;
    cin >> t >> a >> b;
    bool possible[t+1][2];
    for(int i = 0; i <= t; i++) {
        possible[i][0]=false;
        possible[i][1]=false;
    }
    possible[0][0]=true;
    int last = 0;
    for(int i = 0; i <=t; i++) {
        if(possible[i][0]) {
            //cout << i << " 0" << endl;
            last=max(last, i);
            possible[i/2][1]=true;
            if(i+a<=t) {
                possible[i+a][0]=true;
            }
            if(i+b<=t) {
                possible[i+b][0]=true;
            }
        }
    }
    for(int i = 0; i <= t; i++) {
        
        if(possible[i][1]) {
            last=max(last, i);
            if(i+a<=t) {
                possible[i+a][1]=true;
            }
            if(i+b<=t) {
                possible[i+b][1]=true;
            }
        }
    }
    cout << last << endl;
}