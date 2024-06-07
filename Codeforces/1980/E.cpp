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
        int n,m;
        cin >> n >> m;
        vt<vt<int>> bef(n, vt<int>(m)),aft(n, vt<int>(m));
        F0R(i, n) {
            F0R(j, m) cin >> bef[i][j];
        } 
        F0R(i, n) {
            F0R(j, m) cin >> aft[i][j];
        }
        F0R(i, n) {
            F0R(j, m) {
                bef[i][j]--;
                aft[i][j]--;
            }
        }
        vt<set<int>> befrow(n), befcol(m), aftrow(n), aftcol(m);
        vt<int> befRowNum(n*m),aftRowNum(n*m), befColNum(n*m), aftColNum(n*m); 
        F0R(i, n) {
            F0R(j, m) {
                befrow[i].insert(bef[i][j]);
                befcol[j].insert(bef[i][j]);
                aftrow[i].insert(aft[i][j]);
                aftcol[j].insert(aft[i][j]);
                befRowNum[bef[i][j]]=i;
                befColNum[bef[i][j]]=j;
                aftRowNum[aft[i][j]]=i;
                aftColNum[aft[i][j]]=j;
            }
        }
        bool fail = false;
        vt<bool> checkedRow(n*m), checkedCol(n*m);
        F0R(i,n) {
            F0R(j, m) {
                // int x = bef[i][j];
                if(!checkedRow[bef[i][j]]) {
                    auto befr = befrow[i];
                    set<int> aftr = aftrow[aftRowNum[bef[i][j]]];
                    if(befr==aftr) {
                        trav(x, befr) {
                            checkedRow[x]=true;
                        }
                    } else {
                        fail=true;
                        break;
                    }
                }
                if(!checkedCol[bef[i][j]]) {
                    auto befr = befcol[j];
                    auto aftr = aftcol[aftColNum[bef[i][j]]];
                    if(befr==aftr) {
                        trav(x, befr) {
                            checkedCol[x]=true;
                        }
                    } else {
                        fail=true;
                        break;
                    }
                }
            }
            if(fail) break;
        }
        if(fail) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}