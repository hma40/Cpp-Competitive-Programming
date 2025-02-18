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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
bool check(vt<vt<int>> &a, vt<pair<int,int>> &adj) {
    int n = a.size();
    if(adj.size()+1!=n) return false;
    vt<vt<int>> adjadj(n);
    trav(x, adj) {
        adjadj[x.f].add(x.s);
        adjadj[x.s].add(x.f);
    }
    vt<vt<int>> mine(n,vt<int>(n));
    F0R(i, n) {
        vt<int> dist(n,inf);
        dist[i]=0;
        queue<int> q;
        q.push(i);
        while(q.size()) {
            auto tp = q.front();
            q.pop();
            trav(x, adjadj[tp]) {
                if(dist[x]!=inf) continue;
                dist[x]=dist[tp]+1;
                q.push(x);
            }
        }
        F0R(j, n) {
            if(dist[j]==inf) assert(false);
            if(dist[j]<=2) {
                mine[i][j]=1;
            } else {
                mine[i][j]=0;
            }
        }
    }
    return mine == a;
}
vt<pair<int,int>> generate(vt<vt<int>> &a, int x, int y) {
    vt<pair<int,int>> ret;
    queue<array<int,3>> q;
    ret.add({0,x});
    ret.add({0,y});
    q.push({x,0,-1});
    q.push({y,0,-1});
    int n = a.size();
    set<int> active;
    active.insert(x);
    active.insert(y);
    active.insert(0);
    FOR(i, 1, n) {
        if(active.count(i)) continue;
        // if(i==x||i==y) continue;
        if(a[i][x]&&a[i][y]&&a[i][0]) {
            ret.add({0,i});
            q.push({i,0,-1});
            active.insert(i);
        }
    }
    while(q.size()) {
        auto tp = q.front();
        q.pop();
        FOR(i, 1, n) {
            if(active.count(i)) continue;
            if(tp[1]==0) {
                if(a[i][tp[0]]&&a[i][0]&&!(a[i][x]&&a[i][y])) {
                    ret.add({tp[0],i});
                    q.push({i, tp[0], 0});
                    active.insert(i);
                }
            } else {
                if(a[i][tp[0]]&&a[i][tp[1]]&&!a[i][tp[2]]) {
                    ret.add({tp[0],i});
                    q.push({i, tp[0], tp[1]});
                    active.insert(i);
                }
            }
        }
    }
    // cout << a << x << " " << y << ret << endl;
    return ret;
}
void solve() {
    // cout << "SOLVE CALLED" << endl;
    int n;
    cin >> n;
    vt<vt<int>> a(n,vt<int>(n));
    F0R(i, n) F0R(j, n) cin >> a[i][j];
    vt<pair<int,int>> s;
    // cout << a << endl;
    FOR(i, 1, n) {
        FOR(j, i+1, n) {
            // cout << i << " " << j << " " << a[i][j] << " " << a[0][i] << " " << a[0][j] << endl;
            if(a[i][j]&&a[0][i]&&a[0][j]) s.add({i,j});
        }
    }
    assert(s.size()!=0);
    // cout << s << endl;
    shuffle(begin(s),end(s),rnd);
    if(s.size()==1) {
        auto x = generate(a,s[0].f,s[0].s);
        trav(xx,x) cout << xx.f+1 << " " << xx.s+1 << endl;
    } else {
        trav(x, s) {
            auto y = generate(a,x.f,x.s);
            if(check(a,y)) {
                trav(xx, y) {
                    cout << xx.f+1 << " " << xx.s+1 << endl;
                }
                return;
            }
        }
        // pair<int,int> p = {-1,-1};
        // F0R(i, s.size()) {
        //     F0R(j, s.size()) {
        //         // cout << i << " " << j << endl;
        //         if(s[i].f!=s[j].s&&s[i].f!=s[j].f&&s[i].s!=s[j].f&&s[i].s!=s[j].s) {
        //             p={i,j};
        //             break;
        //         }
        //     }
        //     // if(p.f!=-1) break;
        // }
        // cout << p << endl;
        // if(p.f!=-1) {
        //     auto x = generate(a,s[p.f].f,s[p.f].s);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     } 
        //     x = generate(a, s[p.s].f, s[p.s].s);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     }
        //     x = generate(a, s[p.f].f, s[p.s].f);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     }
        //     x = generate(a, s[p.f].f, s[p.s].s);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     }
        //     x = generate(a, s[p.f].s, s[p.s].f);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     }
        //     x = generate(a, s[p.f].s, s[p.s].s);
        //     if(check(a,x)) {
        //         trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //         return;
        //     }
        // } else {
        //     F0R(i, s.size()) {
        //         auto x = generate(a, s[i].f, s[i].s);
        //         if(check(a,x)) {
        //             trav(xx, x) cout << xx.f+1 << " " << xx.s+1 << endl;
        //             return;
        //         }
        //     }
        // }
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
        solve();
    }
    return 0;
}