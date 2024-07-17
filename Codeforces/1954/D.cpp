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
ll mod = 998244353;
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
struct SegTree {
    int n;
    vt<int> tree;
    vt<int> data;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
        data.resize(np);
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
        data[pos]=x;
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=(tree[2*pos]+tree[2*pos+1])%mod;
        }
    }
    void add(int pos, int x) {
        data[pos]+=x;
        data[pos]%=mod;
        pos+=n;
        tree[pos]+=x;
        tree[pos]%=mod;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=(tree[2*pos]+tree[2*pos+1])%mod;
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            ans%=mod;
            a/=2;
            b/=2;
        }
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vt<int> a(n);
    F0R(i, n) cin >> a[i];
    sort(begin(a),end(a));
    int MAXN = 5002;
    // vt<SegTree> dp(MAXN+2, SegTree(MAXN+2));
    // dp[0].set(0,1);
    vt<vt<int>> dpp(MAXN+5, vt<int>(MAXN+5));
    vt<int> sum(MAXN+5);
    dpp[0][0]=sum[0]=1;
    F0R(i,n) {
        R0F(j, MAXN) {
            if(j>=a[i]) {
                dpp[j][a[i]]+=sum[j-a[i]];
                dpp[j][a[i]]%=mod;
                sum[j]+=sum[j-a[i]];
                sum[j]%=mod;
                // dp[j].add(a[i], dp[j-a[i]].rangeQuery(0,a[i]));
            }
        }
    }
    // trav(x, dp) cout << x.data << endl;
    int ans = 0;
    F0R(s, MAXN) {
        F0R(max, MAXN) {
            if(s<2*max) {
                ans+=max*dpp[s][max];
                ans%=mod;
            } else {
                ans+=(s+1)/2*dpp[s][max];
                ans%=mod;
            }
        }
    }
    cout << ans << endl;
    return 0;
}