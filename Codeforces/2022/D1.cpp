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
FastMod fs(mod);
int qLeft = 0;
int query(int x, int y) {
    qLeft--;
    cout << "? " << x+1 << " " << y+1 << endl;
    int ans;
    cin >> ans;
    return ans;
}
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
        if(n==3) {
            if(query(0,1)==query(1,0)) {
                cout << "! 3" << endl;
                continue;
            } else if(query(0,2)==query(2,0)) {
                cout << "! 2" << endl;
                continue;
            } else {
                cout << "! 1" << endl;
                continue;
            }
        } else if(n%2==0) {
            pair<int,int> bad = {0, 1};
            for(int i = 3; i < n; i+=2) {
                if(query(i-1, i)!=query(i, i-1)) {
                    bad={i-1,i};
                    break;
                }
            }
            if(bad.f==0) {
                if(query(0,2)==query(2,0)) {
                    cout << "! 2" << endl;
                    continue;
                } else {
                    cout << "! 1" << endl;
                    continue;
                }
            } else {
                if(query(0, bad.f)==query(bad.f, 0)) {
                    cout << "! " << bad.f+2 << endl;
                } else {
                    cout << "! " << bad.f+1 << endl;
                }
                continue;
            }
        } else {
            int x = query(0,1), y = query(1,2), z = query(2,0);
            if((x+y+z)%2==0) {
                if(query(1,0)==x) {
                    cout << "! 3" << endl;
                } else if(query(2,1)==y) {
                    cout << "! 1" << endl;
                } else {
                    cout << "! 2" << endl;
                }
                continue;
            } 
            pair<int,int> bad = {3,4};
            for(int i = 6; i < n; i+=2) {
                if(query(i,i-1)!=query(i-1,i)) {
                    bad={i-1,i};
                    break;
                }
            }
            if(query(0,bad.f)!=query(bad.f,0)) {
                cout << "! " << bad.f+1 << endl;
            } else {
                cout << "! " << bad.s+1 << endl;
            }
        }
    }
    return 0;
}
/*
NNN: 111
NNK: 100
NKK: 010
KKK: 111
NNI: 110
NKI: 000
KKI: 101
*/