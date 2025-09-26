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
const ll mod = 998244353;
const ll inf = 1e18;
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
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> b(n+1);
        F0R(i, n) {
            if(i%2) b[i+1]=b[i]+a[i];
            else b[i+1]=b[i]-a[i];
        }
        /*
        lets find sum(max-min) over all subarrays for b
        */
        vt<int> nextLargest(n+1, n+1),nextSmallest(n+1, n+1), prevLargest(n+1,-1), prevSmallest(n+1,-1);
        deque<int> dq;
        FOR(i, 0, n+1) {
            while(dq.size()&&b[dq.back()]>b[i]) {
                nextSmallest[dq.back()]=i;
                dq.pop_back();
            }
            dq.push_back(i);
        }
        dq.clear();
        R0F(i, n+1) {
            while(dq.size()&&b[dq.back()]>=b[i]) {
                prevSmallest[dq.back()]=i;
                dq.pop_back();
            }
            dq.push_back(i);
        }
        dq.clear();
        F0R(i, n+1) {
            while(dq.size()&&b[dq.back()]<b[i]) {
                nextLargest[dq.back()]=i;
                dq.pop_back();
            }
            dq.push_back(i);
        }
        dq.clear();
        R0F(i, n+1) {
            while(dq.size()&&b[dq.back()]<=b[i]) {
                prevLargest[dq.back()]=i;
                dq.pop_back();
            }
            dq.push_back(i);
        }
        F0R(i, n+1) b[i]%=mod;
        // cout << b << endl << nextSmallest << endl << prevSmallest << endl << nextLargest << endl << prevLargest << endl;
        int ans = 0;
        F0R(i, n+1) {
            ans+=(nextLargest[i]-i)*(i-prevLargest[i])%mod*b[i];
            ans%=998244353;
            // cout << i << " " << ans << " " << nextLargest[i] << " " << prevLargest[i] << " " << b[i] << endl;
        }
        F0R(i, n+1) {
            ans-=(nextSmallest[i]-i)*(i-prevSmallest[i])%mod*(b[i]);
                    ans%=998244353;
        }
        ans%=998244353;
        ans+=        998244353;
                ans%=998244353;
        cout << ans << endl;
    }
    return 0;
}
/*
[0,-2,-1,-3,1,-2]

0 is largest of [0], [0,-2], [0,-2,-1], [0,-2,-1,-3]
0 is smallest of [0]
Contribution from 0: 0(4)-0(0)=0

-2 is largest of [-2]
-2 is smallest of [-2], [0,-2], [-2,-1], [0,-2,-1]

Contribution from -2: -2(1)-(-2)(4)=6

-1 is largest of [-1], [-2,-1], [-1,-3], [-2,-1,-3]

-3 is largest of [-3]

1 is largest of 
*/