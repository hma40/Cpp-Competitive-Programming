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
int n;
bool oob(int x, int y) {
    return x<0||y<0||x>=n||y>=n;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    cin >> n;
    vt<string> v(n);
    F0R(i, n) cin >> v[i];
    priority_queue<vt<int>, vt<vt<int>>, greater<vt<int>>> pq;
    pq.push({0,n-1,0});
    vt<vt<int>> dist(n, vt<int>(n, inf));
    vt<vt<bool>> vis(n, vt<bool>(n));
    dist[n-1][0]=0;
    vt<int> dx = {-1,1,0,0}, dy = {0,0,1,-1};
    while(pq.size()) {
        auto first = pq.top();
        pq.pop();
        if(vis[first[1]][first[2]]) continue;
        vis[first[1]][first[2]]=true;
        // if(dist[first[1]][first[2]]!=inf) continue;
        // dist[first[1]][first[2]]=first[0];
        F0R(i, 4) {
            int newx = first[1]+dx[i];
            int newy = first[2]+dy[i];
            if(oob(newx,newy)) continue;
            if(v[newx][newy]=='B') {
                if(dist[newx][newy]>first[0]) {
                    dist[newx][newy]=first[0];
                    pq.push({first[0], newx, newy});
                }
            } else {
                if(dist[newx][newy]>1+first[0]) {
                    dist[newx][newy]=1+first[0];
                    pq.push({1+first[0], newx, newy});
                }
            }
        }
    }
    // cout << dist << vis << endl;
    vt<vt<int>> dist2(n, vt<int>(n, inf));
    vis.clear();
    vis.resize(n, vt<bool>(n));
    dist2[n-1][n-1]=0;
    pq.push({0, n-1, n-1});
    while(pq.size()) {
        auto first = pq.top();
        pq.pop();
        if(vis[first[1]][first[2]]) continue;
        // cout << first << endl;
        vis[first[1]][first[2]]=true;
        // if(dist[first[1]][first[2]]!=inf) continue;
        // dist[first[1]][first[2]]=first[0];
        F0R(i, 4) {
            int newx = first[1]+dx[i];
            int newy = first[2]+dy[i];
            if(oob(newx,newy)) continue;
            if(v[newx][newy]=='R') {
                if(dist2[newx][newy]>first[0]) {
                    dist2[newx][newy]=first[0];
                    pq.push({first[0], newx, newy});
                }
            } else {
                if(dist2[newx][newy]>1+first[0]) {
                    dist2[newx][newy]=1+first[0];
                    pq.push({1+first[0], newx, newy});
                }
            }
        }
    }
    // cout << dist << dist2 << endl;
    cout << dist2[0][0]+dist[0][n-1] << endl;
    return 0;
}