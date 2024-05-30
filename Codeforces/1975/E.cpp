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
/*
1
8 1
0 1 0 0 1 0 1 1
2 1
3 2
4 1
5 3
6 2
7 3
8 4
3
*/
struct SegTree {
    int n;
    int minDepth, maxDepth;
    vt<int> start,end,tree;
    int conv(int depth) {
        // cout << "CONVERTING: ORIG DEPTH " << depth << " NEW INDEX " << depth-minDepth << endl;
        return depth-minDepth;
    }
    SegTree(int mn, int mx): minDepth(mn),maxDepth(mx) {
        //index i -> depth i+minDepth
        n=maxDepth-minDepth+1;
        while((n&(-n))!=n) {
            n++;
        }
        start.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        FOR(i, n, 2*n) {
            start[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            start[i]=start[2*i];
            end[i]=end[2*i+1];
        }
    }
    void set(int i, int pos, int val) {
        // cout << "SET CALLED FOR " << i << " " << pos << " " << val << endl;
        if(i>=n) {
            tree[i]=val;
            return;
        }
        if(start[2*i]<=pos&&end[2*i]>=pos) {
            set(2*i, pos, val);
        } else {
            set(2*i+1, pos, val);
        }
        tree[i]=min(tree[2*i], tree[2*i+1]);
    }
    int getMin(int i, int lo, int hi) {
        if(lo==start[i]&&hi==end[i]) {
            return tree[i];
        }
        int ans = inf;
        if(start[2*i]<=hi&&end[2*i]>=lo) {
            ans=min(ans, getMin(i*2, lo, min(hi, end[2*i])));
        }
        if(start[2*i+1]<=hi&&end[2*i+1]>=lo) {
            ans=min(ans, getMin(i*2+1, max(lo, start[2*i+1]), hi));
        }
        return ans;
    }
};
vt<bool> isBlack;
vt<vt<int>> adj;
vt<int> depth,par;
vt<vt<int>> sparse;
vt<int> sSize;
vt<SegTree> sts;
vt<int> segIndex;
vt<int> cnt;
vt<int> minDepth, maxDepth;
set<pair<int, int>> active;
set<int> repeats;
vt<int> depthCount;
int jump(int x, int am) {
    // cout << "JUMP CALLED " << x << " " << am << endl;
    F0R(i, 20) {
        if(am&(1<<i)) {
            x=sparse[x][i];
        }
    }
    return x;
}
int LCA(int x, int y) {
    if(depth[x]>depth[y]) swap(x,y);
    y=jump(y, depth[y]-depth[x]);
    // cout << "LINE 90 " << x << " " << y << endl;
    if(x==y) return x;
    R0F(i, 20) {
        // cout << i << " " << x << " " << y << " " << sparse[x][i] << " " << sparse[y][i] << endl;
        if(sparse[x][i]!=sparse[y][i]) {
            x=sparse[x][i];
            y=sparse[y][i];
        }
    }
    return sparse[x][0];
}
void reset(int n) {
    repeats.clear();
    depthCount.clear();
    depthCount.resize(n);
    isBlack.clear();
    isBlack.resize(n);
    adj.clear();
    adj.resize(n);
    depth.clear();
    depth.resize(n);
    par.clear();
    par.resize(n);
    sparse.clear();
    sSize.clear();
    sSize.resize(n, 1);
    sts.clear();
    minDepth.clear();
    maxDepth.clear();
    segIndex.clear();
    segIndex.resize(n, -1);
    active.clear();
}
bool allBlack(int start, int endDepth) {
    // cout << minDepth << " " << maxDepth << segIndex << endl;
    int good = 1;
    int si = segIndex[start];
    while(start!=-1&&depth[start]>=endDepth) {
        // cout << start << " " << depth[start] << " " << endDepth << endl;
        // cout << sts[si].minDepth << endl;
        if(sts[si].minDepth>=endDepth) {
            good=sts[si].getMin(1, 0, sts[si].conv(depth[start]));
            start=jump(start, depth[start]-sts[si].minDepth);
        } else {
            // cout << "im actually here " << endl;
            good=sts[si].getMin(1, sts[si].conv(endDepth), sts[si].conv(depth[start]));
            start=jump(start, depth[start]-endDepth);
        }
        if(good==0) {
            return false;
        }
        // cout << "LINE 191 " << start << " " << depth[start] << " " << endDepth << endl;
        start=par[start];
        if(start!=-1) si=segIndex[start];
        // cout << "ABOUT TO EXIT LOOP: " << !(start!=-1&&depth[start]>=endDepth) << endl;
        // cout << start << endl;
        // cout << (start!=-1) << " " << (depth[start]>=endDepth) << endl;
    }
    return good;
}
/*
1
5 1
1 0 1 0 1
1 2
1 3
2 4
2 5
1
*/
bool query(int node) {
    // cout << "LINE 188 " << node << " " << depth[node] << endl;
    if(isBlack[node]) {
        isBlack[node]=false;
        active.erase({depth[node], node});
        sts[segIndex[node]].set(1, sts[segIndex[node]].conv(depth[node]), 0);
        depthCount[depth[node]]--;
        if(depthCount[depth[node]]==1) {
            repeats.erase(depth[node]);
        }
    } else {
        isBlack[node]=true;
        active.insert({depth[node], node});
        sts[segIndex[node]].set(1, sts[segIndex[node]].conv(depth[node]), 1);
        depthCount[depth[node]]++;
        if(depthCount[depth[node]]>1) {
            repeats.insert(depth[node]);
        }
    }
    // cout << depthCount << " " << repeats << endl;
    // cout << "LINE 181 " << active << " " << isBlack << endl;
    // printSts();
    if(active.size()==0) return false;
    if(active.size()==1) return true;
    auto deepest = *active.rbegin();    
    auto shallowest = *active.begin();
    if(repeats.size()==0) { 
        // cout << "LINE 237 " << deepest << " " << shallowest << endl;
        if(!allBlack(deepest.s, shallowest.f)) return false;
        int numNodes = deepest.f-shallowest.f+1;
        if(active.size()!=numNodes) return false;
        return true;
    } else {
        int last = *repeats.rbegin();
        if(depthCount[last]>2) return false;
        auto deeper = *active.lower_bound({last,0});
        auto deeperer = *active.upper_bound(deeper);
        // cout << "LINE 240 " << deeper << " " << deeperer << " " << deepest << " " << shallowest << endl;
        // cout << deep << " " << deepest << " " << l << endl;
        int l = LCA(deeper.s, deeperer.s);
        if(l!=shallowest.s) return false;
        if(!allBlack(deepest.s, shallowest.f)) return false;
        // assert(false);
        if(!allBlack(deeperer.s, shallowest.f)) return false;
        if(!allBlack(deeper.s, shallowest.f)) return false;
        int numNodes = deepest.f+deeper.f-2*shallowest.f+1;
        if(active.size()!=numNodes) return false;
        return true;
    }
}
void ddfs(int node) {
    // cout << node << " " << segIndex[node] << segIndex << minDepth << maxDepth << endl;
    if(segIndex[node]==-1) {
        segIndex[node]=minDepth.size();
        minDepth.add(depth[node]);
        maxDepth.add(depth[node]);
        // cout << node << " " << segIndex << endl;
    }
    maxDepth[segIndex[node]]=max(maxDepth[segIndex[node]], depth[node]);
    int maxChild = -1, childSize=0;
    trav(x, adj[node]) {
        if(x==par[node]) continue;
        if(sSize[x]>childSize) {
            childSize=sSize[x];
            maxChild=x;
        }
    }
    if(maxChild!=-1) {
        segIndex[maxChild]=segIndex[node];
    }
    // cout << node << " " << maxChild << " " << childSize << " " << sSize << endl;
    // cout << node << " " << segIndex[node] << segIndex << minDepth << maxDepth << endl;
    trav(x, adj[node]) {
        if(x!=par[node]) {
            ddfs(x);
        }
    }
}
void HLD() {
    ddfs(0);
    F0R(i, minDepth.size()) {
        sts.add(SegTree(minDepth[i], maxDepth[i]));
    }
}
void setSparse(int n) {
    sparse.resize(n, vt<int>(20, -1));
    F0R(i, n) sparse[i][0]=par[i];
    FOR(i, 1, 20) {
        F0R(j, n) {
            if(sparse[j][i-1]!=-1) {
                sparse[j][i]=sparse[sparse[j][i-1]][i-1];
            }
        }
    }
}
void dfs(int node=0) {
    // cout << "LINE 100 " << node << endl;
    trav(x, adj[node]) {
        if(x!=par[node]) {
            par[x]=node;
            depth[x]=depth[node]+1;
            dfs(x);
            sSize[node]+=sSize[x];
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> start;
        F0R(i, n) {
            int x;
            cin >> x;
            if(x) start.add(i);
        }
        reset(n);
        // cout << "LINE 123 " << endl;
        F0R(i, n-1) {
            int x,y;
            cin >> x >> y;
            // cout << i << " " << x << " " << y << endl;
            adj[x-1].add(y-1);
            adj[y-1].add(x-1);
        }
        par[0]=-1;
        dfs();
        // cout << depth << " " << par << endl;
        // cout << "LINE 130" << endl;
        setSparse(n);
        HLD();
        // printSts();
        trav(x, start) {
            query(x);
        }
        // cout << "DEPTHS: " << depth << endl;
        F0R(i, q) {
            int nd;
            cin >> nd;
            nd--;
            if(query(nd)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}