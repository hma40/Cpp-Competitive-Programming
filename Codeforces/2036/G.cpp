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
int qleft = 0;
int n;
int query(int l, int r) {
    assert(qleft>0);
    qleft--;
    assert(l<=r&&r<=n);
    cout << "xor " << l << " " << r << endl;
    cout.flush();
    int ans;
    cin >> ans;
    return ans;
}
pair<int,int> findTwo(int beg, int end, int next, int sus) {
    int cur = beg;
    for(; next>=1; next/=2) {
        int nw = min(end, cur+next-1);
        int qu = query(cur, nw);
        if(qu==0) {
            cur+=next;
            continue;
        } else if(qu<sus) {
            continue;
        } else {
            int other = query(cur+next, end);
            return {qu, other};
        }
    }
    return {-1,-1};
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) {
        qleft = 150;
        cin >> n;
        vt<int> ans;
        pair<int,int> special = {-1, -1};
        int sus = 0;
        for(int start = 1; start<=n; start*=2) {
            int end = min(start*2-1, n);
            int qu = query(start, end);
            if(qu<start&&qu!=0) {
                special={start, end};
            } else if(qu!=0) {
                ans.add(qu);
                sus = start;
            }
        }
        if(ans.size()==1&&special.first==-1) {
            int cur = sus;
            vt<int> realAns;
            for(int i = sus/2; i>=1; i/=2) {
                int nw = min(n, cur+i-1);
                int qu = query(cur, nw);
                if(qu==ans[0]) {
                    continue;
                } else if(qu==0) {
                    cur+=i;
                    continue;
                } else if(qu>=sus) {
                    // realAns.add(qu);
                    auto fuck = findTwo(cur+i, min(n, 2*sus-1), i/2, sus);
                    cout << "ans " << qu << " " << fuck.f << " " << fuck.s << endl;
                    break;
                } else {
                    int ququ = query(cur+i, min(n, 2*sus-1));
                    auto fuck = findTwo(cur, cur+i-1, i/2, sus);
                    cout << "ans " << ququ << " " << fuck.f << " " << fuck.s << endl;
                    break;
                }
            }
            continue;
        }
        if(ans.size()==3) {
            cout << "ans " << ans[0] << " " << ans[1] << " " << ans[2] << endl;
            cout.flush();
            continue; 
        }
        int cur = special.f;
        for(int i = special.f/2; i >= 1; i/=2) {
            int nw = min(n, cur+i-1);
            int qu = query(cur, nw);
            if(qu<special.f) {
                if(qu==0) {
                    cur+=i;
                } 
            } else {
                int other = query(nw+1, min(n, 2*special.f-1));
                cout << "ans " << ans[0] << " " << other << " " << qu << endl;
                cout.flush();
                break;
            }
        }
    }
    return 0;
}
/*
Check ranges
[1, 1]
[2, 3]
[4, 7]
etc.

If you get one where the answer is smaller than 2^k then there are two numbers in there
otherwise you found one


*/