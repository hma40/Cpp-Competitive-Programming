#include <bits/stdc++.h>
using namespace std;
void printArray(vector<long double> &v) {
    cout << "[";
    for(auto i: v) cout << i << ", ";
    cout << "]" << endl;
}
void printArray(vector<long long> &v) {
    cout << "[";
    for(auto i: v) cout << i << ", ";
    cout << "]" << endl;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> haybales(n);
    for(int i = 0; i < n; i++) {
        cin >> haybales[i];
    }
    sort(begin(haybales),end(haybales));
    vector<long double> lb(n);
    vector<long long> constant(n);
    vector<long long> aCoef(n);
    long double sum = 0;
    for(int i = 1; i < n; i++) {
        sum+=haybales[i]-haybales[0];
    }
    aCoef[0]=sum;
    for(int i = 1; i < n; i++) {
        aCoef[i]=aCoef[i-1]-(n-i)*(haybales[i]-haybales[i-1]);
        constant[i]=constant[i-1]+i*(haybales[i]-haybales[i-1]);
    }
    lb[0]=-1e15;
    for(int i = 1; i < n; i++) {
        lb[i]=(constant[i]+(long double)0.0-constant[i-1])/(aCoef[i-1]+(long double)0.0-aCoef[i]);
    }
    int q;
    cin >> q;
    while(q--) {
        long long x,y;
        cin >> x >> y;
        long long ans = ((long long)1<<62);
        for(int i = 0; i < n; i++) {
            ans=min(ans, x*constant[i]+y*aCoef[i]);
        }
        cout << ans << endl;
    }
}