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
bool oob(int x, int y, int n) {
    return x<0||y<0||x>1||y>=n;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<string> v(2);
        F0R(i, 2) cin >> v[i];
        vt<vt<bool>> canReach(2,vt<bool>(n));
        deque<pair<int,int>> dq;
        canReach[0][0]=true;
        dq.add({0,0});
        vt<vt<int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};
        while(dq.size()) {
            auto f = dq.front();
            dq.pop_front();
            F0R(i, 4) {
                pair<int,int> no = {f.f+dir[i][0], f.s+dir[i][1]};
                if(!oob(no.f,no.s,n)) {
                    if(v[no.f][no.s]=='>') no.s++;
                    else no.s--;
                    if(canReach[no.f][no.s]) continue;
                    canReach[no.f][no.s]=true;
                    dq.push_back(no);
                }
            }
        }
        if(canReach[1][n-1]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}