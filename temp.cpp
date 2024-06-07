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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m,k;
        cin >> n >> m >> k;
        vt<int> col(n);
        F0R(i, n) cin >> col[i];
        vt<int> price(n);
        F0R(i, n) cin >> price[i];
        vt<int> outDeg(n);
        vt<vt<int>> adj(n),invadj(n);
        F0R(i, m) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            if(x==y) continue;
            adj[x].add(y);
            invadj[y].add(x);
            outDeg[x]++;
        }
        vt<bool> vis(n);
        priority_queue<pair<int, int>> pq;
        F0R(i, n) pq.push({price[i], i});
        while(pq.size()) {
            auto f = pq.top();
            pq.pop();
            if(vis[f.s]) continue;
            vis[f.s]=true;
            trav(x, invadj[f.s]) {
                if(price[x]<price[f.s]) {
                    price[x]=price[f.s];
                    pq.push({price[f.s], x});
                }
            }
        } 
        F0R(i, n) col[i]=price[col[i]-1];
        sort(begin(col),end(col));
        int ans = 0;
        F0R(i, k) {
            ans+=col[n-i-1];
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
5 6 5
1 5 2 1 3
2 1 5 9 4
3 1
1 4
5 2
4 4
3 3
1 5
*/