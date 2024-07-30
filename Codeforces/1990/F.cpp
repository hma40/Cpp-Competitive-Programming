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
    vt<int> tree;
    vt<int> mx;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
        mx.resize(2*np);
    }
    int getInd(int l, int r, int find) {
        r++;
        while(l+1<r) {
            int mid = (l+r)/2;
            if(getMax(mid, r-1)==find) {
                l=mid;
            } else {
                r=mid;
            }
        }
        return l;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
            mx[i+n]=mx[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
            mx[i]=max(mx[2*i], mx[2*i+1]);
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        mx[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
            mx[pos]=max(mx[2*pos], mx[2*pos+1]);
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            a/=2;
            b/=2;
        }
        return ans;
    }
    int getMax(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=max(ans, tree[a++]);
            if(b%2==0) ans=max(ans, tree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        SegTree st(n);
        st.build(v);
        while(q--) {
            int x,l,r;
            cin >> x >> l >> r;
            l--;
            r--;
            if(x==1) {
                while(r-l>=2) {
                    int s = st.rangeQuery(l,r);
                    int mx = st.getMax(l,r);
                    if(mx*2>=s) {
                        int ind = st.getInd(l,r,mx);
                        
                    } else {
                        break;
                    }
                }
                if(r-l>=2) {
                    cout << r-l+1 << endl;
                } else {
                    cout << -1 << endl;
                }
            } else {

            }
        }
    }
    return 0;
}