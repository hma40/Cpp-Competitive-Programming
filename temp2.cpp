#include <bits/stdc++.h>
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
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct TestCase {
    int n;
    vt<vt<pair<int,int>>> adj;
    int q;
    vt<vt<int>> queries;
};
void print_TC(TestCase tc) {
    cout << tc.n << " " << tc.adj << " " << tc.q << " " << tc.queries << endl;
}
TestCase randTC() {
    TestCase tc;
    tc.n = 3;
    tc.q = 1;
    tc.adj.resize(tc.n);
    FOR(i, 1, tc.n) {
        int par = rnd()%i;
        int xr = rnd()%4;
        tc.adj[par].add({i,xr});
        tc.adj[i].add({par,xr});
    }
    F0R(i, tc.q) {
        if(rand()%2) {
            tc.queries.add({0, (ll)(rnd()%4)});
        } else {
            tc.queries.add({1, (ll)(rnd()%tc.n), (ll)(rnd()%4)});
        }
    }
    return tc;
}
struct WrongSol {
    struct BinaryTrie {
    vt<int> leftChild, rightChild;
    vt<int> last;
    BinaryTrie() {
        leftChild.assign(1,-1);
        rightChild.assign(1,-1);
        last.assign(1,0);
    }  
    int maxXOR(int x, int avoid) {
        // cout << "LINE 63 " << x <<  endl;
        int cur = 0;
        int val = 0;
        if(last[0]==avoid) return 0;
        R0F(i, 31) {
            // cout << i << " " << val << " " << x << endl;
            assert(leftChild[cur]!=-1||rightChild[cur]!=-1);
            if(x&(1<<i)) {
                if(leftChild[cur]!=-1&&last[leftChild[cur]]!=avoid) {
                    cur=leftChild[cur];
                } else {
                    cur=rightChild[cur];
                    val^=(1<<i);
                }
            } else {
                if(rightChild[cur]!=-1&&last[rightChild[cur]]!=avoid) {
                    cur=rightChild[cur];
                    val^=(1<<i);
                } else {
                    cur=leftChild[cur];
                }
            }
        }
        return x^val;
    }
    void insert(int x, int pos) {
        // cout << "LINE 86 " << x << endl;
        int cur = 0;
        if(last[0]==0) last[0]=pos;
        else last[0]=-1;
        R0F(i, 31) {
            if(x&(1<<i)) {
                if(rightChild[cur]==-1) {
                    rightChild[cur]=rightChild.size();
                    rightChild.add(-1);
                    leftChild.add(-1);
                    last.add({});
                }
                cur=rightChild[cur];
            } else {
                if(leftChild[cur]==-1) {
                    // leftChild[cur]=next++;
                    leftChild[cur]=leftChild.size();
                    leftChild.add(-1);
                    rightChild.add(-1);
                    last.add({});
                }
                cur=leftChild[cur];
            }
            if(last[cur]==0) last[cur]=pos;
            else last[cur]=-1;
        }
    }
};
struct TreeAlg {
    int n;
    vt<vt<pair<int,int>>> adj;
    vt<int> xr;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    TreeAlg(vt<vt<pair<int,int>>> aj, int rt) {
        adj=aj;
        root=rt;
        n=aj.size();
        xr.assign(n,0);
        par.resize(n, -1);
        // subSize.resize(n, 1);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        trav(x, adj[node]) {
            if(x.f==par[node]) continue;
            par[x.f]=node;
            depth[x.f]=depth[node]+1;
            xr[x.f]=xr[node]^x.s;
            dfs(x.f);
            // subSize[node]+=subSize[x.f];
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
};
    string solve(TestCase tc) {
        int n = tc.n, q = tc.q;
        auto adj = tc.adj;
        auto queries = tc.queries;
        int od=0, ev=0;
        TreeAlg ta(adj,0);
        string ret;
        F0R(i, n) if(ta.depth[i]%2) od++; else ev++;
        BinaryTrie odd,even;
        F0R(i, n) {
            if(ta.depth[i]%2) {
                odd.insert(ta.xr[i], i);
            } else {
                even.insert(ta.xr[i], i);
            }
        }
        int oddXOR = 0;
        F0R(qq, q) {
            int c = queries[qq][0];
            if(c==0) {
                int y = queries[qq][1];
                oddXOR^=y;
            } else {
                int v,x;
                v = queries[qq][1];
                x = queries[qq][2];
                // cout << v << " " << x << " " << ta.xr[v] << endl;
                if(ta.depth[v]%2) x^=oddXOR;
                int ans = max(even.maxXOR(x^ta.xr[v], v), odd.maxXOR(x^ta.xr[v]^oddXOR, v));
                // cout << ans << " ";
                ret+=to_string(ans)+" ";
            }
        }
        return ret;
    }
};
struct CorrectSol {
    struct BinaryTrie {
    vt<int> leftChild, rightChild;
    vt<set<int>> last;
    BinaryTrie() {
        leftChild.assign(1,-1);
        rightChild.assign(1,-1);
        last.assign(1,{});
    }  
    int maxXOR(int x, int avoid) {
        // cout << "LINE 63 " << x <<  endl;
        int cur = 0;
        int val = 0;
        if(last[0].size()==1&&*(last[0].begin())==avoid) return 0;
        R0F(i, 31) {
            // cout << i << " " << val << " " << x << endl;
            assert(leftChild[cur]!=-1||rightChild[cur]!=-1);
            if(x&(1<<i)) {
                if(leftChild[cur]!=-1&&!(last[leftChild[cur]].size()==1&&(*last[leftChild[cur]].begin())==avoid)) {
                    cur=leftChild[cur];
                } else {
                    cur=rightChild[cur];
                    val^=(1<<i);
                }
            } else {
                if(rightChild[cur]!=-1&&!(last[rightChild[cur]].size()==1&&(*last[rightChild[cur]].begin())==avoid)) {
                    cur=rightChild[cur];
                    val^=(1<<i);
                } else {
                    cur=leftChild[cur];
                }
            }
        }
        return x^val;
    }
    void insert(int x, int pos) {
        // cout << "LINE 86 " << x << endl;
        int cur = 0;
        last[cur].insert(pos);
        R0F(i, 31) {
            if(x&(1<<i)) {
                if(rightChild[cur]==-1) {
                    rightChild[cur]=rightChild.size();
                    rightChild.add(-1);
                    leftChild.add(-1);
                    last.add({});
                }
                cur=rightChild[cur];
                last[cur].insert(pos);
            } else {
                if(leftChild[cur]==-1) {
                    // leftChild[cur]=next++;
                    leftChild[cur]=leftChild.size();
                    leftChild.add(-1);
                    rightChild.add(-1);
                    last.add({});
                }
                cur=leftChild[cur];
                last[cur].insert(pos);
            }
        }
    }
};
struct TreeAlg {
    int n;
    vt<vt<pair<int,int>>> adj;
    vt<int> xr;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    TreeAlg(vt<vt<pair<int,int>>> aj, int rt) {
        adj=aj;
        root=rt;
        n=aj.size();
        xr.assign(n,0);
        par.resize(n, -1);
        // subSize.resize(n, 1);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        trav(x, adj[node]) {
            if(x.f==par[node]) continue;
            par[x.f]=node;
            depth[x.f]=depth[node]+1;
            xr[x.f]=xr[node]^x.s;
            dfs(x.f);
            // subSize[node]+=subSize[x.f];
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
};
    string solve(TestCase tc) {
        int n = tc.n, q = tc.q;
        auto adj = tc.adj;
        auto queries = tc.queries;
        string ret = "";
        int od=0, ev=0;
        TreeAlg ta(adj,0);
        F0R(i, n) if(ta.depth[i]%2) od++; else ev++;
        BinaryTrie odd,even;
        F0R(i, n) {
            if(ta.depth[i]%2) {
                odd.insert(ta.xr[i], i);
            } else {
                even.insert(ta.xr[i], i);
            }
        }
        int oddXOR = 0;
        F0R(qq, q) {
            int c = queries[qq][0];
            if(c==0) {
                int y = queries[qq][1];
                oddXOR^=y;
            } else {
                int v,x;
                v = queries[qq][1];
                x = queries[qq][2];
                // cout << v << " " << x << " " << ta.xr[v] << endl;
                if(ta.depth[v]%2) x^=oddXOR;
                int ans = max(even.maxXOR(x^ta.xr[v], v), odd.maxXOR(x^ta.xr[v]^oddXOR, v));
                ret+=to_string(ans)+" ";
            }
        }
        return ret;
    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        print_TC(tc);
        WrongSol w;
        CorrectSol c;
        string wa = w.solve(tc);
        string cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}