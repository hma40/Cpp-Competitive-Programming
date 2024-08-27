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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> addLazy; 
    //CHANGE THESE!
    int none;
    SegTree(int nn): n(nn) {
        none=(696969420);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
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
        if(addLazy[i]!=none) {
            if(addLazy[2*i]!=none) {
                addLazy[2*i]+=(addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(addLazy[2*i+1]!=none) {
                addLazy[2*i+1]+=(addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]+=addLazy[i];
            tree[2*i]+=addLazy[i];
            addLazy[i]=none;
        }
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=min(tree[2*i], tree[2*i+1]);
    }
    int get(int node) {
        int i = 1;
        while(i<n) {
            prop(i);
            if(beg[2*i]<=node&&end[2*i]>=node) {
                i*=2;
            } else {
                i=i*2+1;
            }
        }
        return tree[i];
    }
    int lastLeq(int comp, int atMost) {
        int cur = 1;
        if(tree[1]>comp) return -1;
        while(cur<n) {
            prop(cur);
            
            if(tree[2*cur+1]>comp||beg[2*cur+1]>atMost) {
                cur=2*cur;
            } else {
                cur=2*cur+1;
            }
        }
        return cur-n;
    }
};
int n,q;
vt<int> v;
vt<int> par;
vt<int> subSize;
vt<vt<int>> chil;
vt<SegTree> hld;
vt<int> startingPoint;
vt<int> hldGroup;
vt<int> groupCount;
vt<int> depth;
vt<int> dp;
void dfs(int node=0) {
    dp[node]=v[node];
    if(chil[node].size()==0) return;
    trav(x, chil[node]) {
        depth[x]=depth[node]+1;
        dfs(x);
        subSize[node]+=subSize[x];
        if(dp[x]>0) dp[node]+=dp[x];
    }
}
void hlld(int node=0) {
    int bestChild=-1, best=-1;
    if(hldGroup[node]==-1) {
        hldGroup[node]=groupCount.size();
        groupCount.add(1);
    }
    if(chil[node].size()==0) return;
    trav(x, chil[node]) {
        if(best<subSize[x]) {
            best=subSize[x];
            bestChild=x;
        }
    }
    hldGroup[bestChild]=hldGroup[node];
    groupCount[hldGroup[node]]++;
    trav(x, chil[node]) hlld(x);
}
int getDP(int node) {
    int group = hldGroup[node];
    int minDepth = depth[startingPoint[group]];
    return hld[group].get(depth[node]-minDepth);
}
int getFirstLEQ(int node, int comp) {
    //RETURN: last depth to add to
    int cur = node;
    while(cur!=0) {
        int group = hldGroup[cur];
        int temp = hld[group].lastLeq(comp, depth[cur]-depth[startingPoint[group]]);
        if(temp==-1) {
            cur=startingPoint[group];
            if(cur!=0) cur=par[cur];
        } else {
            return temp+depth[startingPoint[group]];
        }
    }
    return 0;
}
void addAll(int node, int endDepth, int amount) {
    int cur = node;
    while(cur!=-1&&depth[cur]>=depth[endDepth]) {
        int group = hldGroup[cur];
        hld[group].rangeAdd(max(0LL, endDepth-depth[startingPoint[group]]), depth[cur]-depth[startingPoint[group]], amount);
        cur=par[startingPoint[group]];
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    cin >> n >> q;
    v.resize(n);
    par.resize(n, -1);
    subSize.resize(n, 1);
    chil.resize(n);
    // startingPoint.resize(n
    hldGroup.resize(n, -1);
    depth.resize(n);
    F0R(i, n) cin >> v[i];
    FOR(i, 1, n) {
        cin >> par[i];
        par[i]--;
        chil[par[i]].add(i);
    }
    hldGroup[0]=0;
    groupCount.add(1);
    dp.resize(n);
    dfs();
    hlld();
    cout << hldGroup << groupCount << endl;
    startingPoint.resize(groupCount.size(), -1);
    F0R(i, n) {
        if(startingPoint[hldGroup[i]]==-1) startingPoint[hldGroup[i]]=i;
    }

    F0R(i, groupCount.size()) {
        hld.add(SegTree(groupCount[i]));
    }
    F0R(i, n) {
        addAll(i, depth[i], dp[i]);
    }
    trav(x, hld) {
        cout << x.tree << endl;
    }
    while(q--) {
        int x,c;
        cin >> x >>c;
        x--;
        int bruh = getFirstLEQ(x, -c);
        addAll(x, bruh, c);
        cout << bruh << endl;
        trav(xx, hld) {
            cout << xx.tree << xx.addLazy << endl;
        }
        cout << getDP(x) << endl;
    }
    return 0;
}
/*
we want to:
- find the index of the first element < something on one of its ancestors
- add some number to everything on a path
*/
/*
8 1
1 -9 1 1 1 1 1 1
1 1 3 2 2 4 5
5 7
*/
