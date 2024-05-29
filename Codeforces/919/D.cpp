#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m;
    string s;
    cin >> n >> m >> s;
    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    while(m--) {
        int a,b;
        cin >> a >> b;
        adj[--a].push_back(--b);
        indeg[b]++;
    }
    deque<int> q;
    for(int i = 0; i < n; i++) {
        if(indeg[i]==0) q.push_back(i);
    }
    vector<int> order;
    while(q.size()) {
        int x = q.front();
        q.pop_front();
        order.push_back(x);
        for(int y: adj[x]) 
            if(--indeg[y]==0) 
                q.push_back(y);
    }
    if(order.size()!=n) {
        cout << -1 << endl;
        return 0;
    }
    vector<vector<int>> mostLetters(n, vector<int>(26));
    for(int x: order) {
        mostLetters[x][s[x]-'a']++;
        for(int y: adj[x]) {
            for(int i = 0; i < 26; i++) {
                mostLetters[y][i]=max(mostLetters[y][i], mostLetters[x][i]);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 26; j++) {
            ans=max(ans, mostLetters[i][j]);
        }
    }
    cout << ans << endl;
}