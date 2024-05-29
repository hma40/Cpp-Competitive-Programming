#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool match(string pattern, string s) {
    for(int i = 0; i < s.length(); i++) {
        if(pattern[i]!='_'&&pattern[i]!=s[i]) return false;
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> order;
    vector<string> patterns(n);
    vector<pair<string, int>> strings(m);
    map<string, int> pat;
    for(int i = 0; i < n; i++) {
        cin >> patterns[i];
        pat[patterns[i]]=i;
    }
    for(int i = 0; i < m; i++) {
        cin >> strings[i].first >> strings[i].second;
        if(!match(patterns[--strings[i].second], strings[i].first)) {
            cout << "NO" << endl;
            return 0;
        }
    }
    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    for(pair<string, int> p: strings) {
        vector<int> matches;
        for(int mask = 0; mask < (1<<k); mask++) {
            string newstr = p.first;
            for(int i = 0; i < k; i++) {
                if(mask&(1<<i)) {
                    newstr[i]='_';
                }
            }
            if(pat.count(newstr)) {
                matches.push_back(pat[newstr]);
            }
        }
        for(int i: matches) {
            if(i!=p.second) {
                adj[p.second].push_back(i);
                indeg[i]++;
            }
        }
    }
    deque<int> q;
    for(int i = 0; i < n; i++) {
        if(indeg[i]==0) q.push_back(i); 
    }
    while(q.size()) {
        int x = q.front();
        q.pop_front();
        order.push_back(x);
        for(int y: adj[x]) {
            if(--indeg[y]==0) {
                q.push_back(y);
            }
        }
    }
    if(order.size()!=n) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << order[0]+1;
        for(int i = 1; i < n; i++) {
            cout << " " << 1+order[i];
        }
        cout << endl;
    }
}