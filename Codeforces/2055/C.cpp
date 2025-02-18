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
const ll mod = 1000000007;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m;
        string s;
        cin >> n >> m >> s;
        vt<vt<int>> a(n,vt<int>(m));
        F0R(i, n) F0R(j, m) cin >> a[i][j];
        vt<pair<int,int>> rowsum(n),colsum(m);
        F0R(i, n) {
            F0R(j, m) {
                rowsum[i].s+=a[i][j];
                colsum[j].s+=a[i][j];
            }
        }
        pair<int,int> cur = {0,0};
        vt<int> rowun(n),colun(m);
        F0R(i, n+m-1) {
            rowun[cur.f]++;
            colun[cur.s]++;
            if(s[i]=='D') cur.f++;
            else cur.s++;
        }
        rowun[n-1]++;
        colun[m-1]++;
        vt<vt<pair<int,int>>> unknown(n,vt<pair<int,int>>(m));
        unknown[0][0]={1,0};
        pair<int,int> sum;
        if(s[0]=='D') {
            sum={1,rowsum[0].s};
            cur={1,0};
        } else {
            sum={1,colsum[0].s};
            cur={0,1};
        }
        rowsum[0].f++;
        colsum[0].f++;
        FOR(i, 1, n+m-2) {
            if(s[i]=='D') {
                unknown[cur.f][cur.s]={sum.f-rowsum[cur.f].f, sum.s-rowsum[cur.f].s};
                // cout << i << cur << " " << unknown[cur.f][cur.s] << endl;
                rowsum[cur.f].f+=unknown[cur.f][cur.s].f;
                rowsum[cur.f].s+=unknown[cur.f][cur.s].s;
                colsum[cur.s].f+=unknown[cur.f][cur.s].f;
                colsum[cur.s].s+=unknown[cur.f][cur.s].s;
                cur.f++;
            } else {
                unknown[cur.f][cur.s]={sum.f-colsum[cur.s].f, sum.s-colsum[cur.s].s};
                // cout << i << " " << cur << unknown[cur.f][cur.s] << endl;
                rowsum[cur.f].f+=unknown[cur.f][cur.s].f;
                rowsum[cur.f].s+=unknown[cur.f][cur.s].s;
                colsum[cur.s].f+=unknown[cur.f][cur.s].f;
                colsum[cur.s].s+=unknown[cur.f][cur.s].s;
                cur.s++;
            }
        }
        pair<int,int> another;
        unknown[n-1][m-1]={sum.f-rowsum[n-1].f, sum.s-rowsum[n-1].s};
        another={sum.f-colsum[m-1].f,sum.s-colsum[m-1].s};
        // cout << another << unknown << endl;
        if(another==unknown[n-1][m-1]) {
            cur={0,0};
            F0R(i, n+m-2) {
                a[cur.f][cur.s]=unknown[cur.f][cur.s].s;
                if(s[i]=='D') cur.f++;
                else cur.s++;
            }
            a[n-1][m-1]=unknown[n-1][m-1].s;
        } else {
            int x = -(unknown[n-1][m-1].s-another.s)/(unknown[n-1][m-1].f-another.f);
            cur={0,0};
            F0R(i, n+m-2) {
                a[cur.f][cur.s]=unknown[cur.f][cur.s].s+unknown[cur.f][cur.s].f*x;
                if(s[i]=='D') cur.f++;
                else cur.s++;
            }
            a[n-1][m-1]=unknown[n-1][m-1].s+unknown[n-1][m-1].f*x;
        }
        F0R(i,n ) {
            F0R(j, m) cout << a[i][j] << " ";
            cout << endl;
        }
    }
    return 0;
}