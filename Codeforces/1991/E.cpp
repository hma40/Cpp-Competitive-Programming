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
// #define endl "\n"
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--) {
        int n,m;
        cin >> n >> m;
        vt<vt<int>> adj(n);
        F0R(i, m) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].add(b);
            adj[b].add(a);
        }
        // vt<bool> vis(n);
        deque<int> dq;
        dq.add(0);
        bool bad = false;
        // vis[0]=true;
        vt<int> col(n);
        col[0]=1;
        while(dq.size()) {
            int f = dq.front();
            dq.pop_front();
            trav(x, adj[f]) {
                if(col[x]==col[f]) {
                    bad=true;
                } else if(col[x]==0) {
                    col[x]=3-col[f];
                    dq.push_back(x);
                }
            }
        }
        set<int> o,t;
        F0R(i, n) {
            if(col[i]==1) o.insert(i);
            else t.insert(i);
        }
        // cout << col << bad << endl;
        if(bad) {
            cout << "Alice" << endl;
            vt<int> actualCol(n);
            F0R(i, n) {
                cout << "1 2" << endl;
                int x,y;
                cin >> x;
                if(x==-1) {
                    return 0;
                }
                cin >> y;
            }
        } else {
            cout << "Bob" << endl;
            F0R(i, n) {
                int x,y;
                cin >> x;
                if(x==-1) assert(false);
                cin >> y;
                int colorChosen = 0;
                int choose = 0;
                if(min(x,y)==1&&o.size()) {
                    colorChosen=1;
                    choose=*(o.begin());
                    o.erase(choose);
                } else if(min(x,y)==1) {
                    colorChosen=3;
                    choose=*(t.begin());
                    t.erase(choose);
                    if(max(x,y)==2) {
                        colorChosen=2;
                    }
                } else if(t.size()) {
                    colorChosen=2;
                    choose=*(t.begin());
                    t.erase(choose);
                } else {
                    colorChosen=3;
                    choose=*(o.begin());
                    o.erase(choose);
                }
                cout << choose+1 << " " << colorChosen << endl;
            }
        }
    }
    return 0;
}
/*
1
5 4
2 5
3 4
5 3
1 4
*/
/*
4 2
5 2
1 3
*/