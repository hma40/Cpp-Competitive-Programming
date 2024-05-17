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
ll mod = 1000000007;
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
void printArray(vector<int> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
void printArray(vector<ll> &v) {
    F0R(i, v.size()) cout << v[i] << " ";
    cout << endl;
}
vector<int> tour;
vector<vector<int>> changes;
vector<vector<int>> values;
vector<vector<int>> edges;
vector<vector<int>> sparseTable, lcaTable;
vector<int> depth;
vector<int> tour2, first2;
vector<int> tDepth;
vector<int> first;
vector<int> milk;
void dfs(int x, int parent) {
    if(x!=0) depth[x]=depth[parent]+1;
    first[x]=tour.size();
    changes[milk[x]].add(tour.size());
    first2[x]=tour2.size();
    if(edges[x].size()==1&&x!=0) {
        tour2.add(x);
        tDepth.add(depth[x]);
    }
    if(values[milk[x]].size()==0) {
        values[milk[x]].add(1);
    } else {
        values[milk[x]].add(values[milk[x]].back()+1);
    }
    tour.add(x);
    //tDepth.add(depth[x]);
    trav(a, edges[x]) {
        if(a!=parent) {
            tour2.add(x);
            tDepth.add(depth[x]);
            dfs(a, x);
            tour2.add(x);
            tDepth.add(depth[x]);
        }
    }
    if(edges[x].size()==1&&x!=0) {
        tour2.add(x);
        tDepth.add(depth[x]);
    }
    changes[milk[x]].add(tour.size());
    values[milk[x]].add(values[milk[x]].back()-1);
    tour.add(x);
    //tDepth.add(depth[x]);
}
int lca(int a, int b) {
    //cout << a << " " << b << endl;
    a=first2[a];
    b=first2[b];
    if(a>b) swap(a,b);
    b++;
    int len = 31-__builtin_clz(b-a);
    //cout << a << " " << b << " " << len << " 60" << endl;
    if(sparseTable[a][len]<sparseTable[b-(1<<len)][len]) {
        return lcaTable[a][len];
    }   
    return lcaTable[b-(1<<len)][len];
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    changes=vector<vector<int>>(n);
    values=vector<vector<int>>(n);
    edges=vector<vector<int>>(n);
    first=vector<int>(n);
    milk=vector<int>(n);
    first2=vector<int>(n);
    depth=vector<int>(n);
    F0R(i, n) {
        cin >> milk[i];
        milk[i]--;
    }
    F0R(i, n-1) {
        int a,b;
        cin >> a >> b;
        edges[--a].add(--b);
        edges[b].add(a);
    }
    dfs(0, -1);
    //printArray(tour2);
    //printArray(tDepth);
    //printArray(first2);
    //assert(false);
    sparseTable=vector<vector<int>>(tour2.size());
    lcaTable=vector<vector<int>>(tour2.size());
    F0R(i, tour2.size()) {
        sparseTable[i].add(tDepth[i]);
        lcaTable[i].add(tour2[i]);
    }
    for(int i = 1; (1<<i)<=tour2.size(); i++) {
        F0R(j, tour2.size()-(1<<i)+1) {
            if(sparseTable[j][i-1]<sparseTable[j+(1<<(i-1))][i-1]) {
                sparseTable[j].add(sparseTable[j][i-1]);
                lcaTable[j].add(lcaTable[j][i-1]);
            } else {
                sparseTable[j].add(sparseTable[j+(1<<(i-1))][i-1]);
                lcaTable[j].add(lcaTable[j+(1<<(i-1))][i-1]);
            }
        }
    }
    //printArray(tour);
    //trav(a, sparseTable) printArray(a);
    //trav(a, lcaTable) printArray(a);
    //assert(false);
    F0R(i, 5) {
        F0R(j, 5) {
            //cout << i << " " << j << " " << lca(i,j) << endl;
        }
    }
    //assert(false);
    //printArray(first);
    string ans;

    F0R(i, m) {
        int a, b, mType;
        cin >> a >> b >> mType;
        mType--;
        int lc = first[lca(--a,--b)];
        a=first[a];
        b=first[b];
        if(a>b) swap(a,b);
        int ub1 = upper_bound(begin(changes[mType]), end(changes[mType]), a)-begin(changes[mType])-1;
        int ub2 = upper_bound(begin(changes[mType]), end(changes[mType]), b)-begin(changes[mType])-1;
        int ubl = upper_bound(begin(changes[mType]), end(changes[mType]), lc)-begin(changes[mType])-1;
        int t1=0, t2=0, t3=0;
        if(ubl>=0) {
            if(lc==changes[mType][ubl]) {
                ubl--;
            }
            if(ubl>=0) t3=values[mType][ubl];
        }
        if(ub1>=0) t1=values[mType][ub1];
        if(ub2>=0) t2=values[mType][ub2];
        //cout << a << " " << b << " " << lc << " " << ub1 << " " << ub2 << " " << ubl << " " << t1 << " " << t2 << " " << t3 << endl;
        if(t1>t3||t2>t3) {
            ans+="1";
        } else {
            ans+="0";
        }
    }
    cout << ans << endl;
    return 0;
}