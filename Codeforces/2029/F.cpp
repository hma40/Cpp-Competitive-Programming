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
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(vt<int> s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
void initialize() {
    sd = rnd()%mod;
    pw.add(1);
    F0R(i, 2000050) {
        pw.add(pw.back()*sd%mod);
    }
}
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
struct DSU {
    int n;
    int comps;
    vt<int> par;
    vt<int> sz;
    DSU(int nn) {
        n=nn;
        comps=nn;
        par.resize(nn, -1);
        sz.resize(nn, 1);
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void connect(int i, int j) {
        i=find(i);
        j=find(j);
        if(i==j) return;
        if(sz[i]>sz[j]) swap(i,j);
        sz[j]+=sz[i];
        par[i]=j;
        comps--;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    initialize();
    vector<int> bad = {2,1,2,1,2,1};
    vector<int> bad2 = {1,2,1,2,1,2};
    vt<int> bad3 = {1,2,2,1};
    Hash bd(bad), bd2(bad2), bd3(bad3);

    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        string s;
        cin >> n >> s;
        DSU deez(n);
        F0R(i, n) {
            if(s[i]=='R') {
                deez.connect(i, (i+1)%n);
            }
        }
        // cout << deez.sz << endl;
        vector<int> her;
        F0R(i, n) {
            if(deez.find(i)==i) her.add(deez.sz[deez.find(i)]);
        }
        // cout << her << endl;
        if(n%2==0) {
            if(her.size()==1||her.size()==n-1||her.size()==n) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
            continue;
        }
        int mx = 0, odd = 0;
        bool one = false;
        trav(x, her) {
            if(x==1) one=true;
            mx=max(mx, x);
            if(x%2) odd++;
        }
        if(!one) {
            if(odd==1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
            continue;
        }
        if(mx>2) {
            cout << "NO" << endl;
            continue;
        }
        her.clear();
        deez = DSU(n);
        F0R(i, n) {
            if(s[i]=='B') {
                deez.connect(i, (i+1)%n);
            }
        }
        F0R(i, n) {
            if(deez.find(i)==i) her.add(deez.sz[deez.find(i)]);
        }
        mx=0;
        odd=0;
        one=false;
        trav(x, her) {
            if(x==1) one=true;
            mx=max(mx, x);
            if(x%2) odd++;
        }
        if(!one) {
            if(odd==1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
            continue;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}