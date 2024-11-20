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
struct SegTree {
    int n;
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=max(tree[2*pos], tree[2*pos+1]);
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=max(tree[2*pos],tree[2*pos+1]);
        }
    }
    int rangeQuery(int a, int b) {
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
};
vt<int> a;
struct DSU {
    vt<int> par, sz, mx;
    DSU(int n) {
        par.resize(n, -1);
        sz.resize(n, 1);
        F0R(i, n) mx.add(a[i]);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(sz[x]<sz[y]) swap(x,y);
        sz[x]+=sz[y];
        par[y]=x;
        mx[x]=max(mx[x], mx[y]);
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
        int n;
        cin >> n;
        a.assign(n,0);
        F0R(i, n) {
            cin >> a[i];
        }
        DSU d(n);
        set<pair<int,int>> s;
        F0R(i, n) s.insert({a[i], i});
        R0F(i, n) {
            while(s.size()) {
                auto bk = (*s.rbegin());
                if(bk.f<=a[i]) break;
                s.erase(bk);
                cout << bk.s << " " << i << endl;
                d.unite(bk.s, i);  
            }
            s.erase({a[i], i});
        }
        priority_queue<pair<int,int>> pq;
        set<int> active;
        F0R(i, n) active.insert(i);
        F0R(i, n) pq.push({a[i], i});
        while(pq.size()) {
            auto f = pq.top();
            pq.pop();
            if(!active.count(f.s)) continue;
            active.erase(f.s);
            while(active.size()) {
                auto bk = (*active.rbegin());
                if(bk<=f.s) break;
                active.erase(bk);
                // adj[bk].add(f.s);
                cout << bk << " " << f.s << endl;
                d.unite(bk,f.s);
            }
        }
        // cout << adj << endl;
        F0R(i, n) {
            cout << d.mx[d.find(i)] << " ";
        }
        cout << endl;
    }
    return 0;
}