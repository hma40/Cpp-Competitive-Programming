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
struct SegTree {
    int n;
    vt<int> beg,end,tree;
    SegTree(int nn): n(nn) {
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n, 1e18);
        FOR(i, n, 2*n) beg[i]=end[i]=i-n;
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
    }  
    void set(int i, int pos, int val) {
        if(i>=n) {
            tree[i]=min(val, tree[i]);
            return;
        }
        if(beg[2*i]<=pos&&end[2*i]>=pos) {
            set(2*i, pos, val);
        } else {
            set(2*i+1, pos, val);
        }
        tree[i]=min(tree[2*i], tree[2*i+1]);
    }
    int getMax(int i, int lo, int hi) {
        // cout << "GETMAX CALLED FOR " << i << " " << lo << " " << hi << endl;
        if(beg[i]==lo&&end[i]==hi) {
            return tree[i];
        }
        int ans = inf;
        if(beg[2*i]<=hi&&end[2*i]>=lo) {
            ans=min(ans, getMax(2*i, lo, min(hi, end[2*i])));
        }
        if(beg[2*i+1]<=hi&&end[2*i+1]>=lo) {
            ans=min(ans, getMax(2*i+1, max(lo, beg[2*i+1]), hi));
        }
        return ans;
    }
};
int solve(int n, int m, int k, vt<pair<int,int>> hello) {
    vt<int> all;
    F0R(i, k) all.add(hello[i].f);
    F0R(i, k) all.add(hello[i].s);
    all.add(0);
    all.add(n);
    sort(begin(all),end(all));
    map<int, int> comp;
    vt<int> invComp;
    trav(x, all) {
        if(!comp.count(x)) {
            comp[x]=invComp.size();
            invComp.add(x);
        }
    }
    // cout << comp << " " << invComp << endl;
    F0R(i, k) {
        hello[i].f=comp[hello[i].f];
        // hello[i].s=comp[hello[i].s];
    }
    // cout << hello << endl;
    SegTree st(invComp.size());
    F0R(i, k) {
        st.set(1, hello[i].f, hello[i].s-1);
    }
    st.set(1, n, m);
    int width = 0, area = 0;   
    // cout << st.tree << endl;
    // cout << st.getMax(1,2,3) << endl;
    // cout << st.beg << st.end << endl;
    width=st.getMax(1, 1, invComp.size()-1);
    FOR(i, 1, invComp.size()) {
        // cout << i << " " << width << " " << invComp[i] << endl;
        if(invComp[i]<=n) {
            area+=(invComp[i]-invComp[i-1])*width;
        }
        width=st.getMax(1, i+1, invComp.size()-1);
    }
    return area;
}
signed main() {
    while(true) {
        int n=5,m=5;
        int k = 10;
        set<pair<int,int>> exist;
        exist.insert({n,1});
        vt<pair<int,int>> hello;
        F0R(i, k) {
            pair<int,int> rd = {rand()%n+1,rand()%m+1};
            if(!exist.count(rd)) {
                exist.insert(rd);
                hello.add(rd);
            } else {
                i--;
            }
        }
        if(solve(n,m,k,hello)>n*m) {
            cout << "FAIL" << endl;
            cout << n << " " << m << " " << k << " " << hello << endl;
            cout << solve(n,m,k,hello) << endl;
            break;
        } else {
            cout <<"OK" << endl;
        }
    }
    return 0;
}
/*
1
6 3 3
1 1
4 3
6 3
*/