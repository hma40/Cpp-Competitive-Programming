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
        int n,k;
        string s;
        cin >> n >> k >> s;
        int count = 0;
        R0F(i, n) {
            if(s[i]==s[n-1]) count++;
            else break;
        }
        // cout << s << " " << count << endl;
        if(count>k) {
            cout << -1 << endl;
            continue;
        } else if(count==k) {
            //whole string must be ok
            count = 0;
            bool bad = false;
            char prev = s[0];
            int found = -1;
            F0R(i, n) {
                if(s[i]==prev) count++;
                else {
                    if(count==2*k&&s[i-1]!=s[n-1]) {
                        if(found!=-1) bad=true;
                        found=i;
                    } else if(count!=k) {
                        bad=true;
                    }
                    count=1;
                    prev=s[i];
                }
            }
            if(bad) cout << -1 << endl;
            else if(found==-1) cout << n << endl;
            else cout << found-k << endl;
        } else {
            int missing = k-count;
            count = 0;
            bool bad = false;
            int found = -1;
            char prev = s[0];
            F0R(i, n) {
                // cout << i << " " << found << " " << prev << " " << count << " " << missing << endl;
                if(s[i]==prev) count++;
                else {
                    if(k+missing==count&&s[i-1]==s[n-1]) {
                        if(found==-1) found=i;
                        else bad=true;
                    } else if(k==count) {

                    } else if(count==missing&&s[i-1]==s[n-1]) {
                        if(found!=-1) bad=true;
                        found=i+k;
                    } else {
                        bad=true;
                    }
                    count=1;
                    prev=s[i];
                }   
            }
            if(bad) cout << -1 << endl;
            else if(found==-1) cout << -1 << endl;
            else {
                F0R(i, k) {
                    found--;
                }
                cout << found << endl;
            }
        }
    }   
    return 0;
}
/*
1
6 1
110110
*/