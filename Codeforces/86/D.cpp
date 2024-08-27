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
// set<int> s;
// multiset<int> ms;
vt<int> ct(1000001);
int ans = 0;
void ad(int element) {
    ans-=element*ct[element]*ct[element];
    // ans-=element*ms.count(element)*ms.count(element);
    // s.insert(element);
    // ms.insert(element);
    ct[element]++;
    ans+=element*ct[element]*ct[element];
    // ans+=element*ms.count(element)*ms.count(element);
}
void ers(int element) {
    // ans-=element*ms.count(element)*ms.count(element);
    // ms.erase(ms.find(element));
    // ans+=element*ms.count(element)*ms.count(element);
    ans-=element*ct[element]*ct[element];
    ct[element]--;
    ans+=element*ct[element]*ct[element];
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,q;
    cin >> n >> q;
    vt<int> v(n);
    F0R(i, n) cin >> v[i];
    // int sqr = (int)(sqrt(n));
    const int sqr = 450;
    //a query with L=x is in container x/sqr
    vt<vt<vt<int>>> queries(sqr+8);
    F0R(i, q) {
        int l,r;
        cin >> l >> r;
        l--;
        r--;
        // if(l/sqr>=queries.size()) return 0;
        queries[l/sqr].add({r,l,i});
    }
    F0R(i, sqr+8) {
        sort(begin(queries[i]),end(queries[i]));
    }
    vt<int> an(q);
    int l=0, r=-1;//incl, excl
    // int ans = 0;
    F0R(i, sqr) {
        trav(x, queries[i]) {
            while(r<x[0]) {
                r++;
                ad(v[r]);
            }
            while(r>x[0]) {
                ers(v[r]);
                r--;
            }
            while(l<x[1]) {
                ers(v[l]);
                l++;
            }
            while(l>x[1]) {
                l--;
                ad(v[l]);
            }
            // cout << x << ms << ans << endl;
            an[x[2]]=ans;
        }
    }
    // cout << an << endl;
    trav(x, an) cout << x << endl;
    return 0;
}
/*
20 8
1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2
4 15
1 2
2 20
7 7
13 18
7 7
3 19
3 8
*/