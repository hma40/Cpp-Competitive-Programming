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
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> v(n);
        F0R(i,n) cin >> v[i].f >> v[i].s;
        vt<int> defInc(n);
        F0R(i, n) {
            R0F(j, 30) {
                int f = v[i].f&(1<<j);
                int s = v[i].s&(1<<j);
                if(f==s) {
                    defInc[i]|=f;
                } else {
                    break;
                }
            }
            v[i].f-=defInc[i];
            v[i].s-=defInc[i];
        }
        // cout << v << defInc << endl;
        vt<vt<int>> defIncPref(n+1, vt<int>(30));
        vt<vt<int>> vPref(n+1, vt<int>(30));
        F0R(i, n) {
            F0R(j, 30) {
                if(v[i].s&(1<<j)) {
                    vPref[i+1][j]=vPref[i][j]+1;
                } else {
                    vPref[i+1][j]=vPref[i][j];
                }
                defIncPref[i+1][j]=defIncPref[i][j];                
                if(defInc[i]&(1<<j)) {
                    defIncPref[i+1][j]++;
                }
            }
        }
        // cout << defIncPref << endl << vPref << endl;
        int q;
        cin >> q;
        while(q--) {
            int l,r;
            cin >> l >> r;
            r--;
            l--;
            int ans = 0;
            F0R(i, 30) {
                if(defIncPref[r+1][i]-defIncPref[l][i]) {
                    ans|=(1<<i);
                }
            }
            bool done = false;
            R0F(i, 30) {
                if(done) break;
                // if(ans&(1<<i)) continue;
                int count = vPref[r+1][i]-vPref[l][i]+((ans&(1<<i))?1:0);
                // cout << l << " " << r << " " << i << " " << count << endl;
                // cout << vPref[r+1][i] << " " << vPref[l][i] << " " << (ans&(1<<i)) << endl;
                if(count==1) {
                    ans|=(1<<i);
                } else if(count>1) {
                    ans|=(1<<i);
                    R0F(j, i) {
                        ans|=(1<<j);
                        done=true;
                    }
                }
            }
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
1
4
1 7
1 7
3 10
2 2
1
3 4
*/
/*
7 7 10 0
*/