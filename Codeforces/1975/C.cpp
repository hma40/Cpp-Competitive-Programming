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
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> perm(n);
        int biggest = 0;
        F0R(i, n) {
            cin >> perm[i];
            if(perm[i]==1) biggest=i;
        }
        vt<int> recons(n);
        set<int> exist2;
        set<int> exists;
        F0R(i, n) {
            if(!exists.count(i+1)) exist2.insert(i+1);
        }
        exist2.insert(inf);
        // cout << exists << " " << exist2 << endl;
        exist2.insert(inf);
        // cout << biggest << endl;
        if(biggest%2==0) {
            // cout << "LINE 79" << endl;
            for(int i = 1; i < n-1; i+=2) {
                recons[i]=n+2-perm[i];
                exist2.erase(recons[i]);
            }
            for(int i = 0; i < n; i+=2) {
                int mx =n+1-perm[i];
                auto x = exist2.upper_bound(mx);
                assert(x!=exist2.begin());
                --x;
                recons[i]=*x;
                exist2.erase(recons[i]);
            }
            recons.back()=*exist2.begin();
            // cout << recons << endl;
        } else {
            // cout << "LINE 92 "<< endl;
            for(int i = n-2; i > 0; i-=2) {
                recons[i]=n+2-perm[i];
                exist2.erase(recons[i]);
            }
            for(int i = 1; i < n; i+=2) {
                int mx =n+1-perm[i];
                auto x = exist2.upper_bound(mx);
                assert(x!=exist2.begin());
                --x;
                recons[i]=*x;
                exist2.erase(recons[i]);
            }
            recons[0]=*recons.begin();
            // cout << recons << endl;
        }
        cout << recons[0];
        FOR(i, 1, n) cout << " " << recons[i];
        cout << endl;
    }
    return 0;
}