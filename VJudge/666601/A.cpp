#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n,m,w;
    cin >> n >> m >> w;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u,v,t;
        cin >> u >> v >> t;
        u--;
        v--;
        adj[u].push_back({v,t});
    }
    vector<int> best(n, -1e18);
    best[0]=0;
    priority_queue<pair<int,int>> pq;
    pq.push({0, 0});
    while(pq.size()) {
        auto f = pq.top();
        // cout << f.first << " " << f.second << endl;
        pq.pop();
        if(f.first!=best[f.second]) continue;
        for(auto x: adj[f.second]) {
            int nw = f.first+x.second;
            nw=min(nw, w);
            if(nw>best[x.first]) {
                best[x.first]=nw;
                pq.push({nw, x.first});
            }
        }
    }
    cout << best[n-1] << endl;
}