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
        int one,two,three,four;
        cin >> one >> two >> three >> four;
        int xr = 0;
        if(one%2) xr^=1;
        if(two%2) xr^=2;
        if(three%2) xr^=3;
        if(four%2) xr^=4;
        int ans = 0;
        if(xr!=0) {
            if(xr&4) {
                four--;
                xr^=4;
            }
            if(xr==3) {
                if(three) {
                    three--;
                    xr=0;
                } else {
                    two--;
                    one--;
                    xr=0;
                }
            } else if(xr==2) {
                if(two) {
                    two--;
                    xr=0;
                } else {
                    one--;
                    three--;
                    xr=0;
                }
            } else if(xr==1) {
                if(one) {
                    one--;
                    xr=0;
                } else {
                    two--;
                    three--;
                    xr=0;
                }
            }
            ans=1;
        } else {
            ans=1;
        }
        while(four) {
            ans++;
            four-=2;
        }
        while(three>=2) {
            ans++;
            three-=2;
        }
        while(two>=2) {
            ans++;
            two-=2;
        }
        while(one>=2) {
            ans++;
            one-=2;
        }
        while(one&&two&&three) {
            ans++;
            one--;
            two--;
            three--;
        }
        ans--;
        cout << ans << endl;
    }
    return 0;   
}