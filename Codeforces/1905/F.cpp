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
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
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
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        bool bad = false;
        F0R(i, n) {
            v[i]--;
            if(v[i]!=i) bad=true;
        }      
        if(!bad) {
            cout << n-2 << endl;
            continue;
        }
        SegTree st(n);
        vt<int> left(n),right(n);
        map<pair<int,int>,int> ansInc;
        st.set(v[0], 1);
        FOR(i, 1, n) {
            left[i]=st.rangeQuery(0,i-1);
            st.set(v[i], 1);
        }
        SegTree st2(n);
        st2.set(v[n-1], 1);
        R0F(i, n-1) {
            right[i]=st2.rangeQuery(i+1, n-1);
            st2.set(v[i], 1);
        }
        // cout << left << " " << right << endl;
        vt<int> inv(n);
        F0R(i, n) inv[v[i]]=i;
        int cor = 0;
        vt<int> mx(n, -1),mn(n,-1);
        int ind = 0;
        FOR(i, 1, n) {
            mx[i]=ind;
            if(v[i]>v[ind]) {
                ind=i;
            }
        }
        ind=n-1;
        R0F(i, n-1) {
            mn[i]=ind;
            if(v[i]<v[ind]) ind=i;
        }
        // cout << mx << mn << endl;
        F0R(i, n) {
            if(left[i]==i&&right[i]==n-i-1) {
                cor++;
            } else if(left[i]==i&&right[i]==n-i-2) {
                int swap0 = i, swap1 = inv[i];
                if(swap0>swap1) swap(swap0,swap1);
                ansInc[{swap0,swap1}]++;
            } else if(right[i]==n-i-1&&left[i]==i-1) {

                int swap0 = i, swap1 = inv[i];
                if(swap0>swap1) swap(swap0,swap1);
                // cout << "LINE 160 " << i << " " << swap0 << " " << swap1 << endl;
                ansInc[{swap0,swap1}]++;
            } else if(v[i]==i&&left[i]==i-1) {
                ansInc[{mx[i], mn[i]}]++;
            }
        }
        // cout << cor << " " << ansInc << endl;
        int ans = 0;
        trav(x, ansInc) ans=max(ans, x.s);
        cout << ans+cor << endl;
    }
    return 0;
}
/*
2 3 1 4 5 6
*/