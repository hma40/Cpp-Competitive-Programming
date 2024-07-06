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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<vt<int>> v(n, vt<int>(3));
        F0R(i, n) cin >> v[i][0] >> v[i][1] >> v[i][2];
        // sort(begin(v),end(v));
        vt<vt<pair<int,int>>> adj(n);
        priority_queue<vt<int>> pq;
        F0R(i, n) {
            pq.push({-v[i][0], 2, i});
            pq.push({-v[i][1], 1, i});
        }
        DSU d(n);
        set<pair<int,int>> s;
        s.insert({-inf, -inf});
        s.insert({inf,inf});
        while(pq.size()) {
            auto top = pq.top();
            pq.pop();
            if(top[1]==2) {
                vt<int> h;
                h.add(top[2]);
                while(pq.top()[0]==top[0]&&pq.top()[1]==2) {
                    h.add(pq.top()[2]);
                    pq.pop();
                }
                trav(x, h) {
                    s.insert({v[x][2], x});
                }
                trav(x, h) {
                    auto ub = s.upper_bound({v[x][2], x});
                    auto lb = s.lower_bound({v[x][2], x});
                    --lb;
                    if((*ub).f==v[x][2]) {
                        // cout << "LINE 110" << endl;
                        d.unite((*ub).s, x);
                    }
                    if((*lb).f==v[x][2]) {
                        // cout << "LINE 114" << endl;
                        d.unite((*lb).s, x);
                    }
                    auto before = s.lower_bound({v[x][2], 0});
                    --before;
                    auto after = s.upper_bound({v[x][2], inf});
                    // cout << x << " " << *before << " " << *after << endl;
                    if((*before).f!=-inf) {
                        adj[(*before).s].add({x, abs((*before).f-v[x][2])});
                        adj[x].add({(*before).s, abs((*before).f-v[x][2])});
                    }
                    if((*after).f!=inf) {
                        adj[(*after).s].add({x, abs((*after).f-v[x][2])});
                        adj[x].add({(*after).s, abs((*after).f-v[x][2])});
                    }
                }
            } else {
                s.erase({v[top[2]][2], top[2]});
            }
            // cout << top << s << endl;
        }
        // cout << adj << endl;
        int ans = 0;
        F0R(i, n) {
            trav(x, adj[i]) {
                if(x.f>i) {
                    pq.push({-x.s, i, x.f});
                }
            }
        }
        while(pq.size()) {
            auto top = pq.top();
            pq.pop();
            if(d.find(top[1])==d.find(top[2])) continue;
            ans-=top[0];
            d.unite(top[1], top[2]);
        }
        int check = d.find(0);
        FOR(i, 1, n) {
            if(d.find(i)!=check) {
                check=-1;
            }
        }
        if(check==-1) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}