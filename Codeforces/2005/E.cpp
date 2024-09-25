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
        q.pop();
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
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int l,n,m;
        cin >> l >> n >> m;
        vt<int> a(l);
        vt<vt<int>> mat(n, vt<int>(m));
        F0R(i, l) cin >> a[i];
        F0R(i, n) {
            F0R(j, m) cin >> mat[i][j];
        }
        map<int,int> evenMp,oddMp;
        R0F(i, l) {
            if(i%2) oddMp[a[i]]=i;
            else evenMp[a[i]]=i;
        }
        vt<vt<int>> dp0(n, vt<int>(m, inf)), dp1(n, vt<int>(m, inf));
        if(evenMp.count(mat[n-1][m-1])) {
            dp0[n-1][m-1]=evenMp[mat[n-1][m-1]];
        }
        if(oddMp.count(mat[n-1][m-1])) {
            dp1[n-1][m-1]=oddMp[mat[n-1][m-1]];
        }
        R0F(i, n-1) {
            dp0[i][m-1]=dp0[i+1][m-1];
            dp1[i][m-1]=dp1[i+1][m-1];
            if(evenMp.count(mat[i][m-1])) {
                dp0[i][m-1]=min(dp0[i][m-1], evenMp[mat[i][m-1]]);
            }
            if(oddMp.count(mat[i][m-1])) {
                dp1[i][m-1]=min(dp1[i][m-1], oddMp[mat[i][m-1]]);
            }
        }
        R0F(i, m-1) {
            dp0[n-1][i]=dp0[n-1][i+1];
            dp1[n-1][i]=dp1[n-1][i+1];
            if(evenMp.count(mat[n-1][i])) {
                dp0[n-1][i]=min(dp0[n-1][i], evenMp[mat[n-1][i]]);
            }
            if(oddMp.count(mat[n-1][i])) {
                dp1[n-1][i]=min(dp1[n-1][i], oddMp[mat[n-1][i]]);
            }
        }
        R0F(i, n-1) {
            R0F(j, m-1) {
                dp0[i][j]=min(dp0[i+1][j], dp0[i][j+1]);
                dp1[i][j]=min(dp1[i+1][j], dp1[i][j+1]);
                if(evenMp.count(mat[i][j])) {
                    int ind = evenMp[mat[i][j]];
                    if(dp1[i+1][j+1]>ind+1) {
                        dp0[i][j]=min(dp0[i][j], ind);
                    }
                }
                if(oddMp.count(mat[i][j])) {
                    int ind = oddMp[mat[i][j]];
                    if(dp0[i+1][j+1]>ind+1) {
                        dp1[i][j]=min(dp1[i][j], ind);
                    }
                }
            }
        }
        // cout << dp0 << dp1 << endl;
        if(dp0[0][0]==0) cout << "T\n";
        else cout << "N\n";
    }
    return 0;
}
/*
dp0(i,j) = minimum winning even
dp1(i,j) = minimum winning odd

dp0(i,j) = minimum of the following
- dp0(i+1,j)
- dp0(i,j+1)
- if dp1(i+1,j+1)>x+1: it is winning
  otherwise, other player wouldve had winning position earlier
*/