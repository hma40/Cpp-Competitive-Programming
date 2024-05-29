#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Compare {
	bool operator()(int a, int b) {
		return a<b;
	}
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<int> indeg(n);
    vector<vector<int>> adj(n);
    while(m--) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        adj[b].push_back(a);
        indeg[a]++;
    }
    priority_queue<int, vector<int>, Compare> pq;
    for(int i = 0; i < n; i++) if(indeg[i]==0) pq.push(i);
    vector<int> order;
    while(pq.size()) {
        int x = pq.top();
        pq.pop();
        order.push_back(x);
        for(int y: adj[x]) {
            indeg[y]--;
            if(indeg[y]==0) {
                pq.push(y);
            }
        }
    }
    vector<int> labels(n);
    for(int i = n-1; i >= 0; i--) {
        labels[order[i]]=n-i;
    }
    cout << labels[0];
    for(int i = 1; i < n; i++) cout << " " << labels[i];
    cout << endl;
}