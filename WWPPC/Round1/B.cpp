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

bool poss(int mid, int x1, int x2, int y1, int y2) {
    int xd = abs(x1-x2), yd = abs(y1-y2);
    int tx1=x1,ty1=y1,tx2=x2,ty2=y2;
    if(xd<mid) {
        tx2=tx1;
    } else {
        if(tx2>tx1) tx2-=mid;
        else tx2+=mid;
    }
    if(yd<mid) {
        ty2=ty1;
    } else {
        if(ty2>ty1) ty2-=mid;
        else ty2+=mid;
    }
    if(abs(tx1-tx2)+abs(ty1-ty2)<=mid) return true;
    return false;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        ll x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int lo = 0, hi = 1e10;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(poss(mid,x1,x2,y1,y2)) {
                hi=mid;
            } else {
                lo=mid;
            }
        }
        if(poss(lo,x1,x2,y1,y2)) cout << lo << endl;
        else cout << hi << endl;
        // cout << poss(2,x1,x2,y1,y2) << endl;
        
    }
    return 0;
}