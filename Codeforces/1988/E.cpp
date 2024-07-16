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
/*
1: (2)(1) before, 0 during, (1)(2) after
2: 
*/
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=min(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        if(lo>hi) return -1;
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
void add (vt<int> &pref, int lo, int hi, int amt) {
    if(lo>hi) return;
    pref[lo]+=amt;
    pref[hi+1]-=amt;
}
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
        // SegTree st(n);
        vt<int> before(n, -1), bbefore(n, -1);
        // st.pointSet(0, v[0]);
        RMQ r(v, 22);
        FOR(i, 1, n) {
            // st.pointSet(i, v[i]);
            if(r.getMin(0, i-1)>v[i]) continue;
            int lo = 0, hi = i;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(r.getMin(mid,i-1)<v[i]) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            before[i]=lo;
            if(lo==0) continue;
            if(r.getMin(0, lo-1)>v[i]) continue;
            int l = 0;
            hi = lo;
            while(l+1<hi) {
                int mid = (l+hi)/2;
                // cout << mid << " " << st.rangeQuery(mid, lo-1) << endl;
                if(r.getMin(mid, lo-1)<v[i]) {
                    l=mid;
                } else {
                    hi=mid;
                }
            }
            bbefore[i]=l;
        }
        vt<int> after(n,n), aafter(n,n);
        // RMQ r(v, 22);
        // stt.pointSet(n-1, v[n-1]);
        R0F(i, n-1) {
            // r.getMin(i, v[i]);
            if(r.getMin(i+1, n-1)>v[i]) continue;
            int lo = i, hi = n-1;
            while(lo+1<hi) {
                int mid = (1+lo+hi)/2;
                if(r.getMin(i+1,mid)<v[i]) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            after[i]=hi;
            if(hi==n-1) continue;
            if(r.getMin(hi+1, n-1)>v[i]) continue;
            lo = hi;
            int h = n-1;
            while(lo+1<h) {
                int mid = (1+lo+h)/2;
                // cout << mid << " " << st.rangeQuery(mid, lo-1) << endl;
                if(r.getMin(hi+1, mid)<v[i]) {
                    h=mid;
                } else {
                    lo=mid;
                }
            }
            aafter[i]=h;
        }
        // cout << after << aafter << endl;
        vt<int> pref(n+1);
        F0R(i, n) {
            // cout << "-----------------" << endl;
            if(before[i]!=-1) {
                //0-before-1, before+1-i-1
                // cout << "LINE 278 " << before[i] << " " << v[i]*(after[i]-i)*(i-before[i]) << " " << v[i]*(after[i]-i)*(i-bbefore[i]) << endl;
                // cout << "LINE 280 ADDING: 0 " << before[i]-1 << " " << v[i]*(after[i]-i)*(i-before[i]) << endl; 
                // cout << "ADDING: " << before[i]+1 << " " << i-1 << " " << v[i]*(after[i]-i)*(i-before[i]-1) << endl;
                // cout << "ADDING: " << before[i] << " " << v[i]*(after[i]-i)*(i-bbefore[i]-1) << endl;
                add(pref, 0, before[i]-1, v[i]*(after[i]-i)*(i-before[i]));

                add(pref, before[i]+1, i-1,  v[i]*(after[i]-i)*(i-before[i]-1));
                add(pref, before[i], before[i], v[i]*(after[i]-i)*(i-bbefore[i]-1));
            } else {
                // cout << "LINE 283 ADDING " << before[i] << " " << v[i]*(after[i]-i)*(i-before[i]-1) << endl;
                add(pref, 0, i-1, v[i]*(after[i]-i)*(i-before[i]-1));
            }
            if(after[i]!=n) {
                //0-before-1, before+1-i-1
                // cout << "LINE 288: " << after[i] << " " << v[i]*(after[i]-i)*(i-before[i]) << " " << v[i]*(aafter[i]-i-1)*(i-before[i]) << endl;
                // cout << "LINE 291 ADDING " << i+1 << " " << after[i]-1 << " " << v[i]*(after[i]-i-1)*(i-before[i]) << endl;
                // cout << "LINE 291 ADDING " << after[i]+1 << " " << n-1 << " " << v[i]*(after[i]-i)*(i-before[i]) << endl;
                // cout << "ADDING " << after[i] << " " <<  v[i]*(aafter[i]-i-1)*(i-before[i]) << endl;
                add(pref, i+1, after[i]-1, v[i]*(after[i]-i-1)*(i-before[i]));
                add(pref, after[i]+1, n-1,  v[i]*(after[i]-i)*(i-before[i]));
                add(pref, after[i], after[i], v[i]*(aafter[i]-i-1)*(i-before[i]));
            } else {
                // cout << "LINE 293: " << after[i] << " " << v[i]*(after[i]-i-1)*(i-before[i]) << endl;
                add(pref, i+1, n-1, v[i]*(after[i]-i-1)*(i-before[i]));
            }
        }
        FOR(i, 1, n+1) pref[i]+=pref[i-1];
        F0R(i, n) cout << pref[i] << " ";
        cout << endl;
    }
    return 0;
}