#include <bits/stdc++.h>
using namespace std;
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
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
class SparseSegtree {
  private:
	struct Node {
		int freq = 0;
		int lazy = 0;
		Node *left = nullptr;
		Node *right = nullptr;
	};
	Node *root = new Node;
	const int n;

	int comb(int a, int b) { return max(a, b); }

	void apply(Node *cur, int len, int val) {
		if (val) {
			(cur->lazy) = val;
			(cur->freq) = val;
		}
	}

	void push_down(Node *cur, int l, int r) {
		if ((cur->left) == nullptr) { (cur->left) = new Node; }
		if ((cur->right) == nullptr) { (cur->right) = new Node; }
		int m = (l + r) / 2;
		apply(cur->left, m - l + 1, cur->lazy);
		apply(cur->right, r - m, cur->lazy);
	}

	void range_set(Node *cur, int l, int r, int ql, int qr, int val) {
		if (qr < l || ql > r) { return; }
        // cout << l << " " << r << " " << ql << " " << qr << " " << val << endl;

		if (ql <= l && r <= qr) {
            // cout << "line 127 reached" << endl;
			apply(cur, r - l + 1, val);
		} else {
			push_down(cur, l, r);
			int m = (l + r) / 2;
			range_set(cur->left, l, m, ql, qr, val);
			range_set(cur->right, m + 1, r, ql, qr, val);
			(cur->freq) = comb((cur->left)->freq, (cur->right)->freq);
		}
        // cout << "line 136: " << l << " " << r << " " << cur->freq << endl;
	}

	int range_sum(Node *cur, int l, int r, int ql, int qr) {
		if (qr < l || ql > r) { return 0; }
        // cout << "line 140: " << l << " " << r << " " << ql << " " << qr << " " << cur->freq << endl;
		if (ql <= l && r <= qr) { return cur->freq; }
		push_down(cur, l, r);
		int m = (l + r) / 2;
		return comb(range_sum(cur->left, l, m, ql, qr),
		            range_sum(cur->right, m + 1, r, ql, qr));
	}

  public:
	SparseSegtree(int n) : n(n) {}

	void range_set(int ql, int qr, int val) { range_set(root, 0, n - 1, ql, qr, val); }

	int range_sum(int ql, int qr) { return range_sum(root, 0, n - 1, ql, qr); }
};

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n), c(n);
        F0R(i, n) cin >> a[i];
        SparseSegtree dp(1e9+5);
        F0R(i, n) cin >> c[i];
        int sum = 0;
        F0R(i, n) {
            sum+=c[i];
            int bruh = dp.range_sum(0, a[i]);
            bruh+=c[i];
            // cout << i << " " << bruh << endl;

            dp.range_set(a[i], a[i], bruh);
        }
        // cout << sum << endl;
        cout << sum-dp.range_sum(0, 1e9+3) << endl;
    }
    return 0;
}