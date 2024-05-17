#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod = 1000000007;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    for(;t>0;t--) {
        int n;
        cin >> n;
        string tempb, tempe,b,e;
        cin >> tempb >> tempe;
        for(char c: tempb) {
            if(c=='0') {
                b="0";
            } else if(c!='1') {
                b+=c;
            }
        }
        for(char c: tempe) {
            if(c=='0') {
                e="0";
            } else if(c!='1') {
                e+=c;
            }
        }
        ll bLast[b.size()+1][e.size()+1];
        ll eLast[b.size()+1][e.size()+1];
        for(int i = 0; i <= b.size(); i++) {
            for(int j = 0; j <= e.size(); j++) {
                if(i==0&&j==0) continue;
                bLast[i][j]=0;
                eLast[i][j]=0;
                if(i==0) {
                    eLast[i][j]=1;
                } else if(j==0) {
                    bLast[i][j]=1;
                } 
            }
        }
        //cout << b << " " << e << endl;
        for(int i = 1; i <= b.size(); i++) {
            for(int j = 1; j <= e.size(); j++) {
                eLast[i][j]=eLast[i][j-1]+bLast[i][j-1];
                eLast[i][j]%=mod;
                bLast[i][j]=bLast[i-1][j];
                //cout << i << " " << j << " " << bLast[i][j] << " " << eLast[i][j] << endl;
                if(!((b[i-1]=='+'&&e[j-1]=='+')||(b[i-1]!='+'&&e[j-1]!='+'))) {
                    //cout << i-1 << " " << b[i-1] << " " << e[i-1] << endl;
                    bLast[i][j]+=eLast[i-1][j];
                    bLast[i][j]%=mod;
                }
                //cout << i << " " << j << " " << bLast[i][j] << " " << eLast[i][j] << endl;
            }
        }
        cout << (bLast[b.size()][e.size()]+eLast[b.size()][e.size()])%mod << endl;
        //cout << "test case "<<t<<" complete" << endl;
    }
}