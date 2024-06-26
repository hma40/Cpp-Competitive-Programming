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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        string a,b,newa,newb;
        cin >> n >> a >> b;
        newa=a;
        newb=b;
        FOR(i, 1, n-1) {
            if(newa[i-1]=='0'&&newa[i+1]=='0') newb[i]='1';
        }
        FOR(i, 1, n-1) {
            if(newb[i-1]=='1'&&newb[i+1]=='1') newa[i]='1';
        }
        vt<int> pref(n+1);
        F0R(i, n) {
            pref[i+1]=pref[i];
            if(newa[i]=='1') pref[i+1]++;
        }
        int q;
        cin >> q;
        while(q--) {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            if(l==r) {
                if(a[l]=='1') cout << 1 << endl;
                else cout << 0 << endl;
            } else if(r==l+1) {
                if(a[l]=='1'&&a[r]=='1') cout << 2 << endl;
                else if(a[l]=='0'&&a[r]=='0') cout << 0 << endl;
                else cout << 1 << endl;
            } else if(r==l+2) {
                int count = 0;
                if(a[l]=='1') count++;
                if(a[r]=='1') count++;
                if(a[l+1]=='1'||b[l]=='1'&&b[r]=='1') count++;
                cout << count << endl;
            } else {
                //from l+2 to r-2
                int count = pref[r-1]-pref[l+2];
                if(a[l]=='1') count++;
                if(a[r]=='1') count++;
                if(a[l+1]=='1'||b[l]=='1'&&newb[l+2]=='1') count++;
                if(a[r-1]=='1'||b[r]=='1'&&newb[r-2]=='1') count++;
                cout << count << endl;
            }
        }
    }
    return 0;
}