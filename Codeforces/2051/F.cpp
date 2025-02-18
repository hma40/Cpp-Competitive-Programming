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
int ans(pair<int,int> a, pair<int,int> b, pair<int,int> c) {
    // cout << a << " " << b << " " << c << endl;
    min_pq<pair<int,int>> pq;
    if(a.f!=-1) pq.push({a.f,1});
    if(a.s!=-1) pq.push({a.s+1,-1});
    if(b.f!=-1) pq.push({b.f,1});
    if(b.s!=-1) pq.push({b.s+1,-1});
    if(c.f!=-1) pq.push({c.f,1});
    if(c.s!=-1) pq.push({c.s+1,-1});
    int active = 0, prev = -1;
    int ret = 0;
    while(pq.size()) {
        if(active>0) {
            ret+=pq.top().f-prev;
        }
        // cout << active << " " <<prev << " " << pq.top() << " " << ret << endl;
        prev=pq.top().f;
        active+=pq.top().s;
        pq.pop();
    }
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m,q;
        cin >> n >> m >> q;
        /*
        After 1 operation
        1 2 3 4 ! 6
        2 3 4 ! 6 1

        After 2 operations
        2 1 3 4 ! 6
        1 3 4 ! 6 2
        2 4 ! 6 1 3

        After 3 operations
        13456
        */
        pair<int,int> fromStart = {-1,-1}, fromMid = {m,m}, fromEnd = {-1,-1};
        F0R(i,q) {
            int x;
            cin >> x;
            //see if we activate fromStart and fromEnd
            if(fromStart.f==-1) {
                if(fromMid.f<=x&&x<=fromMid.s) {
                    fromStart={1,1};
                }
            } else {
                //see if we can extendo to right. 
                if(x>fromStart.s) fromStart.s++;
            }
            if(fromEnd.f==-1) {
                if(fromMid.f<=x&&x<=fromMid.s) {
                    fromEnd={n,n};
                }
            } else {
                if(x<fromEnd.f) fromEnd.f--;
            }
            if(fromMid.f==x&&fromMid.s==x) fromMid={-1,-1};
            if(fromMid.f!=-1) {
            if(fromMid.f>x) fromMid.f--;
            if(fromMid.s<x) fromMid.s++;
            }
            cout << ans(fromStart,fromMid,fromEnd) << " ";
        }
        cout << endl;
    }
    return 0;
}