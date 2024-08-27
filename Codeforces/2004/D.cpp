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
    vt<vt<bool>> adj(6, vt<bool>(6, true));
    adj[0][5]=adj[5][0]=false;
    adj[1][4]=adj[4][1]=false;
    adj[2][3]=adj[3][2]=false;
    // adj[0][0]=adj[0][1]=adj[1][0]=adj[0][2]=adj[2][0]=
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> type(n);
        vt<vt<int>> firstNext(n, vt<int>(6, inf));
        vt<vt<int>> firstPrev(n, vt<int>(6, -inf));
        F0R(i, n) {
            string s;
            cin >> s;
            if(s=="BG") {
                type[i]=0;
            } else if(s=="BR") {
                type[i]=1;
            } else if(s=="BY") {
                type[i]=2;
            } else if(s=="GR") {
                type[i]=3;
            } else if(s=="GY") {
                type[i]=4;
            } else {
                type[i]=5;
            }
        }
        // set<int> bind(6),aind(6);
        vt<int> last(6,-inf);
        F0R(i, n) {
            F0R(j, 6) {
                // if(bind[j].size()==0) continue;
                firstPrev[i][j]=last[j];
            }
            last[type[i]]=i;
        }
        last.assign(6, inf);
        R0F(i, n) {
            F0R(j, 6) {
                firstNext[i][j]=last[j];
            }
            last[type[i]]=i;
        }
        // cout << firstPrev << firstNext << endl;
        
        while(q--) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            if(adj[type[x]][type[y]]) {
                cout << abs(y-x) << endl;
            } else {
                int ans = inf;
                F0R(i, 6) {
                    if(adj[type[x]][i]&&adj[i][type[y]]) {
                        ans=min(ans, abs(x-firstPrev[x][i])+abs(y-firstPrev[x][i]));
                        ans=min(ans, abs(firstNext[x][i]-x)+abs(firstNext[x][i]-y));
                    }
                }
                if(ans>=1e6) {
                    cout << -1 << endl;
                } else {
                    cout << ans << endl;
                }
            }
        }
    }
    return 0;
}
/*
if two cities are connected,obviously use that
otherwise, 
*/