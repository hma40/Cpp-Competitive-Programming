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
        int n,m;
        cin >> n >> m;
        vt<string> v(n);
        F0R(i,n) cin >> v[i];
        vt<vt<int>> on(n, vt<int>(m, 1)), off(n, vt<int>(m, 1));
        F0R(i, n) {
            F0R(j, m) {
                on[i][j]=rnd();
                off[i][j]=rnd();
            }
        }
        vt<int> noChange(n), change(n);
        F0R(i, n) {
            F0R(j, m) {
                if(v[i][j]=='0') {
                    noChange[i]^=off[i][j];
                    change[i]^=on[i][j];
                } else {
                    noChange[i]^=on[i][j];
                    change[i]^=off[i][j];
                }
            }
        }
        map<int,int> mp;
        F0R(i, m) {
            //fix 0,i to be the only 1 in this col
            int hash = 0;
            if(v[0][i]=='1') {
                hash^=noChange[0];
            } else {
                hash^=change[0];
            }
            FOR(j, 1, n) {
                if(v[j][i]=='0') {
                    hash^=noChange[j];
                } else {
                    hash^=change[j];
                }
            }
            mp[hash]++;
            FOR(j, 1, n) {
                hash^=noChange[j-1];
                hash^=change[j-1];
                hash^=noChange[j];
                hash^=change[j];
                mp[hash]++;
            }
        }
        // cout << mp << endl;
        int best = 0, hVal = 0;
        trav(x, mp) {
            if(x.s>best) {
                best=x.s;
                hVal=x.f;
            }
        }
        string ans = "";
        bool done = false;
        F0R(i, m) {
            //fix 0,i to be the only 1 in this col
            int hash = 0;
            if(v[0][i]=='1') {
                hash^=noChange[0];
            } else {
                hash^=change[0];
            }
            FOR(j, 1, n) {
                if(v[j][i]=='0') {
                    hash^=noChange[j];
                } else {
                    hash^=change[j];
                }
            }
            if(hash==hVal) {
                if(v[0][i]=='1') {
                    ans+='0';
                } else {
                    ans+='1';
                }
                FOR(j, 1, n) {
                    if(v[j][i]=='1') {
                        ans+='1';
                    } else {
                        ans+='0';
                    }
                }
                done=true;
            }
            if(done) break;
            FOR(j, 1, n) {
                hash^=noChange[j-1];
                hash^=change[j-1];
                hash^=noChange[j];
                hash^=change[j];
                if(hash==hVal) {
                    // cout << j << " " << i << endl;
                    F0R(k, j) {
                        if(v[k][i]=='0') {
                            ans+='0';
                        } else {
                            ans+='1';
                        }
                    }
                    if(v[j][i]=='1') {
                        ans+='0';
                    } else {
                        ans+='1';
                    }
                    FOR(k, j+1, n) {
                        if(v[k][i]=='0') {
                            ans+='0';
                        } else {
                            ans+='1';
                        }
                    }
                    done=true;
                    break;
                }
            }
            if(done) break;
        }
        cout << best << endl << ans << endl;
    }

    return 0;
}
/*
1
20 20
10010110110001110101
01110001110011110000
10100011110110111011
00101011110110111010
10110000100010000110
00100101010100100110
00111010110110100110
00011011000001111011
00000101010011110011
01010101001101101010
11101010011111001000
01010011101110101000
00001010000111100011
01101100010001011011
11100111000101101100
00101000011001000111
10001010110101110000
01010010100001110000
01011101100100010101
00110111100000011000

*/