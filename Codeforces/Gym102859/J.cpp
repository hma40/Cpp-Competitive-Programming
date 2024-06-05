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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vt<int> a(n),b(n);
    vt<int> inv(n+1);
    F0R(i, n) {
        cin >> a[i];
        inv[a[i]]=i;
    }
    F0R(i, n) {
        cin >> b[i];
        b[i]=inv[b[i]];
    }
    // cout << b << endl;
    vt<int> changeDir(n);
    F0R(i, n) {
        int changeTime = b[i]-i;
        if(changeTime<0) changeTime+=n;
        if(b[i]!=n-1) {
            changeDir[changeTime]+=2;
        }
    }
    int cur = 0, ans = 0;
    int delta = 0;
    // cout << changeDir << endl;
    F0R(i, n) {
        if(i!=n-1) {
            if(b[i]>=i) {
                delta++;
            } else {
                delta--;
            }
        }
        ans+=abs(b[i]-i);
    }
    cur=ans;
    // cout << cur << endl;
    F0R(i, n-1) {
        //calculate new delta
        delta-=changeDir[i];
        int last = b[n-i-1];
        //calculate cur
        cur=cur-delta-abs(last-n+1)+last;
        ans=min(ans, cur);
        // cout << "LINE 96: " << i << " " << delta << " " << cur << " " << last << endl;
        //calculate delta
        if(b[n-i-2]!=n-1) {
            delta+=2;
        }
        // cout << "LINE 101: " << i << " " << delta << endl;
    }
    cout << ans << endl;
    return 0;
}