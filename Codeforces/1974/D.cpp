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
        int n;
        string s;
        cin >> n >> s;
        int x=0, y=0;
        F0R(i, n) {
            if(s[i]=='N') x++;
            if(s[i]=='S') x--;
            if(s[i]=='E') y++;
            if(s[i]=='W') y--;
        }
        if(x%2||y%2) {
            cout << "NO" << endl;
            continue;
        }
        if(x==0&&y==0) {
            if(n==2) {
                cout << "NO" << endl;
                continue;
            }
            cout << "R";
            bool done = false;
            FOR(i, 1, n) {
                if(s[0]=='N'&&s[i]=='S'||s[0]=='S'&&s[i]=='N'||s[0]=='W'&&s[i]=='E'||s[0]=='E'&&s[i]=='W') {
                    if(done) {
                        cout << "H";
                    } else {
                        cout << "R";
                        done=true;
                    }
                } else {
                    cout << "H";
                }
            }
            cout << endl;
            continue;
        }
        x/=2;
        y/=2;
        int tmpx=0, tmpy=0;
        F0R(i, n) {
            if(tmpx<x&&s[i]=='N') {
                cout << "H";
                tmpx++;
            } else if(tmpx>x&&s[i]=='S') {
                cout << "H";
                tmpx--;
            } else if(tmpy<y&&s[i]=='E') {
                cout << "H";
                tmpy++;
            } else if(tmpy>y&&s[i]=='W') {
                cout << "H";
                tmpy--;
            } else {
                cout << "R";
            }
        }
        cout << endl;
    }
    return 0;
}