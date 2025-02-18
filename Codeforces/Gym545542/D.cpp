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
struct Node {
    vector<pair<int,int>> data;
    Node* left;
    Node* right;
    Node() {
        left = nullptr;
        right = nullptr;
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
vt<int> hello(vt<int> &a, int mxEle) {
    // cout << "HELLO CALLED FOR " << mxEle << endl;
    int n = a.size();
    vt<int> suffSum(n);
    suffSum[n-1]=(a[n-1]>mxEle? 0:a[n-1]);
    R0F(i, n-1) {
        if(a[i]>mxEle) suffSum[i]=suffSum[i+1];
        else suffSum[i]=suffSum[i+1]+a[i];
    }
    priority_queue<pair<int,int>> pq;
    F0R(i, n) {
        if(a[i]<=mxEle) {
            pq.push({a[i], -i});
        }
    }
    set<int> seq;
    SegTree st(n);
    int overcome = 2*mxEle;
    while(pq.size()) {
        auto tp = pq.top();
        pq.pop();
        tp.s*=-1;
        auto ptr = seq.upper_bound(tp.s);
        if(ptr==seq.end()) {
            seq.insert(tp.s);
            st.set(tp.s,tp.f);
            overcome-=tp.f;
        } else {
            int nxt = *ptr;
            if(overcome<0||suffSum[nxt]-st.rangeQuery(nxt,n-1)>overcome) {
                continue;
            }
            seq.insert(tp.s);
            st.set(tp.s,tp.f);
            overcome-=tp.f;
        }
    }
    vt<int> ret;
    trav(x, seq) ret.add(a[x]);
    // cout << ret << endl;
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> b = a;
        sort(begin(b),end(b));
        pair<int,int> consider = {-1,-1};
        vt<int> pref(n+1);
        F0R(i, n) pref[i+1]=pref[i]+b[i];
        F0R(i, n) {
            if(pref[i+1]<=2*b[i]) continue;
            /*
            bsearch for last j such that a[j]+...+a[i-1]>a[i]
            */
            int lo = 0, hi = i;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(pref[i]-pref[mid]>b[i]) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            consider={b[lo],b[i]};
        }
        vt<int> ans;
        set<int> tried;
        FOR(j, 0, min(n,60LL)) {
            int i = n-1-j;
            if(tried.count(i)) continue;
            if(pref[i+1]<=2*b[i]) continue;
            if(b[i]<consider.f||b[i]>consider.s) continue;
            ans=max(ans, hello(a,b[i]));
        }
        if(ans.size()==0) {
            cout << -1 << endl;
            continue;
        }
        cout << ans.size() << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}
/*

*/