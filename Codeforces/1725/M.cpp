#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 1000000007;
bool debug = true;
vector<string> split(string s, char delimiter) {
    vector<string> ret;
    ret.push_back("");
    F0R(i, s.length()) {
        if(s[i]==delimiter) {
            ret.add("");
        } else {
            ret.back()+=s[i];
        }
    }
    return ret;
}
struct Compare {
    bool operator()(pair<pair<int, bool>, ll> a, pair<pair<int, bool>, ll> b) {
        return a.second>b.second;
    }
};
void printArray(vector<int> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<ll> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<string> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<vector<int>> &v) {
    if(debug) {
        cout << "{\n";
        trav(y, v) printArray(y);
        cout << "}" << endl;
    }
}
int main() {
    ll INF = 1e18;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> dist(n, vector<ll>(2, INF));
    vector<vector<pair<pair<int, bool>, ll>>> adj(n);
    vector<vector<bool>> vis(n, vector<bool>(2, false));
    F0R(i, m) {
        ll a,b,dist;
        cin >> a >> b >> dist;
        adj[--a].add({{--b, false}, dist});
        adj[b].add({{a,true},dist});
    }
    priority_queue<pair<pair<int, bool>, ll>, vector<pair<pair<int, bool>, ll>>, Compare> pq;
    F0R(i, n) {
        adj[i].add({{i, true}, 0});
    }
    dist[0][0]=0;
    pq.push({{0,false},0});
    while(pq.size()) {
        pair<pair<int, bool>, ll> p = pq.top();

        pq.pop();
        if(vis[p.f.f][p.f.s]) continue;
        vis[p.f.f][p.f.s]=true;
        trav(adjNode, adj[p.f.f]) {
            if(p.f.s) {
                if(adjNode.f.s) {
                    if(p.s+adjNode.s<dist[adjNode.f.f][1]) {
                        dist[adjNode.f.f][1]=p.s+adjNode.s;
                        pq.push({{adjNode.f.f, p.f.s}, dist[adjNode.f.f][1]});
                    }
                }
            } else {
                if(p.s+adjNode.s<dist[adjNode.f.f][adjNode.f.s]) {
                    dist[adjNode.f.f][adjNode.f.s]=p.s+adjNode.s;
                    pq.push({{adjNode.f.f, adjNode.f.s}, dist[adjNode.f.f][adjNode.f.s]});
                }
            }
        }
    }
    if(dist[1][1]==INF) {
        cout << -1;
    } else {
        cout << dist[1][1];
    }
    FOR(i, 2, n) {
        cout << " " << (dist[i][1]==INF? -1:dist[i][1]);
    }
    cout << endl;
    return 0;
}