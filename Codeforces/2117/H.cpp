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
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<array<int,4>> tree;//sum, maxPrefix, maxSuffix, maxSum
    vt<int> sum, maxPrefix, maxSuffix, maxSum;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
        for(int i = np; i < 2*np; i++) {
            tree[i][0]=-1;
            tree[i][1]=0;
            tree[i][2]=0;
            tree[i][3]=0;
        }
        for(int i = np-1; i > 0; i--) {
            tree[i][0]=tree[2*i][0]+tree[2*i+1][0];
            tree[i][1]=max(tree[2*i][1], tree[2*i][0]+tree[2*i+1][1]);
            tree[i][2]=max(tree[2*i+1][2], tree[2*i+1][0]+tree[2*i][2]);
            tree[i][3]=max({tree[2*i+1][3], tree[2*i][3], tree[2*i][2]+tree[2*i+1][1]});
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos][0]=x;
        tree[pos][1]=max(x, 0LL);
        tree[pos][2]=max(x, 0LL);
        tree[pos][3]=max(x, 0LL);
        for(pos/=2; pos; pos/=2) {
            int i = pos;
            //CHANGE HERE
            tree[i][0]=tree[2*i][0]+tree[2*i+1][0];
            tree[i][1]=max(tree[2*i][1], tree[2*i][0]+tree[2*i+1][1]);
            tree[i][2]=max(tree[2*i+1][2], tree[2*i+1][0]+tree[2*i][2]);
            tree[i][3]=max({tree[2*i+1][3], tree[2*i][3], tree[2*i][2]+tree[2*i+1][1]});
        }
    }
    int query() {
        return tree[1][3];
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> ans(q);
        set<int> no_ans;
        priority_queue<array<int,3>> pq; //ans, left, right
        vt<set<int>> inv(n);
        vt<int> a;
        F0R(i, n) {
            int x;
            cin >> x;
            inv[x-1].insert(i);
            a.add(x-1);
        }
        vt<vt<array<int,3>>> events(n);//time, set/unset, position
        F0R(i, q) {
            int p,x;
            cin >> p >> x;
            p--;
            x--;
            events[a[p]].add({i, -1, p});
            a[p]=x;
            events[x].add({i, 1, p});
        }
        set<int> active;
        SegTree st(n);
        
        F0R(i, n) {
            trav(x, active) st.set(x, -1);
            active=set<int>();
            trav(x, inv[i]) {
                active.insert(x);
                // cout << i << " SETTING " << x << " TO " << 1 << endl; 
                st.set(x, 1);
            }
            int bef = 0;
            trav(x, events[i]) {
                int ans = st.query();

                // cout << x << endl << ans/2 << " " << bef << " " << x[0]-1 << endl;
                pq.push({ans/2, bef, x[0]-1});
                // cout << "SETTING " << x[2] << " TO " << x[1] << endl;
                st.set(x[2], x[1]);
                if(x[1]==1) active.insert(x[2]);
                else active.erase(x[2]);
                bef=x[0];
            }
            // cout << "LINE 241 " << i << " " << st.query()/2 << " " << bef << " " << q-1 << endl;
            pq.push({st.query()/2, bef, q-1});
        }
        // cout << pq << endl;
        set<int> s;
        F0R(i, q) s.insert(i);
        while(pq.size()) {
            auto tp = pq.top();
            pq.pop();
            for(int i = tp[1]; i<=tp[2]; i++) {
                auto lb = s.lower_bound(i);
                if(lb==s.end()) break;
                if((*lb)>tp[2]) break;
                ans[*lb]=tp[0];
                s.erase(lb);
            }
        }
        F0R(i, q) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
/*
1 2 3 4 5
1 2 4 4 5
4 2 4 4 5
4 4 4 4 5
4 4 4 3 5
4 3 4 3 5
*/