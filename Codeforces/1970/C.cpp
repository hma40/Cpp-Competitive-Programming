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
#define int long long
ll mod = 1000000007;
ll inf = 1e15;
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
vector<vector<int>> adj;
vector<bool> win;
vector<bool> ans;
vector<int> vis;
void dfs(int node, int par) {
    // cout << "DFSING " << node << endl;
    if(par!=-1&&adj[node].size()==1) {
        win[node]=false;
    }
    trav(x, adj[node]) {
        if(x==par) continue;
        dfs(x, node);
        if(!win[x]) win[node]=true;
    }
}
void reroot(int node, int par) {
    if(vis[node]>2) return;
    vis[node]++;
    // cout << "REROOTING " << node << " " << par << endl;
    ans[node]=win[node];
    vector<int> w;
    if(!win[node]) {
        trav(x, adj[node]) {
            if(x!=par) {
                // cout << "ABOUT TO CALL REROOT LINE 77 " << x << " " << node << endl;
                reroot(x, node);
            }
        }
    } else {
        trav(x, adj[node]) {
            if(!win[x]) w.add(x); 
        }
        if(w.size()>1) {
            trav(x, adj[node]) {
                if(x!=par) {
                    reroot(x, node);
                }
            }
        } else {
            // cout << "LINE 91 " << node << endl;
            if(w[0]!=par) {
                win[node]=false;
                win[w[0]]=true;
                reroot(w[0], node);
                win[w[0]]=false;
                win[node]=true;
            }
            trav(x, adj[node]) {
                if(x!=par&&x!=w[0]) {
                    // cout << "ABOUT TO CALL REROOT " << x << " " << node << endl;
                    reroot(x, node);
                }
            }
        }
    }
    
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,t;
    cin >> n >> t;
    win.resize(n);
    adj.resize(n);
    ans.resize(n);
    vis.resize(n);
    F0R(i, n-1) {
        int x,y;
        cin >> x >> y;
        adj[--x].add(--y);
        adj[y].add(x);
    }
    dfs(0, -1);
    reroot(0, -1);
    F0R(i, t) {
        int x;
        cin >> x;
        if(ans[x-1]) {
            cout << "Ron" << endl;
        } else {
            cout << "Hermione" << endl;
        }
    }
    return 0;
}
