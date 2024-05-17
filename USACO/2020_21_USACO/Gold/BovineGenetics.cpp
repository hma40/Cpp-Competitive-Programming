#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll mod = 1000000007;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    string s;
    cin >> s;
    ll function[s.length()][5][4][4]={{{{0}}}};
    for(int i = 0; i < s.length(); i++) {
        if(s[i]=='A') {
            s[i]='0';
        } else if(s[i]=='C') {
            s[i]='1';
        } else if(s[i]=='G') {
            s[i]='2';
        } else if(s[i]=='T') {
            s[i]='3';
        } else {
            s[i]='4';
        }
    }
    if(s[0]-'0'==4) {
        for(int i = 0; i < 4; i++) {
            function[0][4][i][i]=1;
        }
    } else {
        function[0][4][s[0]-'0'][s[0]-'0']=1;
    }
    for(int i = 1; i < s.length(); i++) {
        int x = s[i]-'0';
        //case 1: only one substring
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                if(x!=4&&x!=k) continue;
                for(int l = 0; l < 4; l++) {
                    if(l==k) {
                        continue;
                    }
                    function[i][4][j][k]+=function[i-1][4][j][l];
                    function[i][4][j][k]%=mod;
                }
            }
        }
        //case 2.1: only adding one letter to last substring
        for(int l = 0; l < 4; l++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    if(x!=4&&x!=k) continue;

                    for(int m = 0; m < 4; m++) {
                        if(m==k) continue;
                        function[i][l][j][k]+=function[i-1][l][j][m];
                        function[i][l][j][k]%=mod;
                    }
                }
            }
        }
        //case 2.2: new substring
        //function[i][j][x][x]
        if(x==4) {
            for(int l = 0; l < 4; l++) {
                for(int m = 0; m < 4; m++) {
                    for(int j = 0; j < 4; j++) {
                        function[i][l][m][m]+=function[i-1][4][l][j];
                        function[i][l][m][m]%=mod;
                    }
                }
            }
        } else {
            for(int l = 0; l < 4; l++) {
                for(int j = 0; j < 4; j++) {
                    function[i][l][x][x]+=function[i-1][4][l][j];
                    function[i][l][x][x]%=mod;
                }
            }
        }
        for(int l = 0; l < 4; l++) {
            for(int m = 0; m < 4; m++) {
                for(int j = 0; j < 4; j++) {
                    if(l!=j) continue;
                    if(x==4) {
                        for(int k = 0; k < 4; k++) {
                            function[i][m][k][k]+=function[i-1][l][m][j];
                            function[i][m][k][k]%=mod;
                        }
                    } else {
                        function[i][m][x][x]+=function[i-1][l][m][j];
                        function[i][m][x][x]%=mod;
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ans+=function[s.length()-1][4][i][j];
            ans%=mod;
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            ans+=function[s.length()-1][i][j][i];
            ans%=mod;
        }
    }
    cout << ans << endl;
    for(int i = 0; i < s.length(); i++) {
        for(int j = 0; j < 5; j++) {
            for(int k = 0; k < 4; k++) {
                for(int l = 0; l < 4; l++) {
                    cout << "i: " << i << " j: " << j << " k: " << k << " l: " << l << " function: " << function[i][j][k][l] << endl;
                }
            }
        }
    }
}