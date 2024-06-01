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
        int n,k;
        cin >> n >> k;
        vt<int> ans;
        if(k==3) {
            if(n%4==0) {
                cout << n/4 << " " << n/4 << " " << n/2 << endl;
            } else if(n%2==0) {
                cout << 2 << " " << (n-2)/2 << " " << (n-2)/2 << endl;
            } else {
                cout << 1 << " " << (n-1)/2 << " " << (n-1)/2 << endl;
            }
            continue;
        }
        if(n%2==k%2) {
            while(k>2) {
                ans.add(1);
                k--;
                n--;
            }
            ans.add(n/2);
            ans.add(n/2);
        } else {
            while(k>4) {
                ans.add(1);
                k--;
                n--;
            }
            if(n%4==0) {
                ans.add(n/4);
                ans.add(n/4);
                ans.add(n/4);
                ans.add(n/4);
            } else if(n%4==1) {
                ans.add(1);
                n--;
                ans.add(n/2);
                ans.add(n/4);
                ans.add(n/4);
            } else if(n%4==2) {
                ans.add(1);
                ans.add(1);
                n-=2;
                ans.add(n/2);
                ans.add(n/2); 
            } else {
                ans.add(1);
                ans.add(2);
                n-=3;
                ans.add(n/2);
                ans.add(n/2);
            }
        }

        cout << ans[0];
        FOR(i, 1, ans.size()) {
            cout << " " << ans[i];
        }
        cout << endl;
    }
    return 0;
}