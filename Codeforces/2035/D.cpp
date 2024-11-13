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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
bool ls(array<int,3> &a, array<int,3> &b) {
    if(a[1]==b[1]) {
        return a[0]<=b[0];
    }
    if(a[1]>b[1]) {
        int diff = a[1]-b[1];
        if(diff>=35) return false;
        int x = a[0];
        F0R(i, diff) {
            x*=2;
            if(x>b[0]) return false;
        }
        return true;
    } else {
        int diff = b[1]-a[1];
        if(diff>=35) return true;
        int x = b[0];
        F0R(i, diff) {
            x*=2;
            if(x>a[0]) return true;
        }
        return false;
    }
}
ll bexpo(ll b, ll e) {
    ll a = 1;
    while(e) {
        if(e&1) {
            a*=b;
            a%=mod;
        }
        e>>=1;
        b*=b;
        b%=mod;
    }
    return a;
}
FastMod fs(mod);
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
        stack<array<int,3>> s;
        int sum = 0;
        int contrib = 0;
        F0R(i, n) {
            // cout << "LINE 200 " << i << s << endl;
            while(!(a[i]&1)) {
                a[i]/=2;
                contrib++;
            }
            array<int,3> here = {a[i], contrib, contrib};
            // cout << here << endl;
            while(s.size()) {
                array<int,3> hr = {a[i], contrib-s.top()[2]+s.top()[1], contrib};
                // cout << "LINE 209 " << s.top() << " " << hr << " " << ls(s.top(), hr) << endl;
                if(ls(s.top(), hr)) {
                    sum-=s.top()[0]*bexpo(2, s.top()[1]);
                    sum%=mod;
                    sum+=mod;
                    sum+=s.top()[0];
                    sum%=mod;
                    s.pop();
                } else {
                    break;
                }
                //compare top vs top potential of here
            }
            if(s.size()) {
                here[1]=contrib-s.top()[2];
                sum+=here[0]*bexpo(2, here[1]);
                sum%=mod;
                s.push({here});
            } else {
                sum+=here[0]*bexpo(2, here[1]);
                sum%=mod;
                s.push(here);
            }
            cout << sum << " ";
        }
        cout << endl;
    }   
    return 0;
}
/*
1
10
1 6 9 4 7 4 4 10 3 2
*/