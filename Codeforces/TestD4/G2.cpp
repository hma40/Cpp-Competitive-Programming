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
        vt<string> v(n);
        F0R(i, n) {
            cin >> v[i];
        }
        if(n==1||m==1) {
            cout << n*m << endl;
            continue;
        }
        vt<int> rowCount(n), colCount(m);
        F0R(i, n) {
            F0R(j, m) {
                if(v[i][j]=='#') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }
        vt<vt<int>> ans(n, vt<int>(m));
        vt<vt<bool>> vis(n, vt<bool>(m));
        vt<int> rowAdd(n+3), colAdd(m+3);
        vt<vt<int>> pointAdd(n+3, vt<int>(m+3));
        vt<pair<int, int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        F0R(i, n) {
            F0R(j, m) {
                if(vis[i][j]) continue;
                if(v[i][j]=='.') continue;
                vis[i][j]=true;
                int size = 1;
                deque<pair<int, int>> q;
                pair<int, int> xBound = {i,i}, yBound = {j,j}; 
                q.push_back({i,j});
                while(q.size()) {
                    auto first = q.front();
                    q.pop_front();
                    xBound.f=min(xBound.f, first.f);
                    xBound.s=max(xBound.s, first.f);
                    yBound.f=min(yBound.f, first.s);
                    yBound.s=max(yBound.s, first.s);
                    trav(x, dir) {
                        pair<int,int> next = {first.f+x.f, first.s+x.s};
   
                        if(next.f>=0&&next.f<n&&next.s>=0&&next.s<m) {
                            if(!vis[next.f][next.s]&&v[next.f][next.s]=='#') {
                                // cout << next << endl;
                                vis[next.f][next.s]=true;
                                size++; 
                                q.push_back(next);
                            }
                        }
                    }
                }   
                int bx=0,cx=0;
                if(xBound.f==0) {
                    bx=0;
                } else bx=xBound.f-1;
                if(yBound.f==0) {
                    cx=0;
                } else cx=yBound.f-1;
                pointAdd[bx][cx]-=size;
                pointAdd[xBound.s+2][cx]+=size;
                pointAdd[bx][yBound.s+2]+=size;
                pointAdd[xBound.s+2][yBound.s+2]-=size;
                rowAdd[bx]+=size;
                colAdd[cx]+=size;
                rowAdd[xBound.s+2]-=size;
                colAdd[yBound.s+2]-=size;
            }
        }
        // cout << rowAdd << " " << colAdd << endl;
        FOR(i, 1, n) {
            rowAdd[i]+=rowAdd[i-1];
        }
        FOR(i, 1, m) {
            colAdd[i]+=colAdd[i-1];
        }
        FOR(i, 1, n) {
            pointAdd[i][0]+=pointAdd[i-1][0];
        }
        FOR(i, 1, m) {
            pointAdd[0][i]+=pointAdd[0][i-1];
        }
        FOR(i, 1, n) {
            FOR(j, 1, m) {
                pointAdd[i][j]+=pointAdd[i][j-1]+pointAdd[i-1][j]-pointAdd[i-1][j-1];
            }
        }
        // cout << pointAdd << endl;
        // cout << rowAdd << " " << colAdd << endl;
        F0R(i, n) {
            F0R(j, m) {
                // cout << i << " " << j << endl << rowCount[i] << " " << colCount[j] << " " << rowAdd[i] << " " << colAdd[j] << " " << pointAdd[i][j] << endl;
                ans[i][j]=n+m-1-rowCount[i]-colCount[j]+rowAdd[i]+colAdd[j]+pointAdd[i][j];
                if(v[i][j]=='#') ans[i][j]++;
            }
        }
        int an = 0;
        // cout << ans << endl;
        F0R(i, n) {
            F0R(j, m) {
                an=max(an, ans[i][j]);
            }
        }
        cout << an << endl;
    }
    return 0;
}
/*
1
3 3
..#
#..
..#

*/