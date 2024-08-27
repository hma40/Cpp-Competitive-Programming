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
struct TestCase {
    int n,k;
    vt<int> a;
    int q;
    vt<pair<int,int>> queries;
};
void fill_rand(vt<int> &v, int lo, int hi) {
    for(auto &x: v) {
        x=rnd()%(hi-lo+1)+lo;
    }
}
void rand_tree(vt<vt<int>> &adj) {
    for(int i = 1; i < adj.size(); i++) {
        int par = rnd()%i;
        adj[par].add(i);
        adj[i].add(par);
    }
}
void print_TC(TestCase tc) {
    cout << tc.n << " " << tc.k << " " << tc.q << endl << tc.a << endl << tc.queries << endl;
}
TestCase randTC() {
    TestCase tc;
    tc.n=20;
    tc.q=5;
    tc.k=rnd()%tc.n+1;
    tc.a.resize(tc.n);
    F0R(i, tc.n) {
        tc.a[i]=rnd()%tc.n+1;
    }
    while(tc.queries.size()<tc.q) {
        int l = rnd()%tc.n, r = rnd()%tc.n;
        if(l+tc.k-1>r) {
            continue;
        }
        tc.queries.add({l,r});
    }
    return tc;
}
struct WrongSol {
    int getAns(int &k, multiset<int> &ms) {
    return k-(*ms.rbegin());
}
struct SegTree {
    int n;
    vector<int> tree, setLazy, begin, end;
    void prop(int i) {
        if(setLazy[i]!=-100) {
            setLazy[2*i+1]=setLazy[2*i]=setLazy[i];
            tree[2*i]=tree[2*i+1]=setLazy[i]*(end[2*i+1]-begin[2*i+1]+1);
            setLazy[i]=-100;
        }
    }
    SegTree(int nn) {
        n = 1;
        while(n<nn) n*=2;
        tree.resize(2*n);
        setLazy.resize(2*n, -100);
        begin.resize(2*n);
        end.resize(2*n);
        for(int i = n; i < 2*n; i++) {
            begin[i]=end[i]=i-n;
        }
        for(int i = n-1; i > 0; i--) {
            begin[i]=begin[2*i];
            end[i]=end[2*i+1];
        }
    }
    void rangeSet(int i, int amt, int lo, int hi) {
        if(i<n) prop(i);
        if(begin[i]==lo&&end[i]==hi) {
            tree[i]=amt*(hi-lo+1);
            setLazy[i]=amt;
            return;
        }
        if(begin[2*i]<=hi&&end[2*i]>=lo) {
            rangeSet(2*i, amt, lo, min(hi, end[2*i]));
        }
        if(begin[2*i+1]<=hi&&end[2*i+1]>=lo) {
            rangeSet(2*i+1, amt, max(lo, begin[2*i+1]), hi);
        }
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    int query(int i, int lo, int hi) {
        if(i<n) prop(i);
        if(begin[i]==lo&&end[i]==hi) return tree[i];
        int ans = 0;
        if(begin[2*i]<=hi&&end[2*i]>=lo) {
            ans+=query(2*i, lo, min(end[2*i], hi));
        }
        if(begin[2*i+1]<=hi&&end[2*i+1]>=lo) {
            ans+=query(2*i+1, max(lo, begin[2*i+1]), hi);
        }
        return ans;
    }
};
    vt<int> solve(TestCase tc) {
 int n,k,q;
 n=tc.n;
 k=tc.k;
 q=tc.q;
        // cin >> n >> k >> q;
        vector<int> v=tc.a;
        for(int i = 0; i < n; i++) {
            // cin >> v[i];
            v[i]=v[i]-i;
        }
        vector<int> ans(n);//ans[i] is answer from i to i+k-1
        map<int,int> mp;
        multiset<int> active;
        for(int i = 0; i < k; i++) {
            if(mp[v[i]]==0) {
                mp[v[i]]=1;
                active.insert(1);
            } else {
                active.erase(active.find(mp[v[i]]));
                mp[v[i]]++;
                active.insert(mp[v[i]]);
            }
        }
        // assert(false);
        ans[0]=getAns(k, active);
        for(int i = k; i < n; i++) {
            //erase v[i-k]
            active.erase(active.find(mp[v[i-k]]));
            mp[v[i-k]]--;
            if(mp[v[i-k]]!=0) active.insert(mp[v[i-k]]);

            if(mp[v[i]]==0) {
                mp[v[i]]=1;
                active.insert(1);
            } else {
                active.erase(active.find(mp[v[i]]));
                mp[v[i]]++;
                active.insert(mp[v[i]]);
            }
            ans[i-k+1]=getAns(k,active);
        }
        // cout << "LINE 193 " << ans << endl;
        vector<array<int,3>> queries(q);
        vector<int> an(q);
        // assert(false);
        // cout << tc.queries << q << endl;
        for(int i = 0; i < q; i++) {
            // cout << i << endl;
            queries[i][2]=i;
            queries[i][0]=tc.queries[i].f;
            queries[i][1]=tc.queries[i].s;
            // cin >> queries[i][0] >> queries[i][1];
            // queries[i][0]--;
            // queries[i][1]--;
            queries[i][0]*=-1;
        }
        // assert(false);
        sort(begin(queries),end(queries));
        for(int i = 0; i < q; i++) queries[i][0]*=-1;
        // assert(false);
        SegTree st(n);
        st.rangeSet(1, ans[n-k], n-k, n-k);
        int cur = n-k;
 stack<pair<int,int>> s;
        s.push({ans[n-k], n-k});
        // cout << ans << endl;
        for(int i = 0; i < q; i++) {
            while(cur!=queries[i][0]) {
                cur--;
                int here = cur;
                while(s.size()&&s.top().first>ans[cur]) {
                    here=s.top().second;
                    s.pop();
                }
                // cout << cur << " " << here << " " << ans[cur] << endl;
                s.push({ans[cur], here});
                // cout << "RANGESETTING " << cur << " " << here << " TO " << ans[cur] << endl;
                // cout << "HERE: " << here << " CUR: " << cur << endl;
                st.rangeSet(1, ans[cur], cur, here);
            }
            an[queries[i][2]]=st.query(1, queries[i][0], queries[i][1]-k+1);
        }
        return an;
        // string ret = "";
        // cout << an << endl;
        // for(auto x: an) cout << x << endl;
    }
};
struct CorrectSol {
        int getAns(int &k, multiset<int> &ms) {
    return k-(*ms.rbegin());
}
    vt<int> solve(TestCase tc) {
        // assert(false);
int n,k,q;
 n=tc.n;
 k=tc.k;
 q=tc.q;
        // cin >> n >> k >> q;
        vector<int> v=tc.a;
        for(int i = 0; i < n; i++) {
            // cin >> v[i];
            v[i]=v[i]-i;
        }
        vector<int> ans(n);//ans[i] is answer from i to i+k-1
        map<int,int> mp;
        multiset<int> active;
        for(int i = 0; i < k; i++) {
            if(mp[v[i]]==0) {
                mp[v[i]]=1;
                active.insert(1);
            } else {
                active.erase(active.find(mp[v[i]]));
                mp[v[i]]++;
                active.insert(mp[v[i]]);
            }
        }
        // assert(false);
        ans[0]=getAns(k, active);
        for(int i = k; i < n; i++) {
            //erase v[i-k]
            active.erase(active.find(mp[v[i-k]]));
            mp[v[i-k]]--;
            if(mp[v[i-k]]!=0) active.insert(mp[v[i-k]]);

            if(mp[v[i]]==0) {
                mp[v[i]]=1;
                active.insert(1);
            } else {
                active.erase(active.find(mp[v[i]]));
                mp[v[i]]++;
                active.insert(mp[v[i]]);
            }
            ans[i-k+1]=getAns(k,active);
        }
        // cout << "LINE 286 " << ans << endl;
        vector<int> an(q);
        auto fuck = tc.queries;
        // trav(x, fuck) {
            // x.f--;
            // x.s--;
        // }
        // assert(false);
        F0R(i, q) {
            // cout << fuck[i] << v << k << endl;
            int lo = inf;
            for(int j = fuck[i].f+k-1; j <= fuck[i].s; j++) {
                lo=min(lo, ans[j-k+1]);
                // cout << ans << lo << endl;
                an[i]+=lo;
            }
        }
        return an;
    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        // print_TC(tc);
        // return 0;
        WrongSol w;
        // assert(false);
        CorrectSol c;
        auto wa = w.solve(tc);
        // assert(false);
        auto cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}