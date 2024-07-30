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
// #define int long long
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
    while(t--) {
        string s;
        cin >> s;
        vt<vt<short>> poss(s.size(), vt<short>(s.size()));
        F0R(i, s.size()) {
            FOR(j, i, s.size()) {
                if(s[i]==s[j]||s[i]=='?'||s[j]=='?') poss[i][j]=1;
            }
        }
        // cout << poss << endl;
        vt<vt<int>> weirdPref(s.size()+1, vt<int>(s.size()+1));
        F0R(i, s.size()) {
            FOR(j, i, s.size()) {
                if(poss[i][j]) {
                    weirdPref[j-i][i+1]++;
                }
            }
        }

        F0R(i, s.size()) {
            F0R(j, s.size()) {
                weirdPref[i][j+1]+=weirdPref[i][j];
            }
        }
        int ans = 0;
        F0R(i, s.size()) {
            for(int j = i+1; j < s.size(); j+=2) {
                int mid = (i+j)/2;
                if(weirdPref[mid-i+1][mid+1]-weirdPref[mid-i+1][i]==mid-i+1) {
                    // cout << i << " " << j << endl;
                    ans=max(ans, j-i+1);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}