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
    vt<int> start,end,tree,lazy;
    SegTree(int nn): n(nn) {
        while((n&(-n))!=n) {
            n++;
        }
        start.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        FOR(i, n, 2*n) start[i]=end[i]=i-n;
        ROF(i, 1, n) {
            start[i]=start[2*i];
            end[i]=end[2*i+1];
        }
        lazy.resize(2*n);
    }
    void prop(int i) {
        if(lazy[i]!=0) {
            tree[2*i]+=lazy[i];
            tree[2*i+1]+=lazy[i];
            lazy[2*i]+=lazy[i];
            lazy[2*i+1]+=lazy[i];
            lazy[i]=0;
        }
    }
    void change(int L, int R, int amount, int i) {
        if(i>=n) {
            tree[i]+=amount;
            return;
        }
        if(L==start[i]&&R==end[i]) {
            lazy[i]+=amount;
            tree[i]+=amount;
            return;
        }
        prop(i);
        if(L<=end[2*i]) {
            change(L, min(R, end[2*i]), amount, 2*i);
        }
        if(R>=start[2*i+1]) {
            change(max(L, start[2*i+1]), R, amount, 2*i+1);
        }
        tree[i]=min(tree[2*i], tree[2*i+1]);
    }
    int getMin(int L, int R, int i) {
        // cout << "GETMIN CALLED FOR " << L << " " << R << " " << i << endl;
        if(L==start[i]&&R==end[i]) {
            // cout << "MIN FOR " << L << " " << R << " IS " << tree[i] << " LINE 101 " << i << endl;
            return tree[i];
        }
        prop(i);
        int ans = inf;
        if(L<=end[2*i]) {
            ans=min(ans, getMin(L, min(R, end[2*i]), 2*i));
        }
        if(R>=start[2*i+1]) {
            ans=min(ans, getMin(max(L, start[2*i+1]), R, 2*i+1));
        }
        // cout << "MIN FOR " << L << " " << R << " IS " << ans << " " << i << endl;
        return ans;
    }
    void debug() {
        FOR(i, 1, n) prop(i);
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
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        SegTree st(n);
        map<int, pi> mp;
        int lastCons = n-1;
        int ans = 0;
        R0F(i, n) {
            // cout << "i=" << i << endl;
            // st.debug();
            // cout << st.tree << endl;
            // cout << st.tree << " " << st.lazy << endl;
            if(!mp.count(v[i])) { 
                // cout << "CHANGING: " << i << " " << lastCons << " " << 1 << endl;
                st.change(i, lastCons, 1, 1);
                mp[v[i]]={i, -1};
            } else {
                auto temp = mp[v[i]];
                if(temp.s==-1) {
                    // cout << "CHANGING: " << temp.f << " " << lastCons << " " << -1 << endl;
                    st.change(temp.f, lastCons, -1, 1);
                    // st.debug();
                    // cout << st.tree << "LINE 148 " << endl;
                } else {
                    // cout << "CHANGING: " << temp.f << " " << lastCons << " " << -1 << endl;
                    st.change(temp.f, lastCons, -1, 1);
                    // cout << "CHANGING: " << temp.s << " " << lastCons << " " << 1 << endl;
                    st.change(temp.s, lastCons, 1, 1);
                    // st.debug();
                    // cout << "LINE 153 " << st.tree << endl;
                }
                // cout << "CHANGING: " << i << " " << lastCons << " " << 1 << endl;
                st.change(i, lastCons, 1, 1);
                // cout << "CHANGING: " << temp.f << " " << lastCons << " " << -1 << endl;
                st.change(temp.f, lastCons, -1, 1);
                mp[v[i]]={i, temp.f};
            }
            // cout << "GOT TO LINE 144" << endl;
            if(st.getMin(i, lastCons, 1)==0) {
                // cout << "LINE 156 REACHED " << i << endl;
                // st.debug();
                // cout << st.tree << endl;
                lastCons=i-1;
                ans++;
                mp.clear();
            }
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
9
8 2 9 3 9 1 9 3 5
*/