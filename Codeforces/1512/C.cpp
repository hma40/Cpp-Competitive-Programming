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
        int a,b; string s;
        cin >> a >> b >> s;
        if(a%2&&b%2) {
            cout << -1 << endl;
            continue;
        }
        int n = a+b;
        F0R(i, n) {
            if(s[i]=='0') a--;
            if(s[i]=='1') b--;
        }
        // cout << "GOT HERE0" << endl;
        bool fail = false;
        F0R(i, n) {
            if(s[i]=='0'&&s[n-1-i]=='1'||s[i]=='1'&&s[n-1-i]=='0') {
                fail=true;
            }
            if(s[i]=='?'&&s[n-i-1]!='?') {
                if(s[n-i-1]=='0') {
                    a--;
                    s[i]='0';
                } else {
                    b--;
                    s[i]='1';
                }
            }
        }       
        if(fail) {
            cout << -1 << endl;
            continue;
        }
        // cout << "GOT HERE" << endl;
        // cout << a << " " << b << " " << s << endl;
        if(a<0||b<0) {
            cout << -1 << endl;
        } else {
            if(a%2) {
                s[n/2]='0';
                a--;
            } else if(b%2) {
                s[n/2]='1';
                b--;
            }
            F0R(i, n) {
                if(s[i]=='?') {
                    if(a>0) {
                        a-=2;
                        s[i]=s[n-1-i]='0';
                    } else {
                        b-=2;
                        s[i]=s[n-1-i]='1';
                    }
                }
            }
            cout << s << endl;
        }
    }
    return 0;
}
/*
1
7 12
??00?101??1?0?100??
*/