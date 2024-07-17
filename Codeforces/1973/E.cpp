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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        //special case
        // F0R(i, n) v[i]--;
        bool done = false;
        F0R(i, n) {
            if(v[i]!=i+1) {
                done=true;
            }
        }
        if(!done) {
            cout << 2*n+(2*n*(2*n-1))/2 << endl;
            continue;
        }
        int ans = 0;
        int sum = -1;
        F0R(i, n) {
            if(v[i]!=i+1) {
                int num = v[v[i]-1];
                if(num!=i+1) {
                    done=false;
                }
                int sumHere = i+1+v[i];
                if(sum!=-1&&sum!=sumHere) {
                    done=false;
                }
                sum=sumHere;
            } 
        }
        if(done) ans=1;
        int first=-1,last;
        F0R(i, n) {
            if(v[i]!=i+1) {
                if(first==-1) first=i;
                last=i;
            }
        }
        // cout << first << " " << last << endl;
        first++;
        last++;
        first+=n;
        last++;
        // cout << first << " " << last << endl;
        for(int i = 1; i <= min(2*n,first); i++) {
            int minJ = max(i+1, last);
            int maxJ = 2*n;
            ans+=(maxJ-minJ+1);
        }
        cout << ans << endl;
    }
    return 0;
}