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
struct Obj {
    int x, y;
    bool active;
    Obj(){}
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int a,b,n,m;
        cin >> a >> b >> n >> m;
        vt<pair<int, int>> byX(n), byY(n);
        map<pair<int, int>, bool> active;
        F0R(i, n) {
            cin >> byX[i].f >> byX[i].s;
            byY[i].f=byX[i].s;
            byY[i].s=byX[i].f;
            active[{byX[i].f, byX[i].s}]=true;
        }
        sort(begin(byX), end(byX));
        sort(begin(byY), end(byY));
        // cout << byX << " " << byY << endl;
        int xMin=1, xMax=a, yMin=1, yMax=b, byXStart=0, byXEnd=n-1, byYStart=0, byYEnd=n-1;
        int aAns=0, bAns=0;
        F0R(i, m) {
            // cout << "LINE 81 " << i << endl;
            char c;
            int x;
            cin >> c >> x;
            if(c=='U') {
                xMin+=x;
                while(byXStart<=byXEnd) {
                    if(byX[byXStart].f<xMin) {
                        if(active[{byX[byXStart].f, byX[byXStart].s}]) {
                            active[{byX[byXStart].f, byX[byXStart].s}]=false;
                            if(i%2) {
                                bAns++;
                            } else {
                                aAns++;
                            }
                        }
                        byXStart++;
                    } else {
                        break;
                    }
                }
            } else if(c=='D') {
                xMax-=x;
                while(byXStart<=byXEnd) {
                    if(byX[byXEnd].f>xMax) {
                        if(active[{byX[byXEnd].f, byX[byXEnd].s}]) {
                            active[{byX[byXEnd].f, byX[byXEnd].s}]=false;
                            if(i%2) {
                                bAns++;
                            } else {
                                aAns++;
                            }
                        }
                        byXEnd--;
                    } else {
                        break;
                    }
                }
            } else if(c=='L') {
                yMin+=x;
                while(byYStart<=byYEnd) {
                    if(byY[byYStart].f<yMin) {
                        if(active[{byY[byYStart].s, byY[byYStart].f}]) {
                            active[{byY[byYStart].s, byY[byYStart].f}]=false;
                            if(i%2) {
                                bAns++;
                            } else {
                                aAns++;
                            }
                        }
                        byYStart++;
                    } else {
                        break;
                    }
                }
            } else {
                yMax-=x;
                while(byYStart<=byYEnd) {
                    if(byY[byYEnd].f>yMax) {
                        if(active[{byY[byYEnd].s, byY[byYEnd].f}]) {
                            active[{byY[byYEnd].s, byY[byYEnd].f}]=false;
                            if(i%2) {
                                bAns++;
                            } else {
                                aAns++;
                            }
                        }
                        byYEnd--;
                    } else {
                        break;
                    }
                }
            }
        }
        cout << aAns << " " << bAns << endl;
    }
    return 0;
}
/*
4 4 3 2
4 1
3 3
2 4
D 2
R 1
*/