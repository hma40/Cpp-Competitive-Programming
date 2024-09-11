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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> tree;
    vt<int> max_tree;
    vt<int> beg,end;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        max_tree.resize(2*np);
        beg.resize(2*np);
        end.resize(2*np);
        F0R(i, np) beg[i+np]=end[i+np]=i;
        ROF(i, 1, np) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
            max_tree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
            max_tree[i]=max(max_tree[2*i], max_tree[2*i+1]);
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        max_tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
            max_tree[pos]=max(max_tree[2*pos], max_tree[2*pos+1]);
        }
    }
    int rangeSum(int a, int b) {
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
    int rangeMax(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=max(ans,tree[a++]);
            if(b%2==0) ans=max(ans,tree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
    void modulo(int i, int l, int r, int mod) {
        // cout << "MODULO CALLED " << i << " " << l << " " << r << " " << mod << endl;
        int mx = max_tree[i];
        // cout << mx << endl;
        if(mx<mod) return;
        if(r<beg[i]||end[i]<l) return;
        if(beg[i]==end[i]) {
            tree[i]%=mod;
            max_tree[i]%=mod;
            return;
        }
        // if(beg[2*i]<=r&&end[2*i]>=l) {
        modulo(2*i, l, r, mod);
    // }
    // if(beg[2*i+1]<=r&&end[2*i+1]>=l) {
        modulo(2*i+1, l, r, mod);
        // }
        tree[i]=tree[2*i]+tree[2*i+1];
        max_tree[i]=max(max_tree[2*i], max_tree[2*i+1]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,m;
    cin >> n >> m;
    vt<int> a(n);
    F0R(i, n) cin >> a[i];
    SegTree st(n);
    // cout << st.beg << st.end << endl;
    st.build(a);
    while(m--) {
        int type;
        cin >> type;
        if(type==1) {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            cout << st.rangeSum(l,r) << endl;
        } else if(type==2) {
            int l,r,x;
            cin >> l >> r >> x;
            l--;
            r--;
            st.modulo(1,l,r,x);
        } else {
            int k,x;
            cin >> k >> x;
            k--;
            st.set(k,x);
        }
        // cout << st.tree << endl << st.max_tree << endl;
    }
    return 0;
}