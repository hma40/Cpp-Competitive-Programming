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
// #define endl "\n"
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
struct Node {
    int value;
    Node(int val): value(val){

    };
    Node() {
        value=0;
    }
};
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<Node> tree;
    vt<Node> setLazy;
    vt<Node> addLazy; 
    //CHANGE THESE!
    Node none;
    Node combi(Node &f, Node &s) {
        //ALWAYS COMBINING LEFT TO RIGHT (for non-commutative operations)
        return Node(f.value+s.value);
    }
    Node addRange(Node orig, Node add, int range) {
        return Node(orig.value+add.value*range);
    }
    Node setRange(Node set, int range) {
        return Node(set.value*range);
    }
    Node ad(Node orig, Node ad) {
        //ALWAYS ADDING AD TO ORIG (for non-commutative operations)
        return Node(ad.value+orig.value);
    }
    SegTree(int nn): n(nn) {
        none=Node(inf);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        // cout << beg << end << endl;
    }
    void prop(int i) {
        if(setLazy[i].value!=none.value) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i].value!=none.value) {
            if(setLazy[2*i].value!=none.value) {
                setLazy[2*i]=ad(setLazy[2*i], addLazy[i]);
            } else if(addLazy[2*i].value!=none.value) {
                addLazy[2*i]=ad(addLazy[2*i], addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1].value!=none.value) {
                setLazy[2*i+1]=ad(setLazy[2*i+1], addLazy[i]);
            } else if(addLazy[2*i+1].value!=none.value) {
                addLazy[2*i+1]=ad(addLazy[2*i+1], addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]=addRange(tree[2*i+1], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            tree[2*i]=addRange(tree[2*i], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, Node val) {
        if(i>=n) {
            tree[i]=val;
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void pointSet(int index, Node val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, Node val) {
        if(i>=n) {
            tree[i]=ad(tree[i], val);
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointAdd(2*i, index, val);
        } else {
            pointAdd(2*i+1, index, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void pointAdd(int index, Node val) {
        pointAdd(1, index, val);
    }
    Node rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        Node ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            Node r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans.value==none.value) {
                ans=r;
            } else {
                ans=combi(ans, r);
            }
        }
        return ans;
    }
    Node rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, Node val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, Node val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=setRange(val, end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void rangeAdd(int left, int right, Node val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, Node val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]=addRange(tree[i], val, end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
};
struct TreeAlg {
    int n;
    vt<vt<int>> adj;
    int root;
    vt<int> par;
    vt<int> subSize;
    vt<int> depth;
    TreeAlg(vt<vt<int>> aj, int rt=0) {
        adj=aj;
        root=rt;
        n=aj.size();
        par.resize(n, -1);
        subSize.resize(n, 1);
        depth.resize(n, 0);
        dfs(root);
    }
    void dfs(int node) {
        trav(x, adj[node]) {
            if(x==par[node]) continue;
            par[x]=node;
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
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    TreeAlg t({{1,2},{0},{0,3,4},{2},{2}}, 3);
    cout << t.par << t.depth << endl;
    t.set_sparse(); 
    cout << t.sparse << endl;
    F0R(i, 5) {
        F0R(j, 5) {
            cout << i << " " << j << " " << t.lca(i,j) << endl;
        }
    }
    return 0;
}