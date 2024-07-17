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
// ll mod = 1000000007;
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
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(string s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
void initialize() {
    sd = rnd()%mod;
    pw.add(1);
    F0R(i, 200050) {
        pw.add(pw.back()*sd%mod);
    }
}
Hash fwd(""),rev("");
bool isPal(int start, int end, int n) {
    int mid = (start+end)/2;
    int hsh = fwd.getHash(start,mid);
    int backEnd = n-end-1;
    int backStart = n-start-1;
    int backmid = (backEnd+backStart)/2;
    return (hsh==rev.getHash(backEnd,backmid));
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    initialize();
    int t;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        string s;
        cin >> s;
        string sback = s;
        reverse(begin(sback),end(sback));
        fwd=Hash(s), rev=Hash(sback);
        vt<int> alt(n),same(n);
        same[n-1]=n-1;
        R0F(i, n-1) {
            if(s[i]==s[i+1]) {
                same[i]=same[i+1];
            } else {
                same[i]=i;
            }
        }
        alt[n-1]=n-1;
        alt[n-2]=n-1;
        R0F(i, n-2) {
            if(s[i]==s[i+2]) {
                alt[i]=alt[i+1];
            } else {
                alt[i]=i+1;
            }
        }
        while(q--) {
            int l,r;
            cin >> l >> r;
            r--;l--;
            int ans = 0;//(2+(r-l+1))*(r-l)/2;
            //add all evens if its not all same
            if(same[l]<r) {
                int beg = 2, end = (r-l+1)/2*2;
                ans+=(beg+end)*((end-beg)/2+1)/2;
                if(l%2!=r%2) {
                    if(isPal(l,r,n)) {
                        ans-=r-l+1;
                    }
                }
            }
            if(alt[l]<r) {
                int beg = 3, end = (r-l+1);
                if(end%2==0) end--;
                ans+=(beg+end)*((end-beg)/2+1)/2;
                if(l%2==r%2) {
                    if(isPal(l,r,n)) {
                        ans-=r-l+1;
                    }
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}