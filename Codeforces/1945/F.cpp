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
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> setLazy;
    vt<int> addLazy; 
    //CHANGE THESE!
    int none;
    SegTree(int nn): n(nn) {
        none=(inf);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        // cout << beg << end << endl;
    }
    void pointSet(int i, int index, int val) {
        if(i>=n) {
            tree[i]=val;
            return;
        }
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        tree[i]=(tree[2*i]+tree[2*i+1]);
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    int rangeQuery(int index, int left, int right) {
        if(beg[index]==left&&end[index]==right) return tree[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans=(ans+ r);
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<pair<int,int>> pow(n);
        vt<int> perm(n);
        // vt<int> pow(n),perm(n);
        F0R(i, n) cin >> pow[i].f;
        F0R(i, n) cin >> perm[i];
        F0R(i, n) perm[i]--;
        F0R(i, n) {
            pow[i].s=i;
        }
        sort(begin(pow),end(pow));
        vt<int> map(n);
        F0R(i, n) {
            map[pow[i].s]=i;
        }
        // cout << pow << endl;
        SegTree sex(n);
        int ans = 0;
        int used = 0;
        F0R(i, n) sex.pointSet(i, 1);
        FOR(i, 1, n+1) {
            int lo = 0, hi = n;
            if(sex.rangeQuery(0, n-1)<i) break;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(sex.rangeQuery(mid,n-1)>=i) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            // cout << i << " " << lo << endl;
            if(pow[lo].f*i>ans) {
                ans=pow[lo].f*i;
                used=i;
            }
            sex.pointSet(map[perm[i-1]], 0);
        }
        cout << ans << " " << used << endl;
    }
    return 0;
}