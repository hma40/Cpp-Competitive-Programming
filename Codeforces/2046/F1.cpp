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
int lower(set<int> &s, int target) {
    auto lb = s.lower_bound(target);
    if(lb==s.begin()) return -1;
    --lb;
    return *lb;
}
int upper(set<int> &s, int target) {
    if(s.upper_bound(target)==s.end()) return -1;
    return *s.upper_bound(target);
}
set<int> active;
SegTree st(1);
vt<array<int,3>> ops;
vt<array<char,3>> ops2;
set<int> dx,dy,xy;
string s;
void ers(int a, int b, int c) {
    ops.add({a-st.rangeQuery(0,a-1), b-st.rangeQuery(0, b-1), c-st.rangeQuery(0, c-1)});
    ops2.add({s[a], s[b], s[c]});
    st.set(a, 1);
    st.set(b, 1);
    st.set(c, 1);
    active.erase(a);
    active.erase(b);
    active.erase(c);
    int lwa = lower(active, a);
    int upa = upper(active, a);
    int lwb = lower(active, b);
    int upb = upper(active, b);
    int lwc = lower(active, c);
    int upc = upper(active, c);
    // cout << "GOT TO LINE 210 " << endl;
    // cout << lwa << " " << upa << " " << lwb << " " << lwc << " " << upb << " " << upc << endl;
    dx.erase(a);
    dy.erase(a);
    xy.erase(a);
    dx.erase(b);
    dy.erase(b);
    xy.erase(b);
    dx.erase(c);
    dy.erase(c);
    xy.erase(c);
    if(lwa!=-1) {
        dx.erase(lwa);
        dy.erase(lwa);
        xy.erase(lwa);
        if(upa!=-1) {
            if(s[lwa]=='D'&&s[upa]=='X') dx.insert(lwa);
            if(s[lwa]=='D'&&s[upa]=='Y') dy.insert(lwa);
            if(s[lwa]=='X'&&s[upa]=='D') dx.insert(lwa);
            if(s[lwa]=='X'&&s[upa]=='Y') xy.insert(lwa);
            if(s[lwa]=='Y'&&s[upa]=='D') dy.insert(lwa);
            if(s[lwa]=='Y'&&s[upa]=='X') xy.insert(lwa);
        }
    }
    if(lwb!=-1) {
        dx.erase(lwb);
        dy.erase(lwb);
        xy.erase(lwb);
        if(upb!=-1) {
            if(s[lwb]=='D'&&s[upb]=='X') dx.insert(lwb);
            if(s[lwb]=='D'&&s[upb]=='Y') dy.insert(lwb);
            if(s[lwb]=='X'&&s[upb]=='D') dx.insert(lwb);
            if(s[lwb]=='X'&&s[upb]=='Y') xy.insert(lwb);
            if(s[lwb]=='Y'&&s[upb]=='D') dy.insert(lwb);
            if(s[lwb]=='Y'&&s[upb]=='X') xy.insert(lwb);
        }
    }
    if(lwc!=-1) {
        dx.erase(lwc);
        dy.erase(lwc);
        xy.erase(lwc);
        if(upb!=-1) {
            if(s[lwc]=='D'&&s[upc]=='X') dx.insert(lwc);
            if(s[lwc]=='D'&&s[upc]=='Y') dy.insert(lwc);
            if(s[lwc]=='X'&&s[upc]=='D') dx.insert(lwc);
            if(s[lwc]=='X'&&s[upc]=='Y') xy.insert(lwc);
            if(s[lwc]=='Y'&&s[upc]=='D') dy.insert(lwc);
            if(s[lwc]=='Y'&&s[upc]=='X') xy.insert(lwc);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> s;
        int n = s.size();
        bool g = true;
        FOR(i, 1, n) if(s[i]==s[i-1]) g=false;
        if(!g) {
            cout << "NO" << endl;
            continue;
        }
        int xc=0, yc=0, dc=0;
        F0R(i, n) {
            if(s[i]=='X') xc++;
            if(s[i]=='D') dc++;
            if(s[i]=='Y') yc++;
        }
        if(dc!=xc||dc!=yc) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        cout << s << endl;
        st = SegTree(n);
        active.clear();
        F0R(i, n) active.insert(i);
        ops.clear();
        dx.clear();
        dy.clear();
        xy.clear();
        FOR(i, 1, n) {
            if(s[i-1]=='D'&&s[i]=='X') dx.insert(i-1);
            if(s[i-1]=='D'&&s[i]=='Y') dy.insert(i-1);
            if(s[i-1]=='X'&&s[i]=='D') dx.insert(i-1);
            if(s[i-1]=='X'&&s[i]=='Y') xy.insert(i-1);
            if(s[i-1]=='Y'&&s[i]=='D') dy.insert(i-1);
            if(s[i-1]=='Y'&&s[i]=='X') xy.insert(i-1);
        }
        while(active.size()) {
            int fir = *active.begin();
            if(s[fir]=='Y') {
                int sec = *dx.begin();
                int third = upper(active, sec);
                int lwr = lower(active, sec);
                int upr = upper(active, third);
                // cout << sec << " " << third << " " << lwr << " " << upr << endl;
                if(lwr!=-1&&upr!=-1&&s[lwr]==s[upr]) {
                    assert(s[lwr]=='Y');
                    ers(lwr, sec, third);
                } else {
                    ers(fir, sec, third);
                }
            } else if(s[fir]=='D') {
                int sec = *xy.begin();
                int third = upper(active, sec);
                int lwr = lower(active, sec);
                int upr = upper(active, third);
                if(lwr!=-1&&upr!=-1&&s[lwr]==s[upr]) {
                    assert(s[lwr]=='D');
                    ers(lwr, sec, third);
                } else {
                    ers(fir, sec, third);
                }
            } else {
                int sec = *dy.begin();
                int third = upper(active, sec);
                int lwr = lower(active, sec);
                int upr = upper(active, third);
                if(lwr!=-1&&upr!=-1&&s[lwr]==s[upr]) {
                    assert(s[lwr]=='X');
                    ers(lwr, sec, third);
                } else {
                    ers(fir, sec, third);
                }
            }
        }
        reverse(begin(ops),end(ops));
        reverse(begin(ops2),end(ops2));
        F0R(i, n/3) {
            cout << ops2[i][0] << " " << ops[i][0] << " " << ops2[i][1] << " " << ops[i][1] << " " << ops2[i][2] << " " << ops[i][2] << endl;
        }
    }
    return 0;
}