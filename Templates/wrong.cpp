#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define double long double
const ll mod = 1e9+7;
#define int long long
const int INF = 1e18;

signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    int tt;
    cin >> tt;
    while(tt--){
        // // int p, q; cin >> p >> q;
        // // double res = (double) p / q;
        // // if(ceil(res * 2) != floor(res * 2)){
        // //     cout << -1 << "\n";
        // //     continue ;
        // // }
        // // int use = res * 2;

        int n,m;
        cin >> n >> m;
        if(n==1) {
            cout << "NO" << endl;
            continue;
        }
        if(m==n*(n-1)/2) {
            cout << "NO" << endl;
            continue;
        }
        set<pair<int,int>> s;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                s.insert({i,j});
                if(s.size()>m) break;
            }
            if(s.size()>m) break;
        }
        vector<vector<int>> adj(n);
        for(int i = 0; i < m; i++) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            s.erase({a,b});
            adj[a].push_back(b);
        }
        cout << "YES" << endl;
        pair<int,int> special = {(*s.begin()).first, (*s.begin()).second};
        // cout << special.first << " " << special.second << endl;
        vector<int> indeg(n);
        for(int i = 0; i < n; i++) {
            for(auto x: adj[i]) {
                indeg[x]++;
            }
        }
        vector<int> a(n), b(n);
        int nxt = 1;
        deque<int> dq;
        for(int i = 0; i < n; i++) {
            if(indeg[i]==0) dq.push_back(i);
        }
        while(dq.size()) {
            auto tp = dq.front();
            dq.pop_front();
            if(tp==special.second) continue;
            if(tp==special.first) {
                a[tp] = nxt;
                b[tp] = nxt+1;
                a[special.second] = nxt+1;
                b[special.second] = nxt;
                nxt+=2;
                for(auto x: adj[tp]) {
                    indeg[x]--;
                    if(indeg[x]==0) dq.push_back(x);
                }
                for(auto x: adj[special.second]) {
                    indeg[x]--;
                    if(indeg[x]==0) dq.push_back(x);
                }
            } else {
                a[tp] = nxt;
                b[tp]=nxt;
                nxt++;
                for(auto x: adj[tp]) {
                    indeg[x]--;
                    if(indeg[x]==0) dq.push_back(x);
                }
            }
        }
        for(int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        for(int i = 0; i < n; i++) { cout << b[i] << " ";}
        cout << endl;
    }
}