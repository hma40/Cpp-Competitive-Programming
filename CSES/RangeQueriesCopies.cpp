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
#define int long long
#define vt vector
#define endl "\n"
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
struct Node {
    int value;
    Node* left;
    Node* right;
    Node() {
        left=nullptr;
        right=nullptr;
    }
    friend std::ostream& operator<<(std::ostream& os, Node* node) {
        os << "Node(value: " << node->value;
        if (node->left) {
            os << ", left: " << node->left;
        } else {
            os << ", left: null";
        }
        if (node->right) {
            os << ", right: " << node->right;
        } else {
            os << ", right: null";
        }
        os << ")";
        os << endl;
        return os;
    }
};
vector<Node*> roots;
Node* build(vector<int> &a, int l, int r) {
    Node* here = new Node();
    if(l==r) {
        here->value=a[l];
        return here;
    }
    Node* left = build(a, l, (l+r)/2);
    Node* right = build(a, (l+r)/2+1, r);
    here->left=left;
    here->right=right;
    here->value=left->value+right->value;
    return here;
}
Node* modify(Node* old, int l, int r, int k, int val) {
    Node* here = new Node();
    if(l==k&&r==k) {
        here->value=val;
        return here;
    }
    if((l+r)/2>=k) {
        here->left = modify(old->left,l, (l+r)/2, k, val);
        here->right = old->right;
    } else {
        here->left = old->left;
        here->right = modify(old->right, (l+r)/2+1, r, k, val);
    }
    here->value = here->left->value + here->right->value;
    return here;
}
int query(Node* node, int l, int r, int a, int b) {
    // cout << "QUERY CALLED " << l << " " << r << " " << a << " " << b << endl;
    if(l==a&&r==b) {
        return node->value;
    }
    int ans = 0;
    if((l+r)/2>=a) {
        ans+=query(node->left, l, (l+r)/2, a, min((l+r)/2, b));
    }
    if((l+r)/2+1<=b) {
        ans+=query(node->right, (l+r)/2+1, r, max((l+r)/2+1, a),b);
    }
    return ans;
}
FastMod fs(mod);
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    F0R(i, n) cin >> a[i];
    roots.add(build(a,0,n-1));
    // cout << roots << endl;
    while(q--) {
        int qt;
        cin >> qt;
        if(qt==1) {
            int k,aa,x;
            cin >> k >> aa >> x;
            k--;
            aa--;
            roots[k] = modify(roots[k], 0, n-1, aa, x);
        } else if(qt==2) {
            int k,aa,x;
            cin >> k >> aa >> x;
            k--;
            aa--;
            x--;
            cout << query(roots[k], 0, n-1, aa, x) << endl;
        } else {
            int k;
            cin >> k;
            k--;
            roots.add(roots[k]);
        }
        // cout << roots << endl;
    }
    return 0;
}