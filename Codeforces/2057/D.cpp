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
const ll mod = 1000000007;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> tree;
    vt<int> mxPlus, mnPlus, mxMinus, minusMn;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        mxPlus.resize(2*np, -inf);
        mnPlus.resize(2*np, inf);
        mxMinus.resize(2*np, -inf);
        minusMn.resize(2*np, -inf);
        n=np;
    }
    void set(int pos, int x) {
        pos+=n;
        mxPlus[pos]=x+pos;
        mnPlus[pos]=x+pos;
        mxMinus[pos]=x-pos;
        minusMn[pos]=pos-x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=max(tree[2*pos],tree[2*pos+1]);
            mxPlus[pos]=max(mxPlus[2*pos], mxPlus[2*pos+1]);
            mnPlus[pos]=min(mnPlus[2*pos], mnPlus[2*pos+1]);
            mxMinus[pos]=max(mxMinus[2*pos], mxMinus[2*pos+1]);
            minusMn[pos]=max(minusMn[2*pos], minusMn[2*pos+1]);
            tree[pos]=max(tree[pos], mxPlus[2*pos]-mnPlus[2*pos+1]);
            tree[pos]=max(tree[pos], mxMinus[2*pos+1]+minusMn[2*pos]);
        }
    }
    int query() {
        return tree[1];
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        SegTree st(n);
        F0R(i, n) {
            int x;
            cin >> x;
            st.set(i, x);
        }
        // cout << st.tree << endl;
        cout << st.query() << endl;
        while(q--) {
            int i,x;
            cin >> i >> x;
            i--;
            st.set(i,x);
            cout << st.query() << endl;
        }
        // cout << st.query() << endl;
    }
    return 0;
}
/*
segment tree with max ans, max, min in nodes
- when merging two of them, we either take answer from one of the nodes, or we go in between the nodes. 
- if max and min are in same part of the two segments it should be covered
- otherwise, if max>mid and min<mid then ans=chmax(max-min-maxPos+minPos)
- if max<mid and min>mid then ans=chmax(max-min-minPos+maxPos)
*/