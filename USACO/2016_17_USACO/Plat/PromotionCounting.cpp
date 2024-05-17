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
struct BIT2D {
    int n;
    vector<ll> tree;
    BIT2D(int n): n(n+5),tree(n+5){};
    void update(int idx, int val) {
        idx++;
        while(idx<n) {
            tree[idx]+=val;
            idx+=idx&-idx;
        }
    }
    ll sum(int idx) {
        idx++;
        ll s = 0;
        while(idx) {
            s+=tree[idx];
            idx-=idx&-idx;
        }
        return s;
    }
    ll sum(int l, int r) {
        return sum(r)-sum(l-1);
    }
};
vector<vector<int>> edges;
vector<int> tPos;
vector<int> tour;
vector<int> subtreeSize;
void dfs(int x, int par) {
    tour.add(x);
    tPos[x]=tour.size()-1;
    subtreeSize[x]=1;
    trav(y, edges[x]) {
        if(y!=par) {
            dfs(y,x);
            subtreeSize[x]+=subtreeSize[y];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> skill(n);
    vector<pair<int, int>> skill2(n);
    F0R(i, n) cin >> skill[i];
    F0R(i, n) skill2[i]={i, skill[i]};
    sort(begin(skill2), end(skill2), [](const pair<int, int> a, const pair<int, int> b)-> bool{
        return a.second<b.second;
    });
    F0R(i, n) skill[skill2[i].f]=i+1;
    //printArray(skill);
    edges=vector<vector<int>>(n);
    //tour=vector<int>(n);
    tPos=vector<int>(n);
    subtreeSize=vector<int>(n);
    FOR(i, 1, n) {
        int x;
        cin >> x;
        edges[--x].add(i);
        edges[i].add(x);
    }
    dfs(0,-1);
    //printArray(tour);
    //printArray(subtreeSize);
    //printArray(tPos);
    vector<ll> ans(n);
    BIT2D b(n);
    R0F(i, n) {
        int cowNum = skill2[i].first;
        ans[cowNum]=b.sum(tPos[cowNum], tPos[cowNum]+subtreeSize[cowNum]-1);
        b.update(tPos[cowNum], 1);
    }
    F0R(i, n) cout << ans[i] << endl;
    return 0;
}