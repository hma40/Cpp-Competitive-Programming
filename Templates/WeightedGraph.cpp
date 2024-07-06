#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
struct DSU {
    int n;
    vt<int> par;
    vt<int> sz;
    DSU(int nn): n(nn), par(n, -1), sz(n, 1){}
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(sz[x]>sz[y]) swap(x,y);
        sz[y]+=sz[x];
        par[x]=y;
    }
};
struct WeightedGraph {
    vt<vt<pair<int,int>>> adj;
    vt<vt<pair<int,int>>> MSF;
    vt<int> dist;
    int n;
    WeightedGraph(vt<vt<pair<int,int>>> a): adj(a), n(adj.size()) {
    }
    void dijkstra(int start) {
        dist.assign(n, inf);
        dist[start]=0;
        priority_queue<pair<int,int>> pq;
        pq.push({0,start});
        vt<bool> vis(n);
        // vis[start]=true;
        while(pq.size()) {
            auto top = pq.top();
            pq.pop();
            if(vis[top.s]) continue; 
            vis[top.s]=true;
            trav(x, adj[top.s]) {
                int newdist = x.s-top.f;
                if(newdist<dist[x.f]) {
                    dist[x.f]=newdist;
                    pq.push({-newdist, x.f});
                }
            }
        }
    }
    void getMSF() {
        DSU d(n);
        priority_queue<vt<int>> pq;
        F0R(i, n) {
            trav(x, adj[i]) {
                if(x.f>i) {
                    pq.push({-x.s, i, x.f});
                }
            }
        }
        MSF.assign(n, vt<pair<int,int>>());
        while(pq.size()) {
            auto top = pq.top();
            pq.pop();
            if(d.find(top[1])==d.find(top[2])) continue;
            MSF[top[1]].add({top[2], -top[0]});
            MSF[top[2]].add({top[1], -top[0]});
            d.unite(top[1], top[2]);
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    vt<vt<pair<int,int>>> adj(5);
    adj[0].add({1,3});
    adj[0].add({4,7});
    adj[1].add({0,3});
    adj[1].add({3,2});
    adj[1].add({2,5});
    adj[2].add({1,5});
    adj[2].add({3,8});
    adj[3].add({1,2});
    adj[3].add({2,8});
    adj[3].add({4,4});
    adj[4].add({0,7});
    adj[4].add({3,4});
    WeightedGraph w(adj);
    w.getMSF();
    cout << w.MSF << endl;
    w.dijkstra(0);
    cout << w.dist << endl;
    return 0;
}