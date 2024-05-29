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
struct BinaryIndexedTree {
    int n;
    vector<int> tree;
    BinaryIndexedTree(int n):n(n) {
        tree.resize(n);
    }
    void change(int index, int amount) {
        while(index<n) {
            tree[index]+=amount;
            index+=index&-index;
        }
    }
    int sum(int index) {
        int s = 0;
        while(index>0) {
            s+=tree[index];
            index-=index&-index;
        }
        return s;
    }
    int sum(int left, int right) {
        return sum(right)-sum(left-1);
    }
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,m,q;
    cin >> n >> m >> q;
    vector<pair<int, int>> hosted(m+1);
    hosted[0].first=1000000000;
    F0R(i, m+1) hosted[i].second=i;
    F0R(i, n) {
        int temp; cin >> temp;
        hosted[temp].first++;
    }   
    vector<int> answers(q);
    vector<pair<int, ll>> queries(q);
    F0R(i, q) {
        queries[i].first=i;
        cin >> queries[i].second;
        queries[i].second-=n;
    }
    sort(begin(queries), end(queries), [](const pair<int, ll> a, const pair<int, ll> b)-> bool{
        return a.second<b.second;
    });
    sort(begin(hosted), end(hosted), [](const pair<int, int> a, const pair<int, int> b)->bool {
        return a.first<b.first;
    });
    long long prev = 1;
    ll count = 1;
    BinaryIndexedTree bit(m+2);
    bit.change(hosted[0].second, 1);
    vector<bool> active(m+1);
    active[hosted[0].second]=true;
    trav(a, queries) {
        while(count<m&&a.second>=prev+count*(hosted[count].first-hosted[count-1].first)) {
            bit.change(hosted[count].second, 1);
            active[hosted[count].second]=true;
            prev+=count*(hosted[count].first-hosted[count-1].first);
            count++;
        }
        ll need = (a.second-prev)%count+1;
        //cout << a.second << " " << prev << " " << count << " " << need << endl;
        int left = 1;
        int right = m;
        while(left+1<right) {
            int mid = (left+right)/2;
            if(bit.sum(mid)<need) {
                left=mid;
            } else {
                right=mid;
            }
        }
        if(bit.sum(left)==need&&active[left]) {
            answers[a.first]=left;
        } else {
            answers[a.first]=right;
        }
    }
    trav(a, answers) cout << a << endl;
    return 0;
}