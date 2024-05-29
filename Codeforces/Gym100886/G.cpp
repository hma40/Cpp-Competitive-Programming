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
void printArray(vector<int> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
void printArray(vector<ll> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
vector<int> getDigits(ll x) {
    vector<int> ret;
    while(x) {
        ret.add(x%10);
        x/=10;
    }
    reverse(begin(ret), end(ret));
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    ll a,b;
    cin >> a >> b;
    if(a==b) {
        cout << a << endl;
        return 0;
    }
    vector<int> aDigits = getDigits(a);
    vector<int> bDigits = getDigits(b);
    string append = "";
    /*
    dp[a][b][c]=x:
    a digits used
    b: 0 if below low, 1 if equal low, 2 if above low
    c: 0 if below high, 1 if equals high, 2 if above high
    max product is x
    */
    if(aDigits.size()==bDigits.size()) {
        F0R(i, aDigits.size()) {
            if(aDigits[i]==bDigits[i]) {
                append+=to_string(aDigits[i]);
                aDigits.erase(aDigits.begin());
                bDigits.erase(bDigits.begin());
                i--;
            } else {
                break;
            }
        }
    }   
    ll maxProd=0;
    string best = "";
    vector<vector<vector<ll>>> dp(bDigits.size()+1, vector<vector<ll>>(3, vector<ll>(3)));
    vector<vector<vector<string>>> from(bDigits.size()+1, vector<vector<string>>(3, vector<string>(3)));
    FOR(i, 1, 10) {
        int firstPar=0, secondPar=0;
        if(i<aDigits[0]) {
            firstPar=0;
        } else if(i==aDigits[0]) {
            firstPar=1;
        } else {
            firstPar=2;
        }
        if(i<bDigits[0]) {
            secondPar=0;
        } else if(i==bDigits[0]) {
            secondPar=1;
        } else {
            secondPar=2;
        }
        if((ll)i>dp[1][firstPar][secondPar]) {
            dp[1][firstPar][secondPar]=i;
            from[1][firstPar][secondPar]=to_string(i);
        }
    }
    FOR(i, 1, bDigits.size()+1) {
        F0R(j, 3) {
            F0R(k, 3) {
                if(aDigits.size()==bDigits.size()) {
                    if(i==aDigits.size()&&j>=1&&k<=1) {
                        if(dp[i][j][k]>maxProd) {
                            maxProd=dp[i][j][k];
                            best=from[i][j][k];
                        }
                    }
                } else {
                    if(i==aDigits.size()) {
                        if(j>=1) {
                            if(dp[i][j][k]>maxProd) {
                                maxProd=dp[i][j][k];
                                best=from[i][j][k];
                            }
                        } 
                    } else if(i>aDigits.size()) {
                        if(i==bDigits.size()) {
                            if(k<=1) {
                                if(dp[i][j][k]>maxProd) {
                                    maxProd=dp[i][j][k];
                                    best=from[i][j][k];
                                }
                            }
                        } else {
                            if(dp[i][j][k]>maxProd) {
                                maxProd=dp[i][j][k];
                                best=from[i][j][k];
                            }
                        }
                    }
                }
                if(i!=bDigits.size()) {
                    //cout << i << " " << j << " " << k << endl;
                    if(i>=aDigits.size()) {
                        //cout << "ENTERED LINE 126" << endl;
                        if(k!=1) {
                            if(dp[i+1][j][k]<dp[i][j][k]*9) {
                                dp[i+1][j][k]=dp[i][j][k]*9;
                                from[i+1][j][k]=from[i][j][k]+"9";
                            }
                        } else {
                            if(dp[i+1][j][k]<dp[i][j][k]*bDigits[i]) {
                                dp[i+1][j][k]=dp[i][j][k]*bDigits[i];
                                from[i+1][j][k]=from[i][j][k]+to_string(bDigits[i]);
                            }
                            if(dp[i+1][j][0]<dp[i][j][k]*(bDigits[i]-1)) {
                                dp[i+1][j][0]=dp[i][j][k]*(bDigits[i]-1);
                                from[i+1][j][0]=from[i][j][k]+to_string(bDigits[i]-1);
                            }
                            if(dp[i+1][j][2]<dp[i][j][k]*9) {
                                dp[i+1][j][2]=dp[i][j][k]*9;
                                from[i+1][j][2]=from[i][j][k]+to_string(9);
                            }
                        }
                    } else {
                        //cout << "ENTERED LINE 147" << endl;
                        if(j!=1) {
                            if(k!=1) {
                                if(dp[i+1][j][k]<dp[i][j][k]*9) {
                                    //cout << "l148 " << i << " " << j << " " << k << " " << dp[i][j][k]*9 << endl;
                                    dp[i+1][j][k]=dp[i][j][k]*9;
                                    from[i+1][j][k]=from[i][j][k]+"9";
                                }
                            } else {
                                if(dp[i+1][j][k]<dp[i][j][k]*bDigits[i]) {
                                    dp[i+1][j][k]=dp[i][j][k]*bDigits[i];
                                    from[i+1][j][k]=from[i][j][k]+to_string(bDigits[i]);
                                }
                                if(dp[i+1][j][0]<dp[i][j][k]*(bDigits[i]-1)) {
                                    dp[i+1][j][0]=dp[i][j][k]*(bDigits[i]-1);
                                    from[i+1][j][0]=from[i][j][k]+to_string(bDigits[i]-1);
                                }
                                if(dp[i+1][j][2]<dp[i][j][k]*9) {
                                    dp[i+1][j][2]=dp[i][j][k]*9;
                                    from[i+1][j][2]=from[i][j][k]+to_string(9);
                                }
                            }
                        } else {
                            if(dp[i+1][j][k]<dp[i][j][k]*aDigits[i]) {
                                dp[i+1][j][k]=dp[i][j][k]*aDigits[i];
                                from[i+1][j][k]=from[i][j][k]+to_string(aDigits[i]);
                            }
                            if(dp[i+1][0][k]<dp[i][j][k]*(aDigits[i]-1)) {
                                dp[i+1][0][k]=dp[i][j][k]*(aDigits[i]-1);
                                from[i+1][0][k]=from[i][j][k]+to_string(aDigits[i]-1);
                            }
                            if(dp[i+1][2][k]<dp[i][j][k]*9) {
                                dp[i+1][2][k]=dp[i][j][k]*9;
                                from[i+1][2][k]=from[i][j][k]+"9";
                            }
                        }
                    }
                }
            }
        }
    }
    F0R(i, bDigits.size()+1) {
        F0R(j, 3) {
            F0R(k, 3) {
                //cout << i << " " << j << " " << k << " " << dp[i][j][k] << " " << from[i][j][k] << endl;
            }
        }
    }
    cout << append << best << endl;
    return 0;
}