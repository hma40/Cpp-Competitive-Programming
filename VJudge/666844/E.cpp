#include <bits/stdc++.h>
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
using namespace std;
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
#define int long long
signed main() {
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    vector<vector<pair<int,int>>> edges(n);
    for(int i = 0; i < m; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;
        y--;
        edges[x].push_back({y, z});
    }
    cout << edges << endl;
    vector<int> dist(n, 1e18);
    dist[a-1]=0;
    a--;
    b--;
    min_pq<pair<int,int>> pq;
    pq.push({0,a});
    while(pq.size()) {
        auto f = pq.top();
        pq.pop();
        cout << f.first << " " << f.second << endl;
        if(f.first>dist[f.second]) continue;
        for(auto x: edges[f.second]) {
            cout << f << x << " " << dist[x.first] << endl;
            if(dist[x.first]>f.first+x.second) {
                dist[x.first]=f.first+x.second;
                pq.push({f.first+x.second, x.first});
            }
        }
    }
    
    cout << dist[b] << endl;
}