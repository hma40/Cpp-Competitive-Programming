#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> names(n);
    for(int i = 0; i < n; i++) cin >> names[i];
    vector<vector<int>> adj(26);
    vector<int> indeg(26);
    for(int i = 1; i < n; i++) {
        bool done = false;
        for(int j = 0; j < names[i].size()&&j<names[i-1].size(); j++) {
            if(names[i][j]!=names[i-1][j]) {
                adj[names[i-1][j]-'a'].push_back(names[i][j]-'a');
                indeg[names[i][j]-'a']++;
                done=true;
                break;
            }
        }
        if(!done&&names[i].size()<names[i-1].size()) {
            cout << "Impossible" << endl;
            return 0;
        }
    }
    deque<int> q;
    string s;
    for(int i = 0; i < 26; i++) {
        if(indeg[i]==0) q.push_back(i);
    }
    while(q.size()) {
        int x = q.front();
        q.pop_front();
        s+=char(x+'a');
        for(int y: adj[x]) {
            if(--indeg[y]==0) q.push_back(y);
        }
    }
    if(s.length()!=26) {
        cout << "Impossible" << endl;
    } else {
        cout << s << endl;
    }
}