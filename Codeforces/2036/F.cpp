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
FastMod fs(mod);
int i,k;
int rand_num(int l, int r) {
    return rnd()%(r-l+1)+l;
}
// int bruteforce(int x, int bit) {
//     int tot = 0;
//     FOR(i, 1, x+1) {
//         if(i&(1LL<<bit)) tot++;
//     }
//     return tot;
// }
int amount(int x, int bit) {
    int tot = 0;
    for(int b = 62; b >= 0; b--) {
        if(x&(1LL<<b)) {
            /*
            1 equal number only
            - can append 1 to keep it equal
            - can append 0 to make it less, then everything smaller is free
            */
            if(b==bit) {
                continue;
            } else {
                tot+=(1LL<<(b-(b>bit)));
            }
        } else {
            if(b==bit) break;
        }
    }
    if(x&(1LL<<bit)) tot++;
    return tot;
}
int bruteforce(int l, int r) {
    int ans = 0;
    for(int ii = l; ii <= r; ii++) {
        if(ii%(1LL<<i)==k) {

        } else {
            ans^=ii;
        }
    }
    return ans;
}
int query(int x) {
    int ans = 0;
    for(int bit = 62; bit >= 0; bit--) {
        int amt = amount(x, bit);
        if(amt%2) ans=ans^(1LL<<bit);
    }
    // cout << x << " " << "LINE 188 " << ans << endl;
    if(x>=k) {
        int ast = (x-k)/(1LL<<i)*(1LL<<i)+k;
        int last = (ast-k)/(1LL<<i)+1;
        // cout << ast << " " << last << endl;
        if(last%2) {
            F0R(bit, i) {
                if(k&(1LL<<bit)) {
                    ans=ans^(1LL<<bit);
                }
            }
        }
    }
    // cout << "LINE 210 " << ans << endl;
    int newnum = k;
    ROF(bit, i, 63) {
        // cout << newnum << " " << (1LL<<i) << endl;
        if(newnum+(1LL<<bit)<=x) {
            newnum+=(1LL<<bit);
        }
    }
    // cout << newnum << endl;
    newnum>>=i;
    // cout << "LINE 204 " << newnum << endl;
    FOR(bit, i, 63) {
        int amt = amount(newnum, bit-i);
        // cout << bit << " " << amt << endl;
        if(amt%2) ans=ans^(1LL<<bit);
    }
    // cout << "RETURNING " << ans << endl;
    return ans;
}
int xorall(int x) {
    int ans = 0;
    F0R(ix, x+1) {
        ans^=ix;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // cout << amount(1,0) << endl;
    // return 0;
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);


    // while(true) {
    //     int l = rand_num(1, 63);
    //     int r = rand_num(l, 63);
    //     i = rand_num(1,7);
    //     k = rand_num(0, (1LL<<i)-1);
    //     cout << l << " " << r << " " << i << " " << k << endl;
    //     if((query(r)^query(l-1))!=bruteforce(l,r)) {
    //         cout << "WRONG ANSWER" << endl;
    //         cout << l << " " << r << " " << i << " " << k << endl;
    //         cout << bruteforce(l,r) << endl;
    //         return 0;
    //     }
    // }
    int t = 1;
    cin >> t;
    while(t--) {
        int l,r;
        cin >> l >> r >> i >> k;
        cout << (query(r)^query(l-1)) << endl;
        // cout << (bruteforce(1, r)^bruteforce(1, l-1)) << endl;
        // cout << bruteforce(1,l) << " " << xorall(l-1) << endl;
    }
    return 0;
}