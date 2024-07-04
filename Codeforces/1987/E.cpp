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
vt<int> a;
vt<int> par;
vt<int> cSum;
int n;
vt<vt<int>> adj;
vt<vt<int>> v;
vt<int> start;
void dfs(int nd=0) {
    trav(x, adj[nd]) {
        if(x==par[nd]) continue;
        par[x]=nd;
        cSum[nd]+=a[x];
        dfs(x);
    }
}
int solve(int nd) {
    // cout << "HELLO " << nd << endl;
    if(nd!=0&&adj[nd].size()==1) {
        v[nd][1]=inf;
        // cout << "LINE 100 RETURNING " << nd << " " << 0 << endl;
        return 0;
    }
    int ans = 0;
    trav(x, adj[nd]) {
        if(x==par[nd]) continue;;
        ans+=solve(x);
    }
    // cout << "MADE IT TO LINE 108 " << nd << " " << ans << endl;
    for(int i = 1; i <= n; i++) {
        trav(x, adj[nd]) {
            if(x==par[nd]) continue;
            v[nd][i+1]+=v[x][i];
            v[nd][i+1]=min(v[nd][i+1], inf);
        }
        if(v[nd][i+1]>=inf/2) {
            break;
        }
    }

    if(a[nd]<=cSum[nd]) {
        v[nd][1]=-a[nd]+cSum[nd];
    } else {
        start[nd]=2;
        int sub = a[nd]-cSum[nd];
        for(int i = 2; i <= n; i++) {
            int delta = min(sub, v[nd][i]);
            v[nd][i]-=delta;
            sub-=delta;
            ans+=(i-1)*delta;
            if(v[nd][i]==0) start[nd]=i+1;
            if(sub==0) break;
        }
    }
    // cout << "LINE 135 RETURNING " << nd << " " << ans << " " << v[nd] << endl;
    return ans;
}
void reset() {
    cSum.clear();
    cSum.resize(n);
    a.clear();
    a.resize(n);
    v.clear();
    v.resize(n, vt<int>(n+2));
    adj.clear();
    adj.resize(n);  
    par.clear();
    par.resize(n);
    start.clear();
    start.resize(n, 1);
    par[0]=-1;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        reset();
        F0R(i, n) cin >> a[i];
        FOR(i, 1, n) {
            int x;
            cin >> x;
            adj[i].add(x-1);
            adj[x-1].add(i);
        }
        dfs();
        cout << solve(0) << endl;
        // cout << "LINE 169 " << endl;
    }
    return 0;
}
/*
7
7
1 0 5 0 1 2 2
1 2 1 1 2 4
8
1 1 1 4 0 3 0 3
1 2 2 4 2 6 1
8
2 4 2 3 1 3 3 3
1 2 1 4 5 5 5
9
1 3 4 3 4 3 3 3 5
1 2 1 1 2 4 3 6
2
4 5
1
5
0 4 1 3 4
1 1 2 1
2
5 4
1
*/
/*
0
7
4
1
0
1
1
*/