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
    while(t-- ){
        int n;
        cin >> n;
        vt<int> a(n);
        int ans = 0;
        F0R(i, n) cin >> a[i];
        F0R(i, n) ans+=a[i];
        vt<int> count(n+1);
        F0R(i, n) count[a[i]]++;
        int mad = 0;
        R0F(i, n+1) if(count[i]>1) {mad=i;break;}
        vt<int> madArr(n);
        madArr.back()=mad;
        ROF(i, 1, n) {
            count[a[i]]--;
            while(mad&&count[mad]<=1) {
                mad--;
            }
            madArr[i-1]=mad;
        }
        F0R(i, n) ans+=madArr[i];
        int turns = 0;
        count.assign(n+1,0);
        F0R(i, n) {
            if(madArr[i]!=0) count[madArr[i]]++;
        } 
        // cout << madArr << endl;

        vt<int> mmad(n);
        mad = 0;
        R0F(i, n+1) if(count[i]>1) {mad=i;break;}
        // madArr.assign(n, 0);
        mmad.back()=mad;
        ROF(i, 1, n) {
            count[madArr[i]]--;
            while(mad&&count[mad]<=1) {
                mad--;
            }
            mmad[i-1]=mad;
        }
        // F0R(i, n) ans+=mmad[i];
        // int turns = 0;
        // cout << mmad << ans << endl;
        count.assign(n+1,0);
        F0R(i, n) {
            if(mmad[i]!=0) count[mmad[i]]++;
        } 
        // int extras = 0;
        // int turns = 0;
        R0F(i, n+1) {
            if(count[i]==0) continue;
            ans+=turns*count[i]*i;
            ans+=i*(count[i]+1)*count[i]/2;
            turns+=count[i];
        }
        cout << ans << endl;
        // cout << madArr << endl;

    }
    return 0;
}
/*
2 2 3 4 5 5
0 2 2 2 2 5
0 0 2 2 2 2
*/
/*
2 2 2 3 4 4
0 2 2 2 2 4
*/
/*
3 3 4 4
0 3 3 4
0 0 3 3
*/
/*
0 0 1 2
0 0 0 0     
*/