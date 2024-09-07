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
int none = 0, leafZ = 0, leafO = 0, noLeaf=0;
vt<vt<int>> adj;
int n;
string s;
void dfs(int node, int par) {
    if(adj[node].size()==1&&node!=0) {
        if(s[node]=='0') {
            leafZ++;
        } else if(s[node]=='1') {
            leafO++;
        } else {
            noLeaf++;
        }
    } else if(node!=0) {
        if(s[node]=='?') none++;
    }
    trav(x, adj[node]) {
        if(x!=par) {
            dfs(x,node);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        none=0;
        leafZ=0;
        leafO=0;
        noLeaf=0;
        cin >> n;
        adj.assign(n, vt<int>());
        FOR(i, 1, n) {
            int x,y;
            cin >> x >> y;
            adj[x-1].add(y-1);
            adj[y-1].add(x-1);
        }   
        cin >> s;
        dfs(0,-1);
        // assert(false);
        int score = 0;
        if(s[0]=='?') {
            if(leafZ==0&&leafO==0) {
                if(none%2==0) {
                    score=noLeaf/2;
                } else {
                    score=(noLeaf+1)/2;
                }
            } else {
                score=max(leafZ,leafO)+noLeaf/2;
                if(leafZ==leafO) {
                    if(none%2==0) {
                        score=leafZ+noLeaf/2;
                    } else {
                        score=leafZ+(noLeaf+1)/2;
                    }
                }
            }
        } else {
            if(s[0]=='0') {
                score=leafO+(noLeaf+1)/2;
            } else {
                score=leafZ+(noLeaf+1)/2;
            }
        }
        cout << score << endl;
    }
    return 0;
}
/*
score is -1, 0, 1
01010: score of 0
0101: score of 1
odd length: zero
even length: nonzero
Iris wants to maximize even length
Dora wants to maximize odd length (when duplicates erased)

0?1: two either way
0?0: one or three

Only matters root and leaf - everything else don't matter
Iris wants leaf and root to not match
Dora wants leaf and root to match

If root is already determined: both rush to complete leaves
If root is not determined, but at least one leaf is: iris takes root first, then both rush to finish
If no root and no leaf determined: 
- whoevers colors first takes floor(leaf/2)
- whoever colors second takes floor(leaf/2)
depends on parity of uncolored nonleafs
*/