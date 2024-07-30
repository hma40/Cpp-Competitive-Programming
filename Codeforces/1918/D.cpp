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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<int> dp;
vt<int> v;
int n;
vt<int> pref;
vt<int> firstPos;
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
            tree[i]=min(tree[2*i],tree[2*i+1]);
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=min(tree[2*pos],tree[2*pos+1]);
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=min(tree[2*pos],tree[2*pos+1]);
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=min(ans,tree[a++]);
            if(b%2==0) ans=min(ans,tree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
};
int solve(int maxSum) {
    SegTree st(n);
    //dp[i] = min cost if blocking i
    int left = n-1;
    int sum = 0;
    R0F(right, n) {
        while(sum<=maxSum&&left>=0) {
            // left--;
            sum+=v[left];
            left--;
        }
        if(left==-1) {
            if(sum<=maxSum) {
                firstPos[right]=-1;
            } else {
                firstPos[right]=0;
            }
        } else {
            firstPos[right]=left+1;
        }
        sum-=v[right];
    }
    if(firstPos[n-1]==-1) {
        // return maxSum;
        return 0;
    }
    // cout << v << maxSum << firstPos << endl;
    st.set(0,v[0]);
    FOR(i, 1, n) {
        if(firstPos[i]==-1) {
            st.set(i,v[i]);
            continue;
        }
        int bef = 0;
        if(firstPos[i-1]==i-1) {
            bef=st.rangeQuery(i-1,i-1);
        } else {
            bef=st.rangeQuery(firstPos[i-1], i-1);
        }
        st.set(i, bef+v[i]);
    }
    // cout << "RETURNING " << st.rangeQuery(firstPos[n-1], n-1) << " FOR " << maxSum << endl;
    return st.rangeQuery(firstPos[n-1], n-1);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n;
        firstPos.assign(n,0);
        v.assign(n,0);
        F0R(i, n) cin >> v[i];
        dp.assign(n,0);
        pref.assign(n+1,0);
        // F0R(i, n) pref[i+1]=pref[i]+v[i];
        // pref.add(inf);
        // solve(6);
        // break;
        int lo = 0, hi = 1e15;
        while(lo+4<hi) {
            int mid = (lo+hi)/2;
            // cout << lo << " " << mid << " " << hi << endl;
            if(solve(mid)>mid) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        int ans = inf;
        FOR(i, lo, hi+1) {
            ans=min(ans, max(solve(i),i));
        }
        cout << ans << endl;
    }
    return 0;
}
/*
2 numbers
a b
b a
YES obviously (anything)

3 numbers
a b c
b a+c b
NO

5 numbers
a b c d e
b a+c b+d c+e d

a b c d e f g
b a+c b+d c+e d+f e+g f

a c d e g
a+c b+d c+e d+f e+g


*/