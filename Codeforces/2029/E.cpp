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
int nextLargest(int n, int m) {
    /*
    n+2x==0 mod m
    2x==m-n mod m

    */
//    cout << "NEXTLARGEST CALLED " << m << " " << n << endl;
    int diff = -n;
    diff%=m;
    diff+=m;
    diff%=m;
    if(diff%2==0) diff/=2;
    else {
        diff+=m;
        diff/=2;
    }
    // cout << "RETURNING " << n+2*diff << endl;
    return n+2*diff;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> lp(400001);
    vt<int> primes;
    for(int i = 2; i <= 400000; i++) {
        if(lp[i]==0) {
            lp[i]=i;
            primes.add(i);
        }
        for(int j = 0;i * primes[j]<400001; j++) {
            lp[i*primes[j]]=primes[j];
            if(primes[j]==lp[i]) break;
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        set<int> primo;
        F0R(i, n) {
            cin >> a[i];
            if(lp[a[i]]==a[i]) {
                primo.insert(a[i]);
            }
        }
        sort(begin(a),end(a));
        if(primo.size()>1) {
            cout << -1 << endl;
            continue;
        } else if(primo.size()==0) {
            cout << 2 << endl;
            continue;
        } else if(a[0]!=(*primo.begin())) {
            cout << -1 << endl;
            continue;
        }
        bool good = true;
        int pr = (*primo.begin());
        if(pr==2) {
            cout << 2 << endl;
            continue;
        }
        trav(x, a) {
            if(x%pr==0) continue;
            int here = 2*pr;
            if(here>x) {
                good=false;
                break;
            }
            if(x%2==0) {
                continue;
            }
            int temp = x;
            bool gud = false;
            while(temp!=1) {
                int tr = lp[temp];
                int fuck = nextLargest(here, tr);
                if(fuck<=x) {
                    // cout << x << " " << fuck << " " << tr << endl;
                    gud=true;
                    break;
                }
                temp/=tr;
            }
            if(!gud) good=false;
        }
        if(good) cout << pr << endl;
        else cout << -1 << endl;
    }
    return 0;
}
/*
1
5
98 39 19 52 75
*/