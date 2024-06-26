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
int largestNei(vt<vt<int>> &v, int i, int j) {
    int ans = 0;
    // if(i>0&&j>0) {
    //     ans=max(ans, v[i-1][j-1]);
    // }
    // if(i>0&&j<v[0].size()-1) {
    //     ans=max(ans, v[i-1][j+1]);
    // }
    // if(i<v.size()-1&&j>0) {
    //     ans=max(ans, v[i+1][j-1]);
    // }
    // if(i<v.size()-1&&j<v[0].size()-1) {
    //     ans=max(ans, v[i+1][j+1]);
    // }
    if(i>0) {
        ans=max(ans, v[i-1][j]);
    }
    if(j>0) {
        ans=max(ans, v[i][j-1]);
    }
    if(i<v.size()-1) {
        ans=max(ans, v[i+1][j]);
    }
    if(j<v[0].size()-1) {
        ans=max(ans, v[i][j+1]);
    }
    // cout << i << " " << j << " " << ans << endl;
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        priority_queue<vt<int>> pq;
        vt<vt<int>> v(n, vt<int>(m));
        F0R(i, n) {
            F0R(j, m) {
                cin >> v[i][j];
                pq.push({v[i][j], i, j});
            }
        }
        while(pq.size()) {
            auto first = pq.top();
            pq.pop();
            int l = min(first[0], largestNei(v, first[1], first[2]));
            v[first[1]][first[2]]=l;
        }
        F0R(i, n) {
            F0R(j, m) {
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}