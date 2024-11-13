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
// #define endl "\n"
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
int n;
vt<bool> isPrime(20001);
vt<string> a;
bool wins(pair<int,int> start) {
    if(start.f<0||start.s<0||a[start.f][start.s]!='-') return false;
    // cout << "WINS CALLDE FOR " << start << endl;
    int sz = 1;
    while(true) {
        bool fine = true;
        int endX = start.f+sz-1, endY = start.s+sz-1;
        if(endX>=n||endY>=n) break;
        FOR(i, start.f, endX+1) {
            if(a[i][endY]=='X') {
                fine=false;
            }
        }
        FOR(i, start.s, endY+1) {
            if(a[endX][i]=='X') {
                fine=false;
            }
        }
        if(fine) {
            sz++;
        } else {
            break;
        }
    }
    sz--;
    // cout << sz << endl;
    if(isPrime[sz]&&sz!=2) {
        F0R(i, sz) {
            F0R(j, sz) {
                a[i+start.f][j+start.s]='X';
            }
        }
        bool win = true;
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if(a[i][j]=='-'&&a[i-1][j]=='-'&&a[i][j-1]=='-'&&a[i-1][j-1]=='-') {
                    win=false;
                }
            }
        }
        F0R(i, sz) {
            F0R(j, sz) {
                a[i+start.f][j+start.s]='-';
            }
        }
        return win;
    } else if(isPrime[sz-1]) {
        sz--;
        F0R(i, sz) {
            F0R(j, sz) {
                a[i+start.f][j+start.s]='X';
            }
        }
        bool win = true;
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if(a[i][j]=='-'&&a[i-1][j]=='-'&&a[i][j-1]=='-'&&a[i-1][j-1]=='-') {
                    win=false;
                }
            }
        }
        F0R(i, sz) {
            F0R(j, sz) {
                a[i+start.f][j+start.s]='-';
            }
        }
        return win;
    } else {
        return false;
    }
    // cout << "WINNING FOR " << start << endl;
    return true;
}
FastMod fs(mod);
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("in.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> lp, primes;
    int bound = 20000;
    lp.assign(bound+1, 0);
    primes.clear();

    for(int i = 2; i <= bound; i++) {
        if(lp[i]==0) {
            lp[i]=i;
            primes.add(i);
        }
        for(int j = 0;i * primes[j]<=bound; j++) {
            lp[i*primes[j]]=primes[j];
            if(primes[j]==lp[i]) break;
        }
    }
    trav(x, primes) isPrime[x]=true;
    // int n;
    cin >> n;
    a.resize(n);
    // vt<string> a(n);
    F0R(i, n) cin >> a[i];
    int count = 0;
    F0R(i, n) {
        F0R(j, n) {
            if(a[i][j]=='-') count++;
        }
    }
    if(count%2==0) {
        bool win = false;
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if(a[i][j]=='-'&&a[i-1][j]=='-'&&a[i][j-1]=='-'&&a[i-1][j-1]=='-') {
                    win=true;
                }
            }
        }
        // cout << "LINE 266 " << endl;
        if(win) cout << "RUBY" << endl;
        else cout << "DIA" << endl;
        return 0;
    }
    pair<int,int> start = {-1,-1};
    FOR(i, 1, n) {
        FOR(j, 1, n) {
            if(a[i][j]=='-'&&a[i-1][j]=='-'&&a[i][j-1]=='-'&&a[i-1][j-1]=='-') {
                if(start.f==-1) {
                    start={i-1,j-1};
                }
            }
        }
    }
    if(start.f==-1) {
        cout << "RUBY" << endl;
        return 0;
    }
    isPrime[1]=true;
    bool win = false;
    if(wins({start.f, start.s})||wins({start.f+1, start.s})||wins({start.f, start.s+1})||wins({start.f+1, start.s+1})) win=true;
    int st = start.s;
    while(true) {
        if(st<0||a[start.f+1][st]!='-') {
            st++;
            break;
        } else {
            st--;
        }
    }
    if(wins({start.f+1, st})||wins({start.f+1, st+1})) win=true;
    // for(int i = -1; i <= 1; i++) {
    //     for(int j = -1; j <= 1; j++) {
    //         if(wins({start.f+i, start.s+j})) win=true;
    //     }
    // }
    if(win) cout << "RUBY" << endl;
    else cout << "DIA" << endl;
    return 0;
}
/*
12
XXXXXXXXX--X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
-----------X
*/