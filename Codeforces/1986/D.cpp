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
        string s;
        cin >> n >> s;
        if(n==2) {
            if(s[0]=='0') {
                cout << s[1] << endl;
            } else {
                cout << s << endl;
            }
        } else if(n==3) {
            string t = "";
            t+=s[1];
            int firsttwo = stoi(s[0]+t);
            int lasttwo = stoi(t+s[2]);
            int first = s[0]-'0';
            int last = s[2]-'0';
            cout << min({firsttwo*last, firsttwo+last, first*lasttwo, first+lasttwo}) << endl;
        } else {
            bool hasZ = false;
            F0R(i, n) if(s[i]=='0') hasZ=true;
            if(hasZ) {
                cout << 0 << endl;
                continue;
            }
            int sum = 0;
            F0R(i, n ) {
                if(s[i]!='1') sum+=s[i]-'0';
            }
            int ans = inf;
            FOR(j, 1, n) {
                int tempsum = sum;
                if(s[j]!='1') {
                    tempsum-=s[j]-'0';
                } 
                if(s[j-1]!='1') tempsum-=s[j-1]-'0';
                tempsum+=(s[j-1]-'0')*10+(s[j]-'0');
                ans=min(ans, tempsum);
            }
            cout << ans << endl;
        }
    }
    return 0;
}