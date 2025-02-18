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
struct DSU {
    vt<int> par, sz;
    vt<set<int>> st;
    vt<map<int,int>> ms;
    int mex;
    vt<bool> active;
    multiset<int> activeComps;
    DSU(int n, int mx) {
        st.resize(n);
        ms.resize(n);
        par.resize(n,-1);
        sz.resize(n,1);
        active.resize(n,false);
        mex=mx;
    }
    int find(int x) {
        if(par[x]==-1) return x;
        return par[x]=find(par[x]);
    }
    void unite(int x, int y) {
        x=find(x);
        y=find(y);
        if(x==y) return;
        if(active[x]) {
            active[x]=false;
            activeComps.erase(activeComps.find(sz[x]));
        }
        if(active[y]) {
            active[y]=false;
            activeComps.erase(activeComps.find(sz[y]));
        }
        if(sz[x]>sz[y]) swap(x,y);
        sz[y]+=sz[x];
        par[x]=y;
        for(auto xx: st[x]) {
            st[y].insert(xx);
        }
        for(auto xx: ms[x]) {
            ms[y][xx.f]+=xx.s;
        }
        if(st[y].size()==mex&&(*st[y].rbegin())==mex-1) {
            active[y]=true;
            activeComps.insert(sz[y]);
        }
    }
    void update(int i, int old, int nw) {
        // cout << "LINE 184 " << i << old << " " << nw << endl;
        i=find(i);
        ms[i][old]--;
        if(ms[i][old]==0) ms[i].erase(old);
        if(!ms[i].count(old)) {
            st[i].erase(old);
            if(active[i]) {
                active[i]=false;
                activeComps.erase(activeComps.find(sz[i]));
            }
        }
        ms[i][nw]++;
        // ms[i].insert(nw);
        if(!st[i].count(nw)) {
            st[i].insert(nw);
            if(st[i].size()==mex&&(*st[i].rbegin())==mex-1) {
                active[i]=true;
                activeComps.insert(sz[i]);
            }
        }
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
        int n,q;
        cin >> n >> q;
        vt<array<int,2>> qu(q);
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        F0R(i, q) {
            cin >> qu[i][0] >> qu[i][1];
            qu[i][0]--;
            a[qu[i][0]]+=qu[i][1];
        }
        vt<DSU> d;
        F0R(i, 18) d.add(DSU(n,1<<i));
        vt<set<int>> active(18);
        F0R(i, 18) {
            F0R(j, n) {
                d[i].st[j].insert(a[j]);
                d[i].ms[j][a[j]]++;
            }
        }
        F0R(i, n) {
            F0R(j, 18) {
                if(a[i]<(1<<j)) {
                    active[j].insert(i);
                    if(active[j].count(i-1)) d[j].unite(i-1,i);
                    if(active[j].count(i+1)) d[j].unite(i,i+1);
                }
            }
        }
        F0R(i, n) {
            if(a[i]==0) {
                int j = d[0].find(i);
                d[0].active[j]=true;
                d[0].activeComps.insert(d[0].sz[j]);
            }
        }
        // cout << d[0].par << endl;
        vt<int> answers(q);
        F0R(i, 18) {
            if(d[i].activeComps.size()==0) continue;
            answers[0]=max(answers[0], *d[i].activeComps.rbegin());
        }
        // cout << answers << endl;
        // return 0;
        reverse(begin(qu),end(qu));
        F0R(i, q-1) {
            // cout << i << endl;
            int old = a[qu[i][0]];
            a[qu[i][0]]-=qu[i][1];
            F0R(j, 18) {
                d[j].update(qu[i][0], old, a[qu[i][0]]);
            }
            F0R(j, 18) {
                // cout << "LINE 256 " << j << endl;
                if(active[j].count(qu[i][0])) continue;
                if(a[qu[i][0]]<(1<<j)) {
                    active[j].insert(qu[i][0]);
                    if(active[j].count(qu[i][0]-1)) d[j].unite(qu[i][0], qu[i][0]-1);
                    if(active[j].count(qu[i][0]+1)) d[j].unite(qu[i][0], qu[i][0]+1);
                } 
            }
            F0R(j, 18) {
                // cout << "LINE 265 " << j << endl;
                // cout << answers << endl;
                if(d[j].activeComps.size()==0) continue;       
                // cout << d[j].activeComps << endl;
                answers[i+1]=max(answers[i+1], *d[j].activeComps.rbegin());
            }
        }
        R0F(i, q) cout << answers[i] << endl;
    }
    return 0;
}
/*
1
5 3
0 0 0 0 0
1 1
5 1
5 1


*/