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
vt<int> colors;
void assign(int start, int end) {
    if(start>end) return;
    // cout << "ASSIGN CALLED FOR " << start << " " << end << endl;
    int mid = start+(end-start)/2;
    FOR(i, start, mid+1) {
        colors[i]=start+mid+1-i;
    }
    FOR(i, mid+1, end+1) {
        colors[i]=end+mid+2-i;
    }
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        colors.assign(n,-1);
        k=min(k,n);
        F0R(i, n/k) {
            assign(i*k, i*k+k-1);
        }
        assign(n/k*k, n-1);
        F0R(i, n) cout << colors[i] << " ";
        cout << endl;
        cout << (n+k-1)/k << endl;
        F0R(i, (n+k-1)/k) {
            F0R(j, k) {
                if(i*k+j<n) {
                    cout << 1+i << " ";
                }
            }
        }
        cout << endl;
    }
    return 0;
}