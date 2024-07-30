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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,x;
        cin >> n >> x;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        v.add(inf);
        vt<int> lasts(n, -1);
        int right = 0;
        int sum = v[0];
        F0R(left, n) {
            while(sum<=x) {
                // cout << left << " " << right << " " << sum << endl;
                right++;
                sum+=v[right];
            }
            lasts[left]=right;
            sum-=v[left];
        }
        // cout << lasts << endl;
        int ans = 0;
        vt<int> bad(n+1);
        vt<int> ad(n+1);
        // bad.back()=1;
        R0F(i, n) {
            int adHere = n-i;
            if(lasts[i]==i) {
                ad[i]=ad[i+1];
                bad[i]=adHere-ad[i];
            } else if(lasts[i]<n) {
                ad[i]=lasts[i]-i+ad[lasts[i]+1];
                bad[i]=adHere-ad[i];
            } else {
                // ans+=adHere;
                bad[i]=0;
                ad[i]=adHere;
            }
            ans+=ad[i];
        }
        cout << ans << endl;
        // cout << ans << lasts << ad << bad << endl;
    }
    return 0;
}
/*
1
5 2
9 1 2 1 3
*/