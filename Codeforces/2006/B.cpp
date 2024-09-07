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
int n,w;
vt<int> ans, par, subSize, depth;
vt<vt<int>> chil;

void reset() {
    ans.assign(n, n*w);
    subSize.assign(n, 1);
    chil.assign(n, vt<int>());
    par.assign(n, -1);
    depth.assign(n,0);
}
void dfs(int node=0) {
    // cout << node << endl;
    trav(x, chil[node]) {
        depth[x]=depth[node]+1;
        dfs(x);
        subSize[node]+=subSize[x];
    }
}
vt<vt<int>> sparse;
void set_sparse() {
    sparse.resize(n, vt<int>(20));
    F0R(i, n) sparse[i][0]=par[i];
    FOR(i, 1, 20) {
        F0R(j, n) {
            if(sparse[j][i-1]==-1) sparse[j][i]=-1;
            else sparse[j][i]=sparse[sparse[j][i-1]][i-1];
        }
    }
}
int jump(int x, int steps) {
    R0F(i, 20) {
        if(steps&(1<<i)) {
            x=sparse[x][i];
        }
    }
    return x;
}

int lca(int x, int y) {
    if(depth[x]>depth[y]) swap(x,y);
    y=jump(y, depth[y]-depth[x]);
    if(x==y) return x;
    R0F(i, 20) {
        if(sparse[x][i]!=sparse[y][i]) {
            x=sparse[x][i];
            y=sparse[y][i];
        }
    }
    return par[x];
}
int dist(int x, int y) {
    return depth[x]+depth[y]-2*depth[lca(x,y)];
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n >> w;
        reset();
        FOR(i, 1, n) {
            cin >> par[i];
            par[i]--;
            // cout << chil.size() << par[i] << endl;
            chil[par[i]].add(i);
        }        
        dfs();
        set_sparse();
        vt<int> distToNext(n);
        F0R(i, n) {
            distToNext[i]=dist(i, (i+1)%n);
        }
        int incomp = n;
        vt<int> set(n);
        int pref = 0;
        FOR(i, 1, n) {
            int x,y;
            cin >> x >> y;
            pref+=y;
            x--;
            ans[i]=ans[i-1]-(incomp-2)*y;
            //check [i-1,i]
            distToNext[x-1]--;
            set[x-1]+=y;
            if(distToNext[x-1]==0) {
                ans[i]-=w-pref+set[x-1];
                // cout << "LINE 226" << endl;
                ans[i]+=set[x-1];
                incomp--;
            }
            set[x+subSize[x]-1]+=y;
            distToNext[x+subSize[x]-1]--;
            if(distToNext[x+subSize[x]-1]==0) {
                // cout << "LINE 232" << endl;
                ans[i]-=w-pref+set[x+subSize[x]-1];
                ans[i]+=set[x+subSize[x]-1];
                incomp--;
            }
            // cout << i << " " << incomp << " " << ans << set << distToNext << endl;
        }
        // cout << ans << endl;
        for(int i = 1; i < n; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}