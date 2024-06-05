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
    int n;
    cin >> n;
    vt<vt<int>> color(n);
    F0R(i, n) color[i].resize(i+1);
    F0R(i, n) {
        F0R(j, color[i].size()) {
            cin >> color[i][j];
        }
    }
    vt<vt<short>> DLRed(n, vt<short>(n+1)), DLGreen(n, vt<short>(n+1)), DLBlue(n, vt<short>(n+1));
    //first parameter: take column number. Second parameter: take row number + 1
    F0R(i, n){
        FOR(j, i, n) {
            DLRed[i][j+1]+=DLRed[i][j];
            DLGreen[i][j+1]+=DLGreen[i][j];
            DLBlue[i][j+1]+=DLBlue[i][j];
            if(color[j][i]==1) {
                DLRed[i][j+1]++;
            } else if(color[j][i]==2) {
                DLGreen[i][j+1]++;
            } else {
                DLBlue[i][j+1]++;
            }
        }
    }
    vt<vt<short>> DRRed(n, vt<short>(n+1)), DRGreen(n, vt<short>(n+1)), DRBlue(n, vt<short>(n+1));
    //first parameter: (row number)-(col number). Second parameter: row+1
    F0R(i, n) {
        FOR(j, i, n) {
            DRRed[i][j+1]+=DRRed[i][j];
            DRGreen[i][j+1]+=DRGreen[i][j];
            DRBlue[i][j+1]+=DRBlue[i][j];
            if(color[j][j-i]==1) {
                DRRed[i][j+1]++;
            } else if(color[j][j-i]==2) {
                DRGreen[i][j+1]++;
            } else {
                DRBlue[i][j+1]++;
            }
        }
    }
    vt<vt<short>> hRed(n, vt<short>(n+1)), hGreen(n, vt<short>(n+1)), hBlue(n, vt<short>(n+1));
    //row,col+1
    F0R(i, n) {
        F0R(j, i+1) {
            hRed[i][j+1]+=hRed[i][j];
            hGreen[i][j+1]+=hGreen[i][j];
            hBlue[i][j+1]+=hBlue[i][j];
            if(color[i][j]==1) {
                hRed[i][j+1]++;
            } else if(color[i][j]==2) {
                hGreen[i][j+1]++;
            } else {
                hBlue[i][j+1]++;
            }
        }
    }
    // vt<vt<vt<int>>> dp(n+1, vt<vt<int>>(n+1));
    vt<vt<int>> dp(n+1, vt<int>(n+1));
    //dp[size][botleftrow][botleftcol]
    FOR(size, 2, n+1) {
        vt<vt<int>> cur(n+1, vt<int>(n+1));
        FOR(row, size-1, n) {
            F0R(col, row-size+2) {
                
                //try to remove horiz
                int maxHoriz = max(hGreen[row][col+size]-hGreen[row][col], max(hRed[row][col+size]-hRed[row][col], hBlue[row][col+size]-hBlue[row][col]));
                cur[row][col]=max(cur[row][col], dp[row-1][col]+maxHoriz);

                int rStart = row-size+1;
                int maxDL = max(DLRed[col][row+1]-DLRed[col][rStart], max(DLBlue[col][row+1]-DLBlue[col][rStart], DLGreen[col][row+1]-DLGreen[col][rStart]));

                cur[row][col]=max(cur[row][col], dp[row][col+1]+maxDL);
                int colNum = row-(col+size-1);
                int maxDR = max(DRRed[colNum][row+1]-DRRed[colNum][rStart], max(DRBlue[colNum][row+1]-DRBlue[colNum][rStart], DRGreen[colNum][row+1]-DRGreen[colNum][rStart]));
                // cout << size << " " << row << " " << col << " " << row-col-1 << " " << rStart << " " << maxDR << endl;
                // cout << DRGreen[row-col-1][row+1] << " " << DRGreen[row-col-1][rStart] << endl;
                cur[row][col]=max(cur[row][col], dp[row][col]+maxDR);
            }
        }
        swap(cur,dp);
    }
    cout << dp[n-1][0] << endl;
    // cout << DRRed << endl << DRBlue << endl << DRGreen << endl;
    return 0;
}