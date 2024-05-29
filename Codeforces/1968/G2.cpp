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
__int128_t MOD = (1LL<<61)-1;
__int128_t pol;
vt<__int128_t> polPow;
int MAXN = 2e5+50;
struct Hash {
    vt<__int128_t> prefHash;
    Hash(string s) {
        prefHash.resize(s.size()+1);
        prefHash[0]=0;
        F0R(i, s.size()) {
            prefHash[i+1]=(prefHash[i]*pol+s[i])%MOD;
        }
    }
    int getHash(int s, int e) {
        // cout << "getHash called for " << s << " " << e << endl;
        __int128_t raw = prefHash[e+1]-prefHash[s]*polPow[e-s+1];
        return (raw%MOD+MOD)%MOD;
    }
};
vt<int> largest;
struct RMQ {
    vt<vt<int>> sparse;
    RMQ(vt<int> orig) {
        sparse.resize(orig.size(), vt<int>(20));
        F0R(i, orig.size()) {
            sparse[i][0]=orig[i];
        }
        FOR(i, 1, 20) {
            // cout << "LINE 81 " << orig.size() << " " << (1<<i) << " " << orig.size()-(1<<i)+1 << endl;
            if(orig.size()+1<=(1<<i)) continue;
            F0R(j, orig.size()-(1<<i)+1) {
                // cout << i << " " << j << " " << j+(1<<(i-1)) << endl;
                sparse[j][i]=max(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
        // cout << sparse << endl;
    }
    int getMax(int lo, int hi) {
        int sz = hi-lo+1;
        // cout << endl << "LINE 92 " << lo << " " << hi << " " << sz << " " << largest[sz] << " " << hi-(1<<largest[sz])+1 << endl;
        // cout << sparse[lo][largest[sz]] << endl;
        // cout << sparse[hi-(1<<largest[sz])]
        return max(sparse[lo][largest[sz]], sparse[hi-(1<<largest[sz])+1][largest[sz]]);
    }
    int lastLB(int hi, int amount) {
        int lo = 0;
        int h = hi;
        // cout << "LINE 100 " << hi << " " << amount << endl;
        while(lo+1<h) {
            // cout << lo << " " << h << endl;
            int mid = (lo+h)/2;
            if(getMax(mid,hi)<amount) {
                h=mid;
            } else {
                lo=mid;
            }
        }
        if(sparse[h][0]>=amount) {
            // cout << "RETURNING " << h << endl;
            return h;
        }
        // cout << "RETURNING " << lo << endl;
        return lo;
    }
};
signed main() { 
    srand(time(NULL));
    pol=rand()%MOD;
    pol*=rand();
    pol%=MOD;
    pol*=rand();
    pol%=MOD;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    polPow.add(1);
    largest.add(0);
    int temp = 1;
    FOR(i, 1, MAXN) {
        if(temp*2==i) {
            temp*=2;
            largest.add(largest.back()+1);
        } else {
            largest.add(largest.back());
        }
    }
    // cout << largest << endl;
    FOR(i, 1, MAXN) polPow.add(polPow.back()*pol%MOD);

    int t;
    cin >> t;
    while(t--) {
        int n,l,r;
        string s;
        cin >> n >> l >> r >> s;
        Hash h(s);
        vt<int> LCP(n);
        F0R(i, n) {
            if(s[i]!=s[0]) continue;
            int lo = 0, hi = n-i;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(h.getHash(0,mid)==h.getHash(i, i+mid)) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            LCP[i]=lo+1;
        }
        RMQ rr(LCP);
        vt<int> maxSeg(n+1);
        maxSeg[0]=inf;
        FOR(i, 1, n+1) {
            int cur = n-i;
            while(cur>=0) {
                // cout << i << " " << cur << endl;
                int nxt = rr.lastLB(cur, i);
                maxSeg[i]++;
                cur=nxt;
                cur-=i;
            }
        }
        // cout << maxSeg << endl;
        vt<int> ans(n+1);
        int ind = n;
        FOR(i, 1, n+1) {
            while(maxSeg[ind]<i) {
                ind--;
            }
            ans[i]=ind;
        }
        cout << ans[l];
        FOR(i, l+1, r+1) cout << " " << ans[i];
        cout << endl;
    }
    return 0;
}