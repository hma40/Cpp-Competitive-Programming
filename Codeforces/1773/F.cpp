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
// #define endl "\n"
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
    int n,a,b;
    cin >> n >> a >> b;
    if(n==1) {
        if(a==b) cout << 1 << endl;
        else cout << 0 << endl;
        cout << a << ":" << b << endl;
        return 0;
    }
    if(a==0&&b==0) {
        cout << n << endl;
        F0R(i, n) cout << "0:0" << endl;
        return 0;
    }
    string ans = "";
    if(a==0) {
        while(n>1&&b>0) {
            n--;
            b--;
            ans+="0:1\n";
        }
        int draws = 0;
        if(n==1) ans+="0:"+to_string(b)+"\n";
        else {
            while(n) {
                draws++;
                ans+="0:0\n";
                n--;
            }
        }
        cout << draws << endl << ans;
        return 0;
    }
    if(b==0) {
        while(n>1&&a>0) {
            n--;
            a--;
            ans+="1:0\n";
        }
        int draws = 0;
        if(n==1) ans+=to_string(a)+":0\n";
        else {
            while(n) {
                n--;
                draws++;
                ans+="0:0\n";
            }
        }
        cout << draws << endl << ans;
        return 0;
    }
    int draws = 0;
    // cout << n << " " << a << " " << b << endl;
    while(n>2&&a>1) {
        a--;
        n--;
        ans+="1:0\n"; 
    }
    // cout << n << " " << a << " " << b << endl;
    while(n>2&&b>1) {
        b--;
        n--;
        ans+="0:1\n";
    }
    // cout << n << " " << a << " " << b << endl;
    if(n==2) {
        ans+=to_string(a)+":0\n";
        ans+="0:"+to_string(b)+"\n";
    } else {
        n-=2;
        ans+="1:0\n0:1\n";
        while(n) {
            draws++;
            ans+="0:0\n";
            n--;
        }
    }
    cout << draws << endl << ans;
    return 0;
}