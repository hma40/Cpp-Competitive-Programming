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
vt<vt<int>> allFactors;
vt<int> mobius;
void mob(int n) {
    mobius.assign(n+1,-1);
    vt<int> p(n+1, 1);
    mobius[0] = 0, mobius[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (p[i]) {
            for (int j = 2; j*i <= n; j++) {
                // cout << "LINE 142 " << i << " " << j << endl;
                if (j%i) mobius[i*j] = mobius[i]*mobius[j];
                else mobius[i*j] = 0;
                p[i*j] = 0;
            }
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    mob(300001);
    allFactors.resize(300001);
    for(int i = 1; i<300001; i++) {
        if(mobius[i]!=0) {
            for(int j = i; j < 300001; j+=i) {
                allFactors[j].add(i);
            }
        }
    }
    vector<int> count(300001), sumInd(300001);
    int n;
    cin >> n;
    vector<int> heights(n);
    F0R(i, n) cin >> heights[i];
    sort(begin(heights),end(heights));
    int ans = 0;
    F0R(i, n) {
        int cH=0, sH=0;
        trav(x, allFactors[heights[i]]) {
            cH+=mobius[x]*count[x];
            sH+=sumInd[x]*mobius[x];
        }
        // cout << i << " " << cH << " " << sH << endl;
        ans+=cH*(i-1)-sH;
        trav(x, allFactors[heights[i]]) {
            count[x]++;
            sumInd[x]+=i;
        }
    }
    cout << ans << endl;
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    return 0;
}
/*
1 2 3 5 6
count: 2
sumInd: 3
3(count)-sumInd=3
*/