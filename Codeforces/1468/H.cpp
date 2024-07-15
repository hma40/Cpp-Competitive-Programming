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
        int n,k,m;
        cin >> n >> k >> m;
        set<int> v;
        F0R(i, m) {
            int x;cin >> x;
            v.insert(x);
        }
        if((n-m)%(k-1)!=0) {
            cout << "NO" << endl;
            continue;
        } 
        int operations = (n-m)/(k-1);
        k/=2;
        vt<int> connected;
        int len = 0;
        FOR(i, 1, n+1) {
            if(v.count(i)) {
                if(len!=0) {
                    connected.add(len);
                    len=0;
                }
            } else {
                len++;
            }
        }
        if(len) connected.add(len);
        // cout << connected << endl;
        int sum = 0;
        int left = 0, right = n-1;
        int leftSum = 0;
        F0R(i, connected.size()) {
            leftSum+=connected[i];
            if(leftSum>=k) {
                left=i;
                break;
            }
        }
        leftSum=0;
        R0F(i, connected.size()) {
            leftSum+=connected[i];
            if(leftSum>=k) {
                right=i;
                break;
            }
        }
        if(left<right) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}