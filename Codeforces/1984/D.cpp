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
bool allA(int hash, int size, Hash &all) {
    return all.getHash(0,size-1)==hash;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sd = rand()%mod;
    F0R(i, 10000) {
        sd*=rand();
        sd+=rand();
        sd%=mod;
    }
    pw.add(1);
    F0R(i, 200050) {
        pw.add(pw.back()*sd%mod);
    }
    string alla = "";
    F0R(i, 200050) alla+='a';
    Hash hss(alla);
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        Hash hs(s);
        set<int> nona;
        F0R(i, s.size()) {
            if(s[i]!='a') {
                if(nona.size()==0) {
                    nona.insert(i);   
                } else {
                    if(s[i]==s[*nona.begin()]) {
                        nona.insert(i);
                    }
                }
            }
        }
        // cout << nona << endl;
        if(nona.size()==0) {
            cout << s.size()-1 << endl;
            continue;
        }
        nona.insert(s.size());
        int ans = 0;
        FOR(len, 1, s.size()+1) {
            int last = *nona.begin()+len;
            if(last>s.size()) break;
            bool fail = false;
            int hsh = hs.getHash(*nona.begin(), last-1);
            int minDist = *nona.begin();
            while(true) {
                int next =*nona.lower_bound(last);
                // cout << "LINE 126 " << len << " " << last << " " << next << endl;
                if(!allA(hs.getHash(last,next-1),next-last, hss)) {
                    // cout << "FAIL DUE TO 128 " << endl;
                    fail=true;
                }
                if(next==s.size()) break;
                // cout << last << " " << next << endl;
                minDist=min(minDist, next-last);
                last=next;
                next=last+len;
                // cout << "LINE 133 " << last << " " << next << endl;
                if(next>s.size()) {
                    // cout << "FAIL DUE TO 136 " << endl;
                    fail=true;
                    break;
                }
                // cout << "LINE 138 " << endl;
                if(hs.getHash(last,next-1)!=hsh) {
                    // cout << "FAIL DUE TO 142 " << endl;
                    fail=true;
                }
                last=next;
            }
            // cout << "FAILED? " << fail << " " << minDist << endl;
            if(!fail) {
                ans+=minDist+1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}