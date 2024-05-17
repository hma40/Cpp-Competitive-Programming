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
        int a,b,c;
        cin >> a >> b >> c;
        int depth = 0;
        int open = 1;
        bool fail = false;
        while(true) {
            int nextOpen = 0;
            if(open==0) {
                fail=true;
                break;
            }
            if(a>0) {
                if(a>=open) {
                    a-=open;
                    nextOpen+=2*open;
                    open=0;
                } else {
                    nextOpen+=2*a;
                    open-=a;
                    a=0;
                }
            } 
            if(b>0) {
                if(b>=open) {
                    b-=open;
                    nextOpen+=open;
                    open=0;
                } else {
                    nextOpen+=b;
                    open-=b;
                    b=0;
                }
            }
            if(c>0) {
                if(c>=open) {
                    c-=open;
                    open=0;
                } else {
                    open-=c;
                    c=0;
                }
            }
            swap(open, nextOpen);
            if(nextOpen) {
                fail=true;
                break;
            }

            if(!a&&!b&&!c) {
                if(open) fail=true;
                break;
            } 
            depth++;
        }
        if(fail) {
            cout << -1 << endl;
        } else {
            cout << depth << endl;
        }
    }
    return 0;
}