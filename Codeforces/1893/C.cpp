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
        int m;
        cin >> m;
        vt<array<int,4>> ms(m);
        int sum_n=0, mn=0, mx = 0;
        vt<vt<pair<int,int>>> ele(m);
        F0R(i, m) {
            cin >> ms[i][0] >> ms[i][1] >> ms[i][2];
            sum_n+=ms[i][0];
            mn+=ms[i][1];
            mx+=ms[i][2];
            ele[i].resize(ms[i][0]);
            F0R(j, ms[i][0]) cin >> ele[i][j].f;
            F0R(j, ms[i][0]) cin >> ele[i][j].s;
            F0R(j, ms[i][0]) ms[i][3]+=ele[i][j].s;
        }
        if(mx-mn>sum_n) {
            cout << 0 << endl;
            continue;
        }
        vt<int> maxChosenDiff(mx-mn+2);
        vt<int> minUses(mx-mn+2);
        F0R(i, m) {
            maxChosenDiff[0]+=ms[i][2];
            trav(x, ele[i]) {
                if(x.f>=mn&&x.f<=mx) {
                    maxChosenDiff[x.f-mn]-=ms[i][2];
                    maxChosenDiff[x.f-mn+1]+=ms[i][2];
                    if(ms[i][3]-x.s>=ms[i][1]) {
                        maxChosenDiff[x.f-mn]+=ms[i][3]-x.s;
                        maxChosenDiff[x.f-mn+1]-=ms[i][3]-x.s;
                    } else {
                        maxChosenDiff[x.f-mn]+=ms[i][1];
                        maxChosenDiff[x.f-mn+1]-=ms[i][1];
                        minUses[x.f-mn]+=ms[i][1]-(ms[i][3]-x.s);
                    }
                }
            }
        }
        FOR(i,1, mx-mn+2) maxChosenDiff[i]+=maxChosenDiff[i-1];
        int ans = inf;
        FOR(i, mn, mx+1) {
            int here = minUses[i-mn];
            if(maxChosenDiff[i-mn]<i) here+=i-maxChosenDiff[i-mn];
            ans=min(ans, here);
        }
        cout << ans << endl;
    }
    return 0;
}