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
vt<int> bin(int x) {
    vt<int> ret;
    R0F(i, 31) {
        if(x&(1<<i)) {
            ret.add(1);
        } else if(ret.size()) {
            ret.add(0);
        }
    }
    return ret;
}
int dist(int x, int y) {
    vt<int> xBin = bin(x), yBin=bin(y);
    int firstDiff = -1;
    F0R(i, min(xBin.size(), yBin.size())) {
        if(xBin[i]!=yBin[i]) {
            firstDiff=i;
            break;
        }
    }
    if(firstDiff==-1) {
        // cout << x << " " << y << " " << abs((int)(xBin.size()-yBin.size())) << endl;
        return abs((int)(xBin.size()-yBin.size()));
    }
    // cout << x << " " << y << " " << xBin.size()-firstDiff+yBin.size()-firstDiff << endl;
    return xBin.size()-firstDiff+yBin.size()-firstDiff;
}
vt<int> gtMo(int x, int y) {
    vt<int> xBin = bin(x), yBin=bin(y);
    vt<int> ret;
    int firstDiff = -1;
    F0R(i, min(xBin.size(), yBin.size())) {
        if(xBin[i]!=yBin[i]) {
            firstDiff=i;
            break;
        }
    }
    ret.add(x);
    if(firstDiff!=-1) {
        while(xBin.size()>firstDiff) {
            ret.add(ret.back()/2);
            xBin.pop_back();
        }

    } 
    // cout << xBin << " " << yBin << endl;
    if(xBin.size()>yBin.size()) {
        while(x>y) {
            ret.add(ret.back()/2);
            x/=2;
        }
    } else {
        FOR(i, xBin.size(), yBin.size()) {
            if(yBin[i]==0) {
                ret.add(ret.back()*2);
            } else {
                ret.add(ret.back()*2+1);
            }
        }
    }
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // cout << gtMo(7,3) << endl;
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        vt<pair<int, int>> ind;
        F0R(i, n) {
            if(v[i]!=-1) {
                ind.add({i, v[i]});
            }
        }
        bool imp = false;
        FOR(j, 1, ind.size()) {
            int moves = dist(ind[j-1].s, ind[j].s);
            int actualDist = ind[j].f-ind[j-1].f;
            if(moves%2!=actualDist%2) {
                imp=true;
            } else if(moves>actualDist) {
                imp=true;
            } else {
                vt<int> mo = gtMo(ind[j-1].s, ind[j].s);
                FOR(i, ind[j-1].f+1, ind[j].f) {
                    if(i-ind[j-1].f<mo.size()) {
                        v[i]=mo[i-ind[j-1].f];
                    } else {
                        if(v[i-1]<=ind[j].s) {
                            v[i]=v[i-1]*2;
                        } else {
                            v[i]=v[i-1]/2;
                        }
                    }
                }
            }
        }
        if(ind.size()==0) {
            v[0]=1;
            FOR(i, 1, n) {
                if(v[i-1]==1) {
                    v[i]=2;
                } else {
                    v[i]=1;
                }
            }
        } else {
            R0F(i, ind[0].f) {
                if(v[i+1]==1) {
                    v[i]=2;
                } else {
                    v[i]=v[i+1]/2;
                }
            }
            FOR(i, ind.back().f+1, n) {
                if(v[i-1]==1) {
                    v[i]=2;
                } else {
                    v[i]=v[i-1]/2;
                }
            }
        }
        if(imp) {
            cout << -1 << endl;
        } else {
            cout << v[0];
            FOR(i, 1, n) cout << " " << v[i];
            cout << endl;
        }
    }
    return 0;
}