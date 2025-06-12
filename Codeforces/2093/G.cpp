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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Trie {
//add (number, position), remove (number, position), find least index with x XOR y >= k
    vt<int> left, right, minInd, par;
    vt<set<int>> lol;
    Trie() {
        left.add(-1);
        right.add(-1);
        minInd.add(inf);
        lol.add(set<int>());
        par.add(-1);
    }
    void add_num(int x, int pos) {
        int ind = 0;
        R0F(i, 31) {
            // cout << i << " " << x << " " << (x&(1<<i)) << endl;
            if(x&(1<<i)) {
                if(right[ind]==-1) {
                    right[ind]=left.size();
                    left.add(-1);
                    right.add(-1);
                    par.add(ind);
                    minInd.add(pos);
                    lol.add(set<int>());
                }
                minInd[ind]=min(minInd[ind], pos);
                ind=right[ind];
            } else {
                if(left[ind]==-1) {
                    left[ind]=left.size();
                    left.add(-1);
                    right.add(-1);
                    par.add(ind);
                    minInd.add(pos);
                    lol.add(set<int>());
                }
                minInd[ind] = min(minInd[ind], pos);
                ind=left[ind];
            }
        }
        lol[ind].insert(pos);
    }
    void remove_num(int x, int pos) {
        int ind = 0;
        R0F(i, 31) {
            if(x&(1<<i)) {
                ind=right[ind];
            } else {
                ind=left[ind];
            }
            // cout << i << " " << x << " " << ind << endl;
        }
        // cout << "LINE 191 " << ind << endl;
        lol[ind].erase(pos);
        if(lol[ind].size()) {
            minInd[ind]=*lol[ind].begin();
        } else {
            minInd[ind]=inf;
        }
        ind=par[ind];
        while(ind!=-1) {
            // cout << ind << endl;
            minInd[ind]=inf;
            if(left[ind]!=-1) minInd[ind]=min(minInd[ind], minInd[left[ind]]);
            if(right[ind]!=-1) minInd[ind]=min(minInd[ind], minInd[right[ind]]);
            ind=par[ind];
        }
    }
    int query(int x, int k) {
        int ans = inf;
        int ind = 0;
        R0F(i, 31) {
            if(k&(1<<i)) {
                if(x&(1<<i)) {
                    if(left[ind]==-1) return ans;
                    ind=left[ind];
                } else {
                    if(right[ind]==-1) return ans;
                    ind=right[ind];
                }
            } else {
                if(x&(1<<i)) {
                    if(left[ind]!=-1) {
                        ans=min(ans, minInd[left[ind]]);
                    } 
                    if(right[ind]==-1) return ans;
                    ind=right[ind];
                } else {
                    if(right[ind]!=-1) ans=min(ans, minInd[right[ind]]);
                    if(left[ind]==-1) return ans;
                    ind=left[ind];
                }
            }
        }
        ans=min(ans, minInd[ind]);
        return ans;
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
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        Trie tr;
        F0R(i, n) tr.add_num(a[i],i);
        int ans = inf;
        F0R(i, n) {
            ans=min(ans, tr.query(a[i], k)-i+1);
            tr.remove_num(a[i],i);
        }
        if(ans>n+5) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}