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
    vt<int> tree2;
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
        tree2.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        FOR(i, 1, 2*n) {
            tree2[i]=end[i]-beg[i]+1;
        }
        // cout << beg << end << endl;
    }
    void prop(int i) {  
        if(addLazy[i]!=none) {
            if(addLazy[2*i]!=none) {
                addLazy[2*i]=addLazy[2*i]+addLazy[i];
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(addLazy[2*i+1]!=none) {
                addLazy[2*i+1]=addLazy[2*i+1]+addLazy[i];
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]+=addLazy[i];
            tree[2*i]+=addLazy[i];
            addLazy[i]=none;
        }
    }
    int rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) {
            if(tree[index]==0) {
                return tree2[index];
            }
            return 0;
        }
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans+=r;
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        // tree[i]=combi(tree[2*i], tree[2*i+1]);
        if(tree[2*i]<tree[2*i+1]) {
            tree[i]=tree[2*i];
            tree2[i]=tree2[2*i];
        } else if(tree[2*i]>tree[2*i+1]) {
            tree[i]=tree[2*i+1];
            tree2[i]=tree2[2*i+1];
        } else {
            tree[i]=tree[2*i];
            tree2[i]=tree2[2*i]+tree2[2*i+1];
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        SegTree st(n);
        vt<pair<int,int>> v(m);
        F0R(i, m) {
            cin >> v[i].f >> v[i].s;
            v[i].f--;
            v[i].s--;
        }
        F0R(i, m) {
            st.rangeAdd(v[i].f, v[i].s-1, 1);
        }
        // cout << 1+st.rangeQuery(0,n-1) << endl;
        int ans = st.rangeQuery(0,n-1);
        set<pair<int,int>> start,end;
        F0R(i, m) {
            start.insert({v[i].f, i});
            end.insert({v[i].s, i});
        } 
        // FOR(i, 1,st.n) {
        //     st.prop(i);
        // }
        // cout << st.tree << " " << st.tree2 << endl;
        for(int cur = 0; cur < n; cur++) {
            while(start.size()&&(*start.begin()).f==cur) {
                auto x = (*start.begin());
                start.erase(x);
                st.rangeAdd(v[x.s].f, v[x.s].s-1, -1);
                st.rangeAdd(v[x.s].s, n-1, 1);
                if(v[x.s].f!=0) {
                    st.rangeAdd(0, v[x.s].f-1, 1);
                }
            }
            ans=max(ans, st.rangeQuery(0,n-1));
            // FOR(i, 1,st.n) {
            //     st.prop(i);
            // }
            // cout << st.tree << " " << st.tree2 << endl;
            while(end.size()&&(*end.begin()).f==cur) {
                auto x = (*end.begin());
                end.erase(x);
                st.rangeAdd(v[x.s].f, v[x.s].s-1, 1);
                st.rangeAdd(v[x.s].s, n-1, -1);
                if(v[x.s].f!=0) {
                    st.rangeAdd(0, v[x.s].f-1, -1);
                }
            }
        }
        cout << n-ans << endl;
    }
    return 0;
}
/*
10010012
*/