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
        q.pop_front();
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
#define vt vector
// #define endl "\n"
#define double long double
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
FastMod fs(mod);
struct Node {
    ll mx;
    Node* left;
    Node* right;
    ll lazy;
    Node() {
        this->left=nullptr;
        this->right=nullptr;
        this->lazy=0;
    }
};
Node* build(vector<ll> &a, int l, int r) {
    Node* ret = new Node();
    if(l==r) {
        ret->mx=a[l];
        return ret;
    }
    Node* left = build(a, l, (l+r)/2);
    Node* right = build(a, (l+r)/2+1, r);
    ret->mx=max(left->mx, right->mx);
    ret->left=left;
    ret->right=right;
    return ret;
}
Node* rangeAdd(Node* old, int l, int r, int a, int b, ll val) {
    // cout << "LINE 191 " << old << l << " " << r << " " << a << " " << b << " " << val << endl;
    Node* here = new Node();
    if(l==a&&r==b) {
        here->mx=old->mx+val;
        here->lazy=old->lazy+val;
        here->left=old->left;
        here->right=old->right;
        return here;
    }
    if(old->lazy!=0) {
        Node* nlft = new Node();
        nlft->mx = old->left->mx+old->lazy;
        nlft->lazy = old->left->lazy+old->lazy;
        nlft->left = old->left->left;
        nlft->right = old->left->right;
        Node* nrt = new Node();
        nrt->mx = old->right->mx+old->lazy;
        nrt->lazy = old->right->lazy+old->lazy;
        nrt->left=old->right->left;
        nrt->right=old->right->right;
        old->left = nlft;
        old -> right = nrt;
        old->lazy=0;
    }
    Node* left = old->left;
    Node* right = old->right;
    if((l+r)/2>=a) {
        left=rangeAdd(old->left, l, (l+r)/2, a, min((l+r)/2, b), val);
    }
    if((l+r)/2+1<=b) {
        right=rangeAdd(old->right, (l+r)/2+1, r, max((l+r)/2+1, a),b, val);
    }
    here->mx = max(left->mx, right->mx);
    here->left = left;
    here->right = right;
    return here;
}
ll getMax(Node* node, int l, int r, int a, int b) {
    // cout << "CALLLED " << l << " " << r << " " << a << " " << b << endl;
    if(l==a&&r==b) {
        // cout << "RETURNING " << l << " " << r << " " << a << " " << b << " " << node->mx << endl;
        return node->mx;
    }
    ll ans = 0;
    if(node->lazy!=0&&node->left!=nullptr) {
        Node* nlft = new Node();
        nlft->mx = node->left->mx+node->lazy;
        nlft->lazy = node->left->lazy+node->lazy;
        nlft->left = node->left->left;
        nlft->right = node->left->right;
        Node* nrt = new Node();
        nrt->mx = node->right->mx+node->lazy;
        nrt->lazy = node->right->lazy+node->lazy;
        nrt->left=node->right->left;
        nrt->right=node->right->right;
        node->left = nlft;
        node -> right = nrt;
        node->lazy=0;
    }
    if((l+r)/2>=a) {
        ans=max(ans, getMax(node->left, l, (l+r)/2, a, min((l+r)/2, b)));
    }
    if((l+r)/2+1<=b) {
        ans=max(ans, getMax(node->right, (l+r)/2+1, r, max((l+r)/2+1, a),b));
    }
    // cout << "RETURNING " << l << " " << r << " " << a << " " << b << " " << ans << endl;
    return ans;
}
vector<Node*> roots;
struct RMQ {
    vt<vt<ll>> sparse;
    vt<int> lg;
    RMQ(vt<ll> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<ll>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=max(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMax(int lo, int hi) {
        int log = lg[hi-lo+1];
        return max(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
vt<int> diff;
int n,q;
void doStuff(int aa, int bb, RMQ &rm) {
    if(aa==bb) return;
    int orig = rm.getMax(aa,bb);
    if(getMax(roots.back(), 0, n-1, aa,bb)>=orig) {
        int lo = -1, hi = q;
        while(lo+1<hi) {
            int mid = (lo+hi+1)/2;
            if(getMax(roots[mid], 0, n-1, aa, bb)>=orig) {
                hi=mid;
            } else {
                lo=mid;
            }
        }
        // cout << "LINE 299 " << aa << " " << bb << " " << hi << endl;
        diff[hi]++;
    }
    doStuff(aa, (aa+bb)/2, rm);
    doStuff((aa+bb)/2+1, bb, rm);
    
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    cin >> n >> q;
    vt<ll> a(n), b(n);
    vt<int> type(n);
    diff.resize(q+1);
    F0R(i, n) {
        cin >> type[i];
    }
    F0R(i, n) {
        cin >> a[i];
        if(type[i]) b[i]=a[i];
        else b[i]=-inf;
    }
    roots.add(build(b,0,n-1));
    RMQ rm(a, 20);
    F0R(j, q) {
        int l,r,bbb;
        cin >> l >> r >> bbb;
        l--;
        r--;
        roots.add(rangeAdd(roots.back(), 0, n-1, l, r, bbb));
    }
    doStuff(0, n-1, rm);
    // cout << diff << endl;
    FOR(i, 1, q+1) diff[i]+=diff[i-1];
    FOR(i, 1, q+1) cout << diff[i] << endl;
    return 0;
}