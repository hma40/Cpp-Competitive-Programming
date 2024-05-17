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
ll inf = 2e18;
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
    int n,k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    F0R(i, k) {
        int a,b;
        cin >> a >> b;
        adj[--a].add(--b);
        adj[b].add(a);
    }
    vector<bool> vis(n);
    int comps = 0;
    int goodcomps = 0;
    F0R(i, n) {
        if(vis[i]) continue;
        if(adj[i].size()>2) {
            cout << -1 << endl;
            return 0;
        }
        comps++;
        if(adj[i].size()) goodcomps++;
        deque<pair<int, int>> q;
        q.add({i, -1});
        while(q.size()) {
            auto first = q.front();
            q.pop_front();
            if(vis[first.f]) {
                cout << -1 << endl;
                return 0;
            }
            vis[first.f]=true;
            int pushes = 0;
            trav(x, adj[first.f]) {
                if(x!=first.s) {
                    if(vis[x]) {
                        cout << -1 << endl;
                        return 0;
                    }
                    pushes++;
                    q.add({x, first.f});
                }
                if(pushes>1&&first.f!=i) {
                    cout << -1 << endl;
                    return 0;
                }
            }

        }
    }
    int ans = 1;
    FOR(i, 1, comps+1) {
        ans*=i;
        ans%=mod;
    }
    F0R(i, goodcomps) {
        ans*=2;
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}