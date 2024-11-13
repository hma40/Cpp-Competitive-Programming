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
double xx,yy,xxx,yyy, c;
double f(double x, double y) {
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy))+sqrt((x-xxx)*(x-xxx)+(y-yyy)*(y-yyy));
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // assert(false);
    cin >> xx >> yy >> xxx >> yyy >> c;
    pair<double,double> center = {(xx+xxx)/2, (yy+yyy)/2};
    // assert(false);
    // bsearch for smallest x
    double lo = -1e9, hi = center.f;
    vector<double> ans(4);
    while(hi-lo>0.0000001) {
        double mid = (lo+hi)/2;
        //tsearch for y that minimizes the thing
        double lolo = -1e9, hihi = 1e9;
        while(hihi-lolo>0.0000001) {
            double mid0 = (lolo*2+hihi)/3, mid1 = (lolo+hihi*2)/3;
            auto f0 = f(mid,mid0), f1 = f(mid,mid1);
            if(f0<f1) {
                hihi=mid1;
            } else {
                lolo=mid0;
            }
        }
        double func = f(mid,lolo);
        if(func<=c) {
            hi=mid;
        } else {
            lo=mid;
        }
        ans[0]=lo;
    }
    lo=center.f;
    hi=1e9;
    while(hi-lo>0.0000001) {
        double mid = (lo+hi)/2;
        //tsearch for y that minimizes the thing
        double lolo = -1e9, hihi = 1e9;
        while(hihi-lolo>0.0000001) {
            double mid0 = (lolo*2+hihi)/3, mid1 = (lolo+hihi*2)/3;
            auto f0 = f(mid,mid0), f1 = f(mid,mid1);
            if(f0<f1) {
                hihi=mid1;
            } else {
                lolo=mid0;
            }
        }
        double func = f(mid,lolo);
        if(func<=c) {
            lo=mid;
        } else {
            hi=mid;
        }
        ans[2]=hi;
    }
    lo=-1e9;
    hi=center.s;
    while(hi-lo>0.0000001) {
        double mid = (lo+hi)/2;
        //tsearch for y that minimizes the thing
        double lolo = -1e9, hihi = 1e9;
        while(hihi-lolo>0.0000001) {
            double mid0 = (lolo*2+hihi)/3, mid1 = (lolo+hihi*2)/3;
            auto f0 = f(mid0,mid), f1 = f(mid1,mid);
            if(f0<f1) {
                hihi=mid1;
            } else {
                lolo=mid0;
            }
        }
        double func = f(lolo, mid);
        if(func<=c) {
            hi=mid;
        } else {
            lo=mid;
        }
        ans[1]=lo;
    }
    lo=center.s;
    hi=1e9;
    while(hi-lo>0.0000001) {
        double mid = (lo+hi)/2;
        //tsearch for y that minimizes the thing
        double lolo = -1e9, hihi = 1e9;
        while(hihi-lolo>0.0000001) {
            double mid0 = (lolo*2+hihi)/3, mid1 = (lolo+hihi*2)/3;
            auto f0 = f(mid0,mid), f1 = f(mid1,mid);
            if(f0<f1) {
                hihi=mid1;
            } else {
                lolo=mid0;
            }
        }
        double func = f(lolo, mid);
        if(func<=c) {
            lo=mid;
        } else {
            hi=mid;
        }
        ans[3]=hi;
    }
    cout << fixed << setprecision(10) << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << endl;
    return 0;
}