#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n,m;
vector<set<int>> adj, radj;
vector<int> ans;
vector<int> parents;
void debug() {
    for(int i = 0; i < n; i++) {
        cout << "[";
        for(int j: adj[i]) cout << j << ", ";
        cout << "],";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        cout << "[";
        for(int j: radj[i]) cout << j << ", ";
        cout << "],";
    }
    cout << endl;
}
void merge(int a, int b) {
    if(adj[a].size()<adj[b].size()) swap(a,b);
    //cout << "merge called for " << a << ", " << b << endl;
    parents[b]=a;
    for(int x: adj[b]) {
        radj[x].erase(b);
        radj[x].insert(a);
        adj[a].insert(x);
    }
    for(int x: radj[b]) {
        adj[x].erase(b);
        adj[x].insert(a);
        radj[a].insert(x);
    }
    adj[b].clear();
    radj[b].clear();
}
int get(int x) {
    if(parents[x]==-1) return x;
    return parents[x]=get(parents[x]);
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    cin >> n >> m;
    parents.resize(n, -1);
    adj.resize(n);
    radj.resize(n);
    for(int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        adj[--a].insert(--b);
        radj[b].insert(a);
    }
    //debug();
    queue<int> q;
    ans.resize(n);
    for(int i = 0; i < n; i++) {
        if(adj[i].size()>1) q.push(i);
    }
    while(q.size()) {
        int x = q.front();
        q.pop();
        x=get(x);
        //cout << x << endl;
        //debug();
        while(adj[x].size()>1) {
            merge(*adj[x].begin(), *(++adj[x].begin()));
        }
        if(adj[*adj[x].begin()].size()>1) q.push(*adj[x].begin());
    }
    int next = 1;
    for(int i = 0; i < n; i++) {
        if(ans[get(i)]==0) {
            ans[get(i)]=next;
            next++;
        }
    }
    string answ;
    for(int i = 0; i < n; i++) {
        answ+=to_string(ans[get(i)])+"\n";
    }
    cout << answ;
}