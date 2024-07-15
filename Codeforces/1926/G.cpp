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
vt<int> par;
vt<vt<int>> child;
vt<int> noMusic, music;
string type;
void reset() {
    par.assign(n, -1);
    child.assign(n, vt<int>());
    noMusic.assign(n, -1);
    music.assign(n, -1);
    // type.assign(n, 0);
    type.clear();
}
void solve(int node=0) {
    trav(x, child[node]) {
        solve(x);
    }
    if(type[node]=='S') {
        music[node]=inf;
        noMusic[node]=0;
        trav(x, child[node]) {
            noMusic[node]+=min(noMusic[x], music[x]+1);
        }
    } else if(type[node]=='P') {
        noMusic[node]=inf;
        music[node]=0;
        trav(x, child[node]) {
            music[node]+=min(music[x], noMusic[x]+1);   
        }
    } else {
        noMusic[node]=music[node]=0;
        trav(x, child[node]) {
            noMusic[node]+=min(noMusic[x], music[x]+1);
            music[node]+=min(noMusic[x]+1, music[x]);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        reset();
        FOR(i, 1, n) {
            cin >> par[i];
            par[i]--;
            child[par[i]].add(i);
        }
        cin >> type;
        solve();
        // cout << music << noMusic << endl;
        if(noMusic[0]==-1) {
            cout << music[0] << endl;
        } else if(music[0]==-1) {
            cout << noMusic[0] << endl;
        } else {
            cout << min(music[0], noMusic[0]) << endl;
        }
    }    
    return 0;
}