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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("teleport.in" , "r" , stdin);
    freopen("teleport.out" , "w", stdout);
    // assert(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    F0R(i, n) cin >> a[i].f >> a[i].s;
    sort(begin(a),end(a),[](const auto &x, const auto &y)->bool{
        if(x.s==y.s) return x.f<y.f;
        return x.s<y.s;
    });
    /*
    */
    /*
    for each interval keep track of interval in which teleport > interval
    note distance = abs(L)+abs(R-y)
    want: abs(L)+abs(R-y)<abs(R-L)
    abs(R-y)<something
    R-y<something or y-R<something
    */
    vt<pair<int,int>> goodRange(n);
    F0R(i, n) {
        int something = abs(a[i].s-a[i].f)-abs(a[i].f);
        if(something<0) {
            goodRange[i]={-inf,-inf};
            continue;
        }
        int lb = a[i].s-something;
        int ub = a[i].s+something;
        goodRange[i].f=lb;
        goodRange[i].s=ub;
    }
    // cerr << goodRange << endl;
    /*
    for all tasks using teleporter, we have contrib = abs(L)+abs(R-tp_pos)
    if R-tp_pos>0: contrib = abs(L)+R-tp_pos
    if R-tp_pos<0: contrib = abs(L)+tp_pos-R
    */
    min_pq<array<int,3>> pq;
    F0R(i, n) {
        //keep track of three events: direct->TP, TP switch range, TP->direct
        if(goodRange[i].f==-inf)continue;
        pq.push({goodRange[i].f, i, 1});
        pq.push({a[i].s, i, 2});
        pq.push({goodRange[i].s, i, 3});
    }
    int best = inf;
    int ans = 0;
    F0R(i, n) ans+=abs(a[i].s-a[i].f);
    best=ans;
    // cerr << ans << endl;
    int balance = 0;
    while(pq.size()) {
        int time = pq.top()[0];
        ans+=time*balance;
        // cerr << "LINE 195 " << time << " " << ans << endl;
        while(pq.size()&&pq.top()[0]==time) {
            auto tp = pq.top();
            pq.pop();
            if(tp[2]==1) {
                int ind = tp[1];
                ans-=abs(a[ind].s-a[ind].f);
                ans+=abs(a[ind].f)+a[ind].s-time;
                balance--;
            } else if(tp[2]==2) {
                balance+=2;
            } else {
                balance--;
            }
        }
        best=min(best, ans);
        // cerr << time << " " << ans << " " << balance << endl;
        ans-=time*balance;
    }
    cout << best << endl;
    return 0;
}
/*
2
0 4
-1 1
*/