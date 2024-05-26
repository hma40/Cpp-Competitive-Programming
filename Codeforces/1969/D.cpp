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
ll mod = 1000000007;
ll inf = 1e15;
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

        vector<pair<int, int>> v(n);
        F0R(i, n) {
            cin >> v[i].s;
        }
        F0R(i, n) cin >> v[i].f;
        sort(begin(v),end(v));
        //cout << v << endl;
        vector<int> profit(n);
        if(v[0].f>v[0].s) {
            profit[0]=v[0].f-v[0].s;
        }
        FOR(i, 1, n) {
            if(v[i].f>v[i].s) {
                profit[i]=profit[i-1]+v[i].f-v[i].s;
            } else {
                profit[i]=profit[i-1];
            }
        }
        // cout << profit << endl;
        if(k==0) {
            cout << profit.back() << endl;
            continue;
        }
        int ans = 0;
        int sum = 0;
        multiset<int> aPay;
        F0R(i, k) {
            sum+=v[n-1-i].s;
            aPay.insert(v[n-1-i].s);
        }
       // cout << sum << " " << aPay << endl;
        R0F(i, n-k) {
            ans=max(ans, profit[i]-sum);
            //cout << i << " " << profit[i] << " " << sum << endl;
            auto last = *aPay.rbegin();
            if(last>v[i].s) {
                sum-=last;
                aPay.erase(aPay.lower_bound(last));
                sum+=v[i].s;
                aPay.insert(v[i].s);
            }   

        }
        cout << ans << endl;
    }
    return 0;
}