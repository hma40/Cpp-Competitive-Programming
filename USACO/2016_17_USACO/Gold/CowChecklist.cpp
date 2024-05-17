#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<pair<int, int>> hc;
vector<pair<int, int>> gc;
ll dist(bool firstIsH, bool secondIsH, int firstIndex, int secondIndex) {
    pair<int, int> first = (firstIsH? hc[firstIndex]:gc[firstIndex]);
    pair<int, int> second = (secondIsH? hc[secondIndex]:gc[secondIndex]);
    return (first.first-second.first)*(first.first-second.first)+(first.second-second.second)*(first.second-second.second);
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    int h,g;
    cin >> h >> g;

    for(int i = 0; i < h; i++) {
        pair<int, int> temp;
        cin >> temp.first >> temp.second;
        hc.push_back(temp);
    }
    for(int i = 0; i < g; i++) {
        pair<int, int> temp;
        cin >> temp.first >> temp.second;
        gc.push_back(temp);
    }
    ll func[h+1][g+1][2];
    for(int i = 0; i <= h; i++) {
        for(int j = 0; j <= g; j++) {
            for(int k = 0; k < 2; k++) {
                func[i][j][k]=-1;
            }
        }
    }
    func[1][0][0]=0;
    for(int i = 1; i <= hc.size(); i++) {
        for(int j = 0; j <= gc.size(); j++) {
            for(int k = 0; k < 2; k++) {
                if(i==1&&j==0) continue;
                if(j==0) {
                    if(k==0) {
                        func[i][j][k]=func[i-1][j][k]+dist(true, true, i-2, i-1);
                    } 
                    continue;
                }
                if(k==0) {
                    ll firstResult=-1;
                    if(func[i-1][j][0]!=-1) {
                        firstResult=func[i-1][j][0]+dist(true, true, i-2, i-1);
                    }
                    ll secondResult = -1;
                    if(func[i-1][j][1]!=-1) {
                        secondResult=func[i-1][j][1]+dist(false, true, j-1, i-1);
                    }
                    if(firstResult==-1) {
                        func[i][j][k]=secondResult;
                    } else if(secondResult==-1) {
                        func[i][j][k]=firstResult;
                    } else {
                        func[i][j][k]=min(firstResult, secondResult);
                    }
                }
                if(k==1) {
                    ll firstResult=-1;
                    if(func[i][j-1][0]!=-1) {
                        firstResult=func[i][j-1][0]+dist(true, false, i-1, j-1);
                    }
                    ll secondResult = -1;
                    if(func[i][j-1][1]!=-1) {
                        secondResult=func[i][j-1][1]+dist(false, false, j-2, j-1);
                    }
                    if(firstResult==-1) {
                        func[i][j][k]=secondResult;
                    } else if(secondResult==-1) {
                        func[i][j][k]=firstResult;
                    } else {
                        func[i][j][k]=min(firstResult, secondResult);
                    }
                }
            }
        }
    }
    cout << func[h][g][0] << endl;
}