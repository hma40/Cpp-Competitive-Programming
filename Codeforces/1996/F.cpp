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
int func(int a, int b, int times) {
    //first: a
    //last: a-b*(times-1)
    return (a+a-b*(times-1))*times/2;
}
int uses(vt<int> &a, vt<int> &b, int piv) {
    int n = a.size();
    int uses = 0;
    F0R(i, n) {
        if(a[i]<piv) continue;
        uses+=(a[i]-piv+b[i]-1)/b[i];
        // cout << i << " " << piv << " " << uses << endl;
    }
    return uses;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t-- ){
        int n,k;
        cin >> n >> k;
        vt<int> a(n), b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n)cin >> b[i];

        if(uses(a,b,0)<k) {
            int ans = 0;
            F0R(i, n) {
                ans+=func(a[i], b[i], (a[i]+b[i]-1)/b[i]);
            }
            cout << ans << endl;
        } else {    
            int lo = 0, hi = 1e6;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(uses(a,b,mid)<k) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            if(uses(a,b,hi)>=k) {
                lo=hi;
            } 
            //use lo
            priority_queue<int> pq;
            int ans = 0;
            int uses = 0;
            F0R(i, n) {
                int us = (a[i]-lo-1)/b[i];
                if(us<0) us=0;
                // cout << i << " " << a[i] << " " << b[i] << " " << us << " " << func(a[i],b[i],us) << endl;
                ans+=func(a[i],b[i],us);
                uses+=us;
                pq.push(a[i]-b[i]*us);
            }
            while(uses<k) {
                ans+=pq.top();
                pq.pop();
                uses++;
            }
            cout << ans << endl;
        }
    }
    return 0;
}