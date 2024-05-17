#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int m,n,t, current;
vector<vector<ll>> ans;
struct Border {
    int distance, first, second;
    Border(int dist, int f, int s) {
        distance=dist;
        first=f;
        second=s;
    }
};
int toInt(int x, int y) {
    return x*n+y;   
}
bool outOfBounds(int x, int y) {
    return x<0||y<0||x>=m||y>=n;
}
struct DisjointSet {
    vector<int> parents, sizes;
    vector<vector<int>> children;
    DisjointSet(int n) {
        parents = vector<int>(n, -1);
        sizes = vector<int>(n, 1);
        children = vector<vector<int>>(n);
    }
    int find(int x) {
        if(parents[x]==-1) return x;
        parents[x]=find(parents[x]);
        return parents[x];
    }
    void fillElevations(int root) {
        //cout << "fill elevations" << endl;
        ans[root/n][root%n]=current;
        for(int i: children[root]) {
            fillElevations(i);
        }
    }
    bool combine(int x, int y) {
        int rootX = find(x), rootY = find(y);
        //cout << rootX << " " << rootY << endl;
        if(rootX==rootY) return false;
        bool done = false;
        if(sizes[rootX]<sizes[rootY]) {
            if(sizes[rootY]>=t) {
                done = true;
                if(sizes[rootX]<t) {
                    fillElevations(rootX);
                }
            }
            parents[rootX]=rootY;
            sizes[rootY]+=sizes[rootX];
            children[rootY].push_back(rootX);
            if(!done&&sizes[rootY]>=t) {
                fillElevations(rootY);
            }
        } else {
            if(sizes[rootX]>=t) {
                done=true;
                if(sizes[rootY]<t) {
                    fillElevations(rootY);
                }
            }
            parents[rootY]=rootX;
            sizes[rootX]+=sizes[rootY];
            children[rootX].push_back(rootY);
            if(!done&&sizes[rootX]>=t) {
                fillElevations(rootX);
            }
        }
        return true;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    cin >> m >> n >> t;
    vector<vector<int>> elevations = vector<vector<int>>(m, vector<int>(n));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> elevations[i][j];
        }
    }
    ans = vector<vector<ll>>(m, vector<ll>(n));
    if(t==1) {
        cout << 0 << endl;
        return 0;
    }
    vector<Border> borders;
    int dx[4] = {0,0,-1,1};
    int dy[4] = {-1,1,0,0};
    //cout << "Got here 0 " << endl;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 4; k++) {
                int newI = i+dx[k];
                int newJ = j+dy[k];
                if(!outOfBounds(newI, newJ)&&toInt(i,j)>toInt(newI,newJ)) {
                    borders.push_back(Border(abs(elevations[newI][newJ]-elevations[i][j]), toInt(i,j), toInt(newI, newJ)));
                }
            }
        }
    }
    sort(begin(borders), end(borders), [](const Border a, const Border b)->bool{
       return a.distance<b.distance; 
    });
    DisjointSet ds(m*n);
    //cout << "got here" << endl;
    for(int i = 0; i < borders.size(); i++) {
        //cout << i << endl;
        current = borders[i].distance;
        ds.combine(borders[i].first, borders[i].second);
    }

    ll answ = 0;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int temp;
            cin >> temp;
            if(temp==1) {
                answ+=ans[i][j];
            }
        }   
    }
    cout << answ << endl;
}