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
FastMod fs(mod);
bool ok(vt<pair<int,int>> &par, vt<int> &color, int fixed, int fir, int sex) {
    int n = par.size();
    bool poss[n][20][20];
    F0R(i, n) {
        F0R(j, 20) {
            F0R(k, 20) poss[i][j][k]=false;
        }
    }
    F0R(i, n) {
        if(i==fixed) {
            poss[fixed][fir][sex]=true;
            continue;
        }
        //first allele always its eye color, second allele can be anything more
        FOR(sec, color[i], 20) {
            if(par[i].f==-1) {
                poss[i][color[i]][sec]=true;
                continue;
            }
            //case 1: inherits eye color from parent 1 and second color from parent 2
            bool firstPos = false, secondPos = false;
            F0R(j, 20) {
                firstPos=firstPos||poss[par[i].f][color[i]][j];
                firstPos=firstPos||poss[par[i].f][j][color[i]];
                secondPos=secondPos||poss[par[i].s][sec][j];
                secondPos=secondPos||poss[par[i].s][j][sec];              
                if(i==2&&sec==2) {
                    // cout << "LINE 177 " << firstPos << " " << secondPos << endl;
                }
            }
            if(firstPos&&secondPos) {
                poss[i][color[i]][sec]=true;
            }
            firstPos=false;
            secondPos=false;
            F0R(j, 20) {
                firstPos=firstPos||poss[par[i].f][sec][j];
                firstPos=firstPos||poss[par[i].f][j][sec];
                secondPos=secondPos||poss[par[i].s][color[i]][j];
                secondPos=secondPos||poss[par[i].s][j][color[i]];                
            }
            if(firstPos&&secondPos) {
                poss[i][color[i]][sec]=true;
            }
        }
    }
    bool good = true;
    F0R(i, n) {
        bool found = false;
        F0R(j, 20) {
            F0R(k, 20) {
                if(poss[i][j][k]) {
                    // if(!found) cout << i << " " << j << " " << k << " " << fixed << " " << fir << " " << sex << endl;
                    found=true;
                }
            }
        }
        good=good&&found;
    }
    return good;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int n;
    cin >> n;
    vt<pair<int,int>> par(n);
    vt<int> color(n);
    F0R(i, n) {
        // cout << "LINE 161 " << i << endl;
        char c;
        cin >> par[i].f >> par[i].s >> c;
        par[i].f--;
        par[i].s--;
        color[i]=c-'a';
    }
    bool poss[n][20][20];
    F0R(i, n) {
        F0R(j, 20) {
            F0R(k, 20) poss[i][j][k]=false;
        }
    }
    F0R(i, n) {
        //first allele always its eye color, second allele can be anything more
        FOR(sec, color[i], 20) {
            if(par[i].f==-1) {
                poss[i][color[i]][sec]=true;
                continue;
            }
            //case 1: inherits eye color from parent 1 and second color from parent 2
            bool firstPos = false, secondPos = false;
            F0R(j, 20) {
                firstPos=firstPos||poss[par[i].f][color[i]][j];
                firstPos=firstPos||poss[par[i].f][j][color[i]];
                secondPos=secondPos||poss[par[i].s][sec][j];
                secondPos=secondPos||poss[par[i].s][j][sec];                
                // if(i==2&&sec==2) cout << j << " " << poss[par[i].f][color[i]][j] << " " << poss[par[i].f][j][color[i]] << " " << firstPos << " " << secondPos << endl;
            }
            if(firstPos&&secondPos) {
                poss[i][color[i]][sec]=true;
            }
            firstPos=false;
            secondPos=false;
            F0R(j, 20) {
                firstPos=firstPos||poss[par[i].f][sec][j];
                firstPos=firstPos||poss[par[i].f][j][sec];
                secondPos=secondPos||poss[par[i].s][color[i]][j];
                secondPos=secondPos||poss[par[i].s][j][color[i]];                
            }
            if(firstPos&&secondPos) {
                poss[i][color[i]][sec]=true;
            }
        }
    }
    bool good = true;
    F0R(i, n) {
        bool found = false;
        F0R(j, 20) {
            F0R(k, 20) {
                if(poss[i][j][k]) {
                    found=true;
                    
                }
            }
        }
        good=good&&found;
    }
    // cout << poss[0][0][2] << " " << poss[1][1][2] << endl;
    if(!good) {
        cout << -1 << endl;
        return 0;
    }
    F0R(i, n) {
        pair<int,int> x = {-1,-1};
        F0R(fir, 20) {
            F0R(sec, 20) {
                if(!poss[i][fir][sec]) continue;
                if(x.f==-1&&ok(par,color,i,fir,sec)) {
                    x = {fir,sec};
                }
            }
        }
        cout << char('a'+x.f) << char('a'+x.s) << endl;
    }
    return 0;
}