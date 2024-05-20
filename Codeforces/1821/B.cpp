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
        vt<int> orig(n), og(n);
        F0R(i, n) cin >> orig[i];
        F0R(i, n) cin >> og[i];
        int first = -1, last = -1;
        F0R(i, n) {
            if(orig[i]!=og[i]) {
                if(first==-1) first=i;
                last=i;
            }
        }
        if(first==-1) {
            int begin = 0;
            int a = 0;
            pair<int, int> ans;
            FOR(i, 1, n) {
                if(orig[i]<orig[i-1]) {
                    if(i-begin>a) {
                        ans={begin, i-1};
                        a=i-begin;
                        begin=i;
                    }
                } 
            }
            if(n-begin>a) {
                ans={begin, n-1};
            }
            cout << ans.f+1 << " " << ans.s+1 << endl;
        } else {
            while(first>0&&og[first-1]<=og[first]) first--;
            while(last<n-1&&og[last+1]>=og[last]) last++;
            cout << first+1 << " " << last+1 << endl;
        }
    }
    return 0;
}