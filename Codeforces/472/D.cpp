#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    int distances[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> distances[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        if(distances[i][i]!=0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(distances[i][j]!=distances[j][i]||distances[i][j]==0) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    vector<bool> visited(n);
    vector<int> minDist(n);
    vector<int> from(n);
    visited[0]=true;
    vector<vector<pair<int, int>>> edges(n);
    for(int i = 1; i < n; i++) {
        minDist[i]=distances[0][i];
    }
    for(int i = 1; i < n; i++) {
        int minIndex = -1;
        for(int j = 0; j < n; j++) {
            if(visited[j]) continue;
            if(minIndex==-1||minDist[j]<minDist[minIndex]) {
                minIndex=j;
            }
        }
        edges[minIndex].push_back({from[minIndex], minDist[minIndex]});
        edges[from[minIndex]].push_back({minIndex, minDist[minIndex]});
        visited[minIndex]=true;
        for(int j = 0; j < n; j++) {
            if(visited[j]) continue;
            if(distances[j][minIndex]<minDist[j]) {
                minDist[j]=distances[j][minIndex];
                from[j]=minIndex;
            }
        }
    }
    vector<vector<int>> calculatedDist(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        vector<bool> visited(n);
        visited[i]=true;
        deque<int> q;
        q.push_back(i);
        while(q.size()) {
            int x = q.front();
            q.pop_front();
            for(pair<int, int> y: edges[x]) {
                if(visited[y.first]) continue;
                visited[y.first]=true;
                calculatedDist[i][y.first]=calculatedDist[i][x]+y.second;
                q.push_back(y.first);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(distances[i][j]!=calculatedDist[i][j]) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
}