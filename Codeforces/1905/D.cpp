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
#define endl "\n"
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
struct SegTree {
    int n;
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            a/=2;
            b/=2;
        }
        return ans;
    }
    void rangeAdd(int l, int r, int amt) {
        // cout << "ADDING " << amt << " TO " << l << " " << r << endl;
        add(l,amt);
        add(r+1,-amt);
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> perm(n*2);
        F0R(i,n) cin >> perm[i];
        map<int,int> f,s;
        F0R(i, n) {
            perm[i+n]=perm[i];
        }
        vt<int> firstLater(n),firstEarlier(n);
        vt<int> later(2*n, -1),earlier(2*n, -1);
        deque<int> dq;
        F0R(i, n*2) {
            while(dq.size()&&perm[dq.front()]>perm[i]) {
                later[dq.front()]=i;
                dq.pop_front();
            }
            dq.push_front(i);
        }
        dq.clear();
        R0F(i, 2*n) {
            while(dq.size()&&perm[dq.front()]>perm[i]) {
                earlier[dq.front()]=i;
                dq.pop_front();
            }
            dq.push_front(i);
        }
        // cout << later << earlier << endl;
        F0R(i, 2*n) {
            if(later[i]!=-1) {
                firstLater[perm[i]]=later[i]-i;
            }
            if(earlier[i]!=-1) {
                firstEarlier[perm[i]]=i-earlier[i];
            }
        }
        vt<int> inv(n);
        F0R(i, n) inv[perm[i]]=i;
        // cout << firstLater << firstEarlier << endl;
        SegTree stree(n+2);
        FOR(i, 1, n) {
            int ad = firstEarlier[i]*i;
            int nextInd = inv[i]+firstLater[i];
            if(nextInd>=n) {
                int beg = 0;
                int end = n-inv[i]-1;
                stree.rangeAdd(beg,end,ad);
                beg=n-(nextInd%n);
                end=n-1;
                stree.rangeAdd(beg,end,ad);
            } else {
                int beg = n-nextInd;
                int end = n-inv[i]-1;
                stree.rangeAdd(beg,end,ad);
            }
        }
        int ans = 0;
        F0R(i, n) {
            ans=max(ans, stree.rangeQuery(0,i));
        }
        cout << ans+n << endl;
    }
    return 0;
}
/*
0 3 1 2 0 3 1 2
*/