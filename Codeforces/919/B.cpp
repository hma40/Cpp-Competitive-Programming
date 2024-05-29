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
vector<int> getDigits(ll num) {
    vector<int> digits;
    while(num) {
        digits.add(num%10);
        num/=10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}
ll perfectUnder(ll ub) {
    //dp[a][b][c]: a digits, sum=b, c={0 (under), 1 (same)}
    vector<int> digits = getDigits(ub);
    ll ans = 0;
    //printArray(digits);
    vector<vector<vector<int>>> dp(digits.size(), vector<vector<int>>(11, vector<int>(2)));
    dp[0][0][1]=1;
    F0R(i, digits.size()-1) {
        F0R(j, 11) {
            F0R(k, 2) {
                //cout << i << " " << j << " " << k << endl;
                if(k==1) {
                    int nextDigit = digits[i];
                    if(j+nextDigit<=10) {
                        F0R(m, nextDigit) {
                            dp[i+1][j+m][0]+=dp[i][j][1];
                        }
                        dp[i+1][j+nextDigit][1]+=dp[i][j][1];
                    } else {
                        F0R(m, 11-j) {
                            dp[i+1][j+m][0]+=dp[i][j][1];
                        }
                    }
                } else {
                    if(j==0) {
                        F0R(m, 10) {
                            dp[i+1][j+m][0]+=dp[i][j][0];
                        }
                    } else {
                        F0R(m, 11-j) {
                            //cout << m << endl;
                            dp[i+1][j+m][0]+=dp[i][j][0];
                        }
                    }
                }
            }
        }
    }
    FOR(j, 1, 11) {
        ans+=dp[digits.size()-1][j][0];
    }
    FOR(j, 1, 11) {
        if(digits.back()>=10-j) {
            ans+=dp[digits.size()-1][j][1];
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout); 
    int k;
    cin >> k;
    ll lo = 1, hi = 1e14;
    while(lo+1<hi) {
        ll mid = lo+(hi-lo)/2;
        if(perfectUnder(mid)<k) {
            lo=mid;
        } else {
            hi=mid;
        }
    }
    if(perfectUnder(lo)==k) {
        cout << lo << endl;
    } else {
        cout << hi << endl;
    }
    return 0;
}