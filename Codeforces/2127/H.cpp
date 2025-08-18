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
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<vt<int>> adj(n);
        F0R(i, m) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        vt<vt<int>> tadj(n), down(n), up(n);
        vt<int> vis(n), par(n, -1), depth(n, -1);
        vt<pair<int,int>> back;
        auto dfs = [&](auto self, int node)->void{
            // cout << node << endl;
            trav(x, adj[node]) {
                if(x==par[node]) continue;
                if(vis[x]) {
                    if(depth[x]<depth[node]) {
                        down[node].add(x);
                    } else{
                        up[node].add(x);
                    }
                } else {
                    vis[x]=true;
                    tadj[node].add(x);
                    par[x]=node;
                    depth[x]=depth[node]+1;
                    self(self, x);
                }
            }  
        };
        vis[0]=true;
        dfs(dfs,0);
        vt<vt<int>> spec(n);
        // assert(false);
        F0R(i, n) {
            trav(x, down[i]) back.add({x,i});
        }
        int ind = 0;
        // cout << tadj << back << endl;
        trav(x, back) {
            // cout << x << endl;
            for(int i = x.s; i != x.f; i=par[i]) {
                spec[i].add(ind);
            }
            spec[x.f].add(ind);
            ind++;
        }
        // cout << tadj << back << spec << endl;
        //dp[node][mask][deg]
        // vt<vt<vt<int>>> dp(n, vt<vt<int>>(64, vt<int>(3)));
        vt<vt<int>> dp(n, vt<int>(64, -inf)), dp2(n, vt<int>(64, -inf));
        auto dfs2 = [&](auto self, int node)->void{
            // cout << "LINE 214 " << node << endl;
            trav(x, tadj[node]) self(self, x);
            F0R(mask, 64) {
                // cout << mask << " " << node << endl;
                int deg = 0, plus=0;
                bool ok = true;
                // cout << "GOT TO LINE 220" << endl;
                if(mask&32) {
                    deg++;
                    plus++;
                }
                // cout << "GOT TO LINE 224" << endl;
                F0R(i, 5) if((mask&(1<<i))) {
                    if(spec[node].size()<i+1) ok=false;
                    else if(back[spec[node][i]].f==node) deg++;
                    else if(back[spec[node][i]].s==node) {
                        plus++;
                        deg++;
                    }
                }
                // cout << "GOT TO LINE 232" << endl;
                if(!ok || deg>2) continue;
                dp[node][mask]=0;
                // cout << "LINE 224 " << mask << " " << node << endl;
                vt<int> msks;
                trav(x, tadj[node]) {
                    int mm = 0;
                    F0R(i, 5) {
                        if((mask&(1<<i))==0 && spec[node].size()>i) {
                            auto bruh = find(begin(spec[x]), end(spec[x]), spec[node][i]);
                            if(bruh==spec[x].end()) continue;
                            int indd = bruh-spec[x].begin();
                            mm+=1<<indd;
                        }
                    }
                    msks.add(mm);
                }
                // cout << msks << tadj[node] << endl;
                vt<int> another;
                F0R(i, msks.size()) {
                    dp[node][mask]+=dp2[tadj[node][i]][31-msks[i]];
                    another.add(dp2[tadj[node][i]][63-msks[i]]-dp2[tadj[node][i]][31-msks[i]]);
                }
                // cout << "LINE 256" << endl;
                sort(rbegin(another),rend(another));
                int more = min((int)another.size(), 2-deg);
                // cout << more << endl;
                // if(node==2 && mask==0) cout << another << more << endl;
                // cout << "GOT TO LINE 261" << endl;
                
                F0R(i, more) {
                        // cout << i << another << " "  << endl;
                        // cout << another.size() << endl;
                    dp[node][mask]+=another[i];
                }
                // cout << "GOT TO LNIE 262" << endl;
                dp[node][mask]+=plus;
                // cout << "GOT TO LINE 263" << endl;
            }
            F0R(i, 64) {
                dp2[node][i]=dp[node][i];
                F0R(j, 6) if(i&(1<<j)) dp2[node][i]=max(dp2[node][i], dp2[node][i-(1<<j)]);
            }
        };
        dfs2(dfs2, 0);
        int ans = 0;
        F0R(i, 31) F0R(j, 3)ans=max(ans, dp[0][i]);
        cout << ans << endl;
    }
    return 0;
}
/*
tree edges
0 1
1 3
3 2
3 4
4 5
5 6
2: (0,3)
so (0,2) back edge + to par
(2,33): why is it 2 (fine 2 is correct)
3: 
(3,1) (to par)
and 
(3 4) 
*/