#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
// #define int long long
#define vt vector
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        string s;
        cin >> s;
        //we want to calculate max 1 in a row if we make change s.t. there are x 0s in a row, where -1 is impossibruh
        vt<int> maxOnes(n+1, -1);
        vt<vt<int>> prefOnes(n, vt<int>(k+1));
        vt<vt<int>> prefOnesInc(n, vt<int>(k+1, -1));
        if(s[0]=='0') {
            prefOnes[0][0]=0;
            prefOnesInc[0][0]=0;
            FOR(i, 1, 1+k) {
                prefOnes[0][i]=1;
                prefOnesInc[0][i]=1;
            }
        } else {
            F0R(i, k+1) {
                prefOnesInc[0][i]=1;
                prefOnes[0][i]=1;
            }
        }
        // assert(false);
        FOR(i, 1, n) {
            if(s[i]=='1') {
                F0R(j, k+1) {
                    prefOnesInc[i][j]=prefOnesInc[i-1][j]+1;
                    prefOnes[i][j]=max(prefOnes[i-1][j], prefOnesInc[i][j]);
                }
            } else {
                prefOnesInc[i][0]=0;
                prefOnes[i][0]=prefOnes[i-1][0];
                FOR(j, 1, k+1) {
                    prefOnesInc[i][j]=prefOnesInc[i-1][j-1]+1;
                    prefOnes[i][j]=max(prefOnes[i-1][j], prefOnesInc[i][j]);
                }
            }
        }
        // assert(false);
        vt<vt<int>> suffOnes(n, vt<int>(k+1));
        vt<vt<int>> suffOnesInc(n, vt<int>(k+1));
        if(s.back()=='0') {
            suffOnes[n-1][0]=suffOnesInc[n-1][0]=0;
            FOR(i, 1, k+1) suffOnes[n-1][i]=suffOnesInc[n-1][i]=1;
        } else {
            F0R(i, k+1) {
                suffOnesInc[n-1][i]=suffOnes[n-1][i]=1;
            }
        }
        R0F(i, n-1) {
            if(s[i]=='1') {
                F0R(j, k+1) {
                    suffOnesInc[i][j]=suffOnesInc[i+1][j]+1;
                    suffOnes[i][j]=max(suffOnes[i+1][j], suffOnesInc[i][j]);
                }
            } else {
                suffOnesInc[i][0]=0;
                suffOnes[i][0]=suffOnes[i+1][0];
                FOR(j, 1, k+1) {
                    suffOnesInc[i][j]=suffOnesInc[i+1][j-1]+1;
                    suffOnes[i][j]=max(suffOnes[i+1][j], suffOnesInc[i][j]);
                }
            }
        }
        maxOnes[0]=prefOnes[n-1][k];
        // assert(false);
        if(n!=1) {
            F0R(i, n) {
                int ones = 0;
                if(s[i]=='1') ones=1;
                if(s[i]=='0') {
                    if(i==0) {
                        maxOnes[1]=max(maxOnes[1], suffOnes[1][k]);
                    } else if(i==n-1) {
                        maxOnes[1]=max(maxOnes[1], prefOnes[n-2][k]);
                    } else {
                        maxOnes[1]=max(maxOnes[1], max(prefOnes[i-1][k], suffOnes[i+1][k]));
                    }
                } else {
                    if(k!=0) {
                        if(i==0) {
                            maxOnes[1]=max(maxOnes[1], suffOnes[1][k-1]);
                        } else if(i==n-1) {
                            maxOnes[1]=max(maxOnes[1], prefOnes[n-2][k-1]);
                        } else {
                            maxOnes[1]=max(maxOnes[1], max(prefOnes[i-1][k-1], suffOnes[i+1][k-1]));
                        }
                    }
                }
                // assert(false);
                // cout << i << " " << i << " " << 1 << " " << maxOnes[1] << endl;
                // cout << "ABOUT TO ENTER FOR LOOP: " << maxOnes[2] << endl;
                FOR(j, i+1, n) {
                    if(s[j]=='1') ones++;
                    int movesLeft = k-ones;
                    if(movesLeft<0) break;
                    if(i!=0) {
                        // cout << "LINE 150" << endl;
                        maxOnes[j-i+1]=max(maxOnes[j-i+1], prefOnes[i-1][movesLeft]);
                    }
                    if(j!=n-1) {
                        // cout << "LINE 154 " << maxOnes[2] << endl;
                        // cout << j+1 << " " << movesLeft << " " << suffOnes[j+1][movesLeft] << endl;
                        maxOnes[j-i+1]=max(maxOnes[j-i+1], suffOnes[j+1][movesLeft]);
                        // cout << "line 158: " << maxOnes[2] << endl;
                    }
                    if(i==0&&j==n-1) {
                        maxOnes[n]=0;
                    }
                    // cout << i << " " << j << " " << j-i+1 << " " << movesLeft << " " << maxOnes[j-i+1] << endl;
                }
            }
        } else {
            if(k==0) {
                if(s[0]=='0') {
                    maxOnes[0]=maxOnes[1]=0;
                } else {
                    maxOnes[0]=1;
                    maxOnes[1]=-1;
                }
            } else {
                maxOnes[0]=1;
                maxOnes[1]=0;
            }
        }
        vt<int> ans(n+1);
        FOR(a, 1, n+1) {
            F0R(zeroes, n+1) {
                if(maxOnes[zeroes]!=-1) {
                    ans[a]=max(ans[a], a*zeroes+maxOnes[zeroes]);
                }
            }
        }
        // cout << "LINE 169: " << maxOnes << endl;
        // cout << suffOnes << endl;
        cout << ans[1];
        FOR(i, 2, n+1) {
            cout << " " << ans[i];
        }
        cout << endl;
    }
    return 0;
}
/*
1
6 2
101101
*/