#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
double calculate(double a, double b, double e, ll x) {
    return pow(a,x) * e + b * (pow(a,x)-1) / (a-1);
}
bool possible(double a, double b, double e, ll x) {
    return floor(e)==floor(calculate(a,b,e,x));
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int T;
    ll k;
    cin >> T >> k;
    T--;
    double probability[T+1][T+1];
    probability[0][0]=1;
    for(int i = 1; i < T+1; i++) {
        probability[i][0]=probability[i][i]=probability[i-1][0]/2;
        for(int j = 1; j < i; j++) {
            probability[i][j]=(probability[i-1][j-1]+probability[i-1][j])/2;
        }
    }
    double prefSumProb[T+1];
    double prefSum2[T+1];
    prefSumProb[0]=probability[T][0];
    prefSum2[0]=0;
    for(int i = 1; i <= T; i++) {
        prefSumProb[i]=prefSumProb[i-1]+probability[T][i];
        prefSum2[i]=prefSum2[i-1]+i*probability[T][i];
    }
    //for(double i: prefSumProb) cout << i << endl;
    //for(double i: prefSum2) cout << i << endl;
    double e = 0;
    while(k!=0) {
        double a = prefSumProb[(int)floor(e)];
        double b = prefSum2[T]-prefSum2[(int)floor(e)];
        ll left = 1;
        ll right = 1000000000;
        while(left+1<right) {
            ll mid = (left+right+1)/2;
            //cout << k << " " << mid << " " << e << " " << fl << endl;
            if(possible(a,b,e,mid)) {
                left=mid;
            } else {
                right=mid;
            }
        }
        if(possible(a,b,e,right)) {
            left=min(right, k);
        } else {
            left=min(left,k);
        }
        e = calculate(a,b,e,left);
        k-=left;
    }
    cout << fixed << setprecision(20);
    cout << e+1 << endl;
}