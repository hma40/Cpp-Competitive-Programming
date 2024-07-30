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
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        int mx = 0;
        bool fail = false;
        F0R(i, n) {
            if(v[i]==1&&mx>1) {
                fail=true;
            }
            mx=max(mx,v[i]);
        }
        if(fail) {
            cout << -1 << endl;
            continue;
        }
        vt<int> comp(n);
        vt<bool> equal(n);
        FOR(i, 1, n) {
            int temp = v[i-1];
            int tmp = v[i];
            if(temp<tmp) {
                if(temp==1) {
                    comp[i]=-1;
                    continue;
                }
                while(temp<tmp) {
                temp*=temp;
                comp[i]--;
                }
            } else {
                while(tmp<temp) {
                tmp*=tmp;
                comp[i]++;
                }
            }
            if(temp==tmp) equal[i]=true;
        }
        // cout << comp << equal << endl;
        int ans = 0;
        int prev = 0;
        FOR(i, 1, n) {
            if(equal[i]) {
                int here = max(0LL, prev+comp[i]);
                ans+=here;
                prev=here;
            } else {
                if(comp[i]>0) {
                    int here = prev+comp[i];
                    ans+=here;
                    prev=here;
                } else {
                    int here = max(0LL, prev+comp[i]+1);
                    ans+=here;
                    prev=here;
                }
                // int here = max(0LL, prev+comp[i]+1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}