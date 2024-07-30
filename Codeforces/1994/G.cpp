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
#define int long long
#define vt vector
#define endl "\n"
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        string sum;
        vt<string> values(n);
        cin >> sum;
        F0R(i, n) cin >> values[i];
        vt<vt<bool>> dp(k+1, vt<bool>(2*n+5));
        //dp[i][j]: true if j carries until ith bit
        dp[k][0]=true;
        ROF(i, 1, k) {
            int z=0, o=0;
            F0R(j, n) {
                if(values[j][i]=='0') z++;
                else o++;
            }
            //option 1: use o
            F0R(carries, 2*n+5) {
                if(dp[i+1][carries]) {
                    int here = o+carries;
                    if(here%2==0&&sum[i]=='0') {
                        //possible!
                        int cHere = here/2;
                        dp[i][cHere]=true;
                    } 
                    if(here%2==1&&sum[i]=='1') {
                        int cHere = here/2;
                        dp[i][cHere]=true;
                    }
                }
            }
            //option 2: use z
            F0R(carries, 2*n+5) {
                if(dp[i+1][carries]) {
                    int here = z+carries;
                    if(here%2==0&&sum[i]=='0') {
                        //possible!
                        int cHere = here/2;
                        dp[i][cHere]=true;
                    } 
                    if(here%2==1&&sum[i]=='1') {
                        int cHere = here/2;
                        dp[i][cHere]=true;
                    }
                }
            }
        }
        //last row
        int z=0,o=0;
        F0R(i, n) {
            if(values[i][0]=='0') {
                z++;
            } else {
                o++;
            }
        }
        if(sum[0]=='0') {
            if(dp[1][0]&&(z==0||o==0)) dp[0][0]=true;
        } else {
            if(dp[1][1]&&(z==0||o==0)) dp[0][0]=true;
            if(dp[1][0]&&(z==1||o==1)) dp[0][0]=true;
        }
        // cout << dp << endl;
        if(!dp[0][0]) {
            cout << -1 << endl;
        } else {
            string ans = "";
            int carries = 0;
            F0R(i, k) {
                z=0;
                o=0;
                F0R(j, n) {
                    if(values[j][i]=='0') z++;
                    else o++;
                }
                int needed = carries*2+(sum[i]=='1');
                for(int car = 0; car < 2*(carries+1)&&car<2*n+5; car++) {
                    if(dp[i+1][car]&&car+z==needed) {
                        ans+='1';
                        carries=car;
                        break;
                    } else if(dp[i+1][car]&&car+o==needed) {
                        ans+='0';
                        carries=car;
                        break;
                    }
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}
/*
2 8
00101001
10111111
10011110

10111111
0010
*/