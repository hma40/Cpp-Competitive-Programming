#include <bits/stdc++.h>
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
ll mod = 998244353;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<int> l,r;
vt<int> LE,RI;
vt<int> order;
void dfs(int nd) {
    if(LE[nd]!=-1) {
        dfs(LE[nd]);
    } else {
        order.add(l[nd]);
    }
    if(RI[nd]!=-1) {
        dfs(RI[nd]);
    } else {
        order.add(r[nd]);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    // vt<int> l(q),r(q);
    l.resize(q);
    r.resize(q);
    F0R(i, q) cin >> l[i];
    F0R(i, q) cin >> r[i];
    F0R(i, q) {
        l[i]--;
        r[i]--;
    }
    vt<int> par(q, -1), lastSeen(n, -1);
    LE.resize(q, -1);
    RI.resize(q, -1);
    lastSeen[l[0]]=0;
    lastSeen[r[0]]=0;
    FOR(i, 1, q) {
        if(lastSeen[l[i]]!=-1) {
            if(l[lastSeen[l[i]]]==l[i]) {
                LE[lastSeen[l[i]]]=i;
            } else {
                RI[lastSeen[l[i]]]=i;
            }
        } else {
            if(l[lastSeen[r[i]]]==r[i]) {
                LE[lastSeen[r[i]]]=i;
            } else {
                RI[lastSeen[r[i]]]=i;
            }
        }
        lastSeen[l[i]]=lastSeen[r[i]]=i;
    }
    // cout << LE << RI << endl;
    dfs(0);
    // cout << order << endl;
    priority_queue<int> unseen;
    int ans = 1;
    priority_queue<int> spots;
    spots.push(order[0]);
    FOR(i, 1, order.size()) {
        spots.push(max(order[i-1], order[i]));
    }
    spots.push(order.back());
    // cout << spots << endl;
    int places = 0;
    // priority_queue<int> unseen;
    F0R(i, n) {
        if(lastSeen[i]==-1) unseen.push(i);
    }
    while(unseen.size()) {
        int f = unseen.top();
        unseen.pop();
        while(spots.size()&&spots.top()>f) {
            places++;
            spots.pop();
        }
        ans*=places;
        places++;
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}
/*   
5 3 3
4 4 1

5 3 1 4
*/