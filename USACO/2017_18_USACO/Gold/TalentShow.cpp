#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    int n,w;
    cin >> n >> w;
    int data[n][2];
    for(int i = 0; i < n; i++) {
        cin >> data[i][0] >> data[i][1];
    }
    ll minWeight[250001];
    ll minAcceptedWeight[250001];
    for(int i = 0; i < 250001; i++) {
        minWeight[i]=350000000;
        minAcceptedWeight[i]=350000000;
    }
    minWeight[0]=0;
    for(int i = 0; i < n; i++) {
        for(int j = 250001-1; j >= data[i][1]; j--) {//data[i][1]; j < 60; j++) {
            ll temp = minWeight[j-data[i][1]]+data[i][0];
            minWeight[j]=min(minWeight[j], temp);
            if(temp>=w) {
                minAcceptedWeight[j]=min(minAcceptedWeight[j], temp);
            }
        }
    }
    double bestRatio = 0;
    for(int i = 0; i < 250001; i++) {
        //cout << i << " " << minAcceptedWeight[i] << endl;
        bestRatio=max(bestRatio, (double)i/minAcceptedWeight[i]);
    }
    //cout << fixed << setprecision(20);
    cout << (int)floor(1000*bestRatio) << endl;
}