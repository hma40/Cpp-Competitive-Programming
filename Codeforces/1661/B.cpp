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
#define vt vector
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
    vt<int> dist(32768, inf);
    dist[0]=0;
    deque<int> q;
    q.add(0);
    while(q.size()) {
        int first = q.front();
        q.pop_front();
        if(first%2==0) {
            int x = first/2;
            if(dist[x]==inf) {
                dist[x]=dist[first]+1;
                q.push_back(x);
            }
            x = (first+32768)/2;
            if(dist[x]==inf) {
                dist[x]=dist[first]+1;
                q.push_back(x);
            }
        }
        int x = (first+32767)%32768;
        if(dist[x]==inf) {
            dist[x]=dist[first]+1;
            q.push_back(x);
        }
    }
    int n;
    cin >> n;
    F0R(i, n) {
        int x;
        cin >> x;
        if(i==0) {
            cout << dist[x];
        } else {
            cout << " " << dist[x];
        }
    }
    cout << endl;
    return 0;
}