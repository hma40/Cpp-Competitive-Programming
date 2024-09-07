#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
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
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n;
    cin >> n;
    vt<int> a(n);
    F0R(i, n) cin >> a[i];
    vt<int> firstLeftGreater(n, -1), firstRightGreater(n, n), firstRightSmaller(n, n);
    //index i makes the range FLG[i]<l<=i and FRG<=r<FRS
    stack<int> stk;
    F0R(i, n) {
        while(stk.size()&&a[stk.top()]<a[i]) {
            firstRightGreater[stk.top()]=i;
            stk.pop();
        }
        stk.push(i);
    }
    while(stk.size()) stk.pop();
    R0F(i, n) {
        while(stk.size()&&a[stk.top()]<a[i]) {
            firstLeftGreater[stk.top()]=i;
            stk.pop();
        }
        stk.push(i);
    }
    RMQ r(a, 20);
    F0R(i, n) {
        if(firstRightGreater[i]==n) continue;
        if(r.getMin(firstRightGreater[i], n-1)>a[i]) continue;
        int lo = firstRightGreater[i], hi = n-1;
        while(lo+1<hi) {
            int mid = (lo+hi+1)/2;
            if(r.getMin(firstRightGreater[i], mid)>a[i]) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        firstRightSmaller[i]=hi;
    }
    int q;
    cin >> q;
    vt<int> ans(q);
    vt<array<int,3>> queries(q);
    F0R(i, q) {
        cin >> queries[i][0] >> queries[i][1];
        queries[i][0]--;
        queries[i][1]--;
        queries[i][2]=i;
    }
    sort(begin(queries),end(queries));
    min_pq<array<int,4>> pq;
    //at time pq[i][0] we should add pq[i][3] to pq[i][1] thru pq[i][2]
    F0R(i, n) {
        if(firstRightGreater[i]!=n) {
            pq.push({firstLeftGreater[i]+1, firstRightGreater[i], firstRightSmaller[i]-1, 1});
            pq.push({i+1, firstRightGreater[i], firstRightSmaller[i]-1, -1});
        }
    }
    // cout << pq << endl;
    // cout << firstLeftGreater << firstRightGreater << firstRightSmaller << endl;
    SegTree st(n+1);
    trav(x, queries) {
        while(pq.size()&&pq.top()[0]<=x[0]) {
            auto f = pq.top();
            // cout << f << endl;
            pq.pop();
            st.add(f[1], f[3]);
            st.add(f[2]+1, -f[3]);
        }
        if(st.rangeQuery(0,x[1])==0) {
            ans[x[2]]=0;
        } else {
            ans[x[2]]=1;
        }
        // cout << x << st.tree << endl;
    }
    // cout << ans << endl;
    trav(x, ans) {
        if(x) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
/*
10
10 4 9 2 6 3 1 7 8 5
1
2 4
*/