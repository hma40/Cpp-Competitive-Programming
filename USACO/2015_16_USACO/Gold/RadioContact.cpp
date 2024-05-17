#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll dist(pair<int, int> f, pair<int, int> b) {
    return (f.first-b.first)*(f.first-b.first)+(f.second-b.second)*(f.second-b.second);
}
int main() {
    ios_base::sync_with_stdio(false); 
    std::cin.tie(0);
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    vector<pair<int, int>> fLoc;
    vector<pair<int, int>> bLoc;
    pair<int, int> fPos, bPos;
    std::cin >> fPos.first >> fPos.second >> bPos.first >> bPos.second;
    fLoc.push_back(fPos);
    bLoc.push_back(bPos);
    string a,b;
    std::cin >> a >> b;
    for(char c: a) {
        if(c=='N') {
            fPos.second++;
        } else if(c=='E') {
            fPos.first++;
        } else if(c=='S') {
            fPos.second--;
        } else {
            fPos.first--;
        }
        fLoc.push_back(fPos);
    }
    for(char c: b) {
        if(c=='N') {
            bPos.second++;
        } else if(c=='E') {
            bPos.first++;
        } else if(c=='S') {
            bPos.second--;
        } else {
            bPos.first--;
        }
        bLoc.push_back(bPos);
    }
    ll func[n+1][m+1];
    func[0][0]=0;
    for(int i = 1; i <= n; i++) {
        func[i][0]=func[i-1][0]+dist(fLoc[i], bLoc[0]);
    }
    for(int i = 1; i <= m; i++) {
        func[0][i]=func[0][i-1]+dist(fLoc[0], bLoc[i]);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            func[i][j]=min(func[i-1][j-1],min(func[i][j-1], func[i-1][j]))+dist(fLoc[i], bLoc[j]);
        }
    }
    std::cout << func[n][m] << endl;
}