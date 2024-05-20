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
ll inf = 1e18+5;
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
int poww(int base, int exp) {
    int ans = 1;
    while(exp) {
        ans*=base;
        exp--;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int p,q;
        cin >> p >> q;
        if(p%q!=0) {
            cout << p << endl;
            continue;
        }
        map<int, int> mq;
        for(int i = 2; i*i<=q; i++) {
            while(q%i==0) {
                mq[i]++;
                q/=i;
            }
        }
        if(q>1) mq[q]++;
        map<int, int> mp;
        int tempp = p;
        trav(x, mq) {
            while(tempp%x.f==0) {
                mp[x.f]++;
                tempp/=x.f;
            }
        }
        int ans = inf;
        trav(x, mp) {
            int diff = x.s-mq[x.f];
            ans=min(ans, poww(x.f, diff+1));
        }
        cout << p/ans << endl;
    }
    return 0;
}