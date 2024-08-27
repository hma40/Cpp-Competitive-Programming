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
int mex(set<int> &s) {
    F0R(i, s.size()+5) {
        if(s.count(i)==0) {
            return i;
        }
    }
    return 69420;
}
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
        vt<set<int>> v(n);
        vt<int> l(n);
        vt<int> ex(n);
        vt<int> mmex(n);
        F0R(i, n) {
            cin >> l[i];
            F0R(j, l[i]) {
                int x;
                cin >> x;
                v[i].insert(x);
            }
        }
        int sum_l = 0;
        F0R(i, n) sum_l+=l[i];
        F0R(i, n) {
            ex[i]=mex(v[i]);
            v[i].insert(ex[i]);
            mmex[i]=mex(v[i]);
        }
        vt<vt<int>> adj(sum_l+5);
        // vt<int> oneJump(sum_l+5), twoJump(sum_l+5);
        F0R(i, n) {
            adj[ex[i]].add(mmex[i]);
        }
        //dp[i] = min sequences used to get to i, or -1 if impossible
        vt<int> dp(sum_l+5);
        // cout << adj << endl;
        vt<bool> general(sum_l+5);
        F0R(i, sum_l+5) {
            if(adj[i].size()==0) continue;   
            sort(begin(adj[i]), end(adj[i]));
            if(general[i]||adj[i].size()>1) {
                general[i]=true;
                trav(x, adj[i]) {
                    general[x]=true;
                }
            }
            if(adj[i].size()) general[i]=true;
        }
        int max_gen = 0;
        F0R(i, sum_l+5) {
            if(general[i]) max_gen=i;
        }
        vt<int> special(sum_l+5);
        R0F(i, sum_l+5) {
            special[i]=i;
            trav(x, adj[i]) {
                special[i]=max(special[i], x);
                special[i]=max(special[i], special[x]);
            }
        }
        int ans = 0;
        if(sum_l+5>m) {
            F0R(i, m+1) {
                ans+=max(max_gen, special[i]);
            }
        } else {    
            F0R(i, sum_l+5) {
                ans+=max(max_gen, special[i]);
            }
            ans+=(sum_l+5+m)*(m-sum_l-4)/2;
        }
        cout << ans << endl;
    }
    return 0;
}
/*
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556

mex: [0,1,0,1,0]
mmex: [1,2,1,3,1]

*/