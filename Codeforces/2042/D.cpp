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
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<array<int,3>> v(n);
        F0R(i, n) cin >> v[i][0] >> v[i][1];
        F0R(i, n) v[i][2] = i;
        vt<int> ans(n);
        min_pq<array<int,3>> pq;
        F0R(i, n) pq.push(v[i]);
        multiset<int> rights;
        while(pq.size()) {
            vt<array<int,3>> here;
            here.add(pq.top());
            pq.pop();
            while(pq.size()&&pq.top()[0]==here[0][0]) {
                here.add(pq.top());
                pq.pop();
            }
            trav(x, here) {
                rights.insert(x[1]);
            }
            trav(x, here) {
                rights.erase(rights.find(x[1]));
                auto lb = rights.lower_bound(x[1]);
                if(lb==rights.end()) {
                    rights.insert(x[1]);
                    continue;
                }
                ans[x[2]]+=(*lb)-x[1];
                rights.insert(x[1]);
            }
            // cout << here << ans << endl;
        }
        multiset<int> lefts;
        priority_queue<array<int,3>> p;
        trav(x, v) {
            p.push({x[1], x[0], x[2]});
        }
        while(p.size()) {
            vt<array<int,3>> here;
            here.add(p.top());
            p.pop();
            while(p.size()&&p.top()[0]==here[0][0]) {
                here.add(p.top());
                p.pop();
            }
            trav(x, here) {
                lefts.insert(x[1]);
            }
            trav(x, here) {
                lefts.erase(lefts.find(x[1]));
                auto lb = lefts.upper_bound(x[1]);
                if(lb==lefts.begin()) {
                    lefts.insert(x[1]);
                    continue;
                }
                --lb;
                ans[x[2]]-=(*lb)-x[1];
                lefts.insert(x[1]);
            }
        }
        // cout << ans << endl;
        trav(x, ans) cout << x << endl;
    }   
    return 0;
}
/*
process all intervals with decreasing order of N
for each interval, query minimum R_j out of everything with R_j>=R_i
*/