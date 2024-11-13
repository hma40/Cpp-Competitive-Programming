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
struct RMQ {
    vt<vt<int>> minSparse;
    vt<vt<int>> maxSparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        minSparse.resize(v.size(), vt<int>(log, -1));
        maxSparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            minSparse[i][0]=v[i];
            maxSparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                minSparse[j][i]=min(minSparse[j][i-1], minSparse[j+(1<<(i-1))][i-1]);
                maxSparse[j][i]=max(maxSparse[j][i-1], maxSparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        if(lo>hi) return inf;
        int log = lg[hi-lo+1];
        return min(minSparse[lo][log], minSparse[hi-(1<<log)+1][log]);
    }
    int getMax(int lo, int hi) {
        if(lo>hi) return -inf;
        int log = lg[hi-lo+1];
        return max(maxSparse[lo][log], maxSparse[hi-(1<<log)+1][log]);
    }    
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<vt<int>> pref(n, vt<int>(m+1));
        F0R(i, n) {
            F0R(j, m) {
                int x;
                cin >> x;
                pref[i][j+1]=pref[i][j]+x;
            }
        }
        vt<RMQ> r;
        F0R(i, n) {
            r.add(RMQ(pref[i], 20));
        }
        vt<vt<int>> dp(n, vt<int>(m)), dp2(n, vt<int>(m));
        F0R(i, m) {
            int mn = r[0].getMin(0, i);
            dp[0][i]=pref[0][i+1]-mn;
            int mx = r[0].getMax(i+1, m);
            dp2[0][i]=mx-pref[0][i];
        }
        FOR(i, 1, n) {
            F0R(j, m) {
                dp[i-1][j]-=r[i].getMin(0, j);
                dp2[i-1][j]-=r[i].getMin(0, j-1);
            }
            RMQ temp(dp[i-1], 20);
            RMQ temp2(dp2[i-1], 20);
            F0R(j, m) {
                dp[i][j]=max(temp.getMax(0, j-1), temp2.getMax(0, j))+pref[i][j+1];
            }
            F0R(j, m) {
                dp[i-1][j]+=r[i].getMin(0, j);
                dp2[i-1][j]+=r[i].getMin(0, j-1);
                dp[i-1][j]+=r[i].getMax(j+2, m);
                dp2[i-1][j]+=r[i].getMax(j+1, m);
            }
            RMQ temp3(dp[i-1], 20), temp4(dp2[i-1], 20);
            F0R(j, m) {
                dp2[i][j]=max(temp3.getMax(j, m-1), temp4.getMax(j+1, m-1))-pref[i][j];
            }
        }
        int ans = -inf;
        F0R(i, m) {
            ans=max(ans, dp[n-1][i]);
        }
        cout << ans << endl;
    }
    return 0;
}
/*
Let dp[i][j] = most you can earn in days 0...i if last right is j and on day i+1, we will expand to right of j
similarly dp2[i][j] = most in days 0...i if last left is j and on day i+1, we will expand to left of j

dp[i][j] = max(pref[j]+dp[i-1][k]-min(pref[x]) over all x<=k) over all k 
or dp2[i-1][k]+pref[j]-min(pref[x]) over all x<k

dp2[i][j] = max(max(pref[x])-pref[j]+dp[i-1][k]) over all k>=
*/