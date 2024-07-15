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
    vt<int> beg,end;
    vt<int> tree;
    vt<int> addLazy; 
    //CHANGE THESE!
    int none;
    SegTree(int nn): n(nn) {
        none=(inf);
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
                addLazy[2*i]+=addLazy[i];
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(addLazy[2*i+1]!=none) {
                addLazy[2*i+1]+=addLazy[i];
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]+=addLazy[i]*(end[2*i]-beg[2*i]+1);
            tree[2*i]+=addLazy[i]*(end[2*i+1]-beg[2*i+1]+1);
            addLazy[i]=none;
        }
    }
    int rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans+=r;
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val*(end[i]-beg[i]+1);//addRange(tree[i], val, end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=(tree[2*i]+tree[2*i+1]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        if(n==1) {
            if(a[0]==b[0]) cout << "YES" << endl;
            else cout << "NO" << endl;
            continue;
        }
        if(n==2) {
            if(a[0]==b[0]&&a[1]==b[1]) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
            continue;
        }
        auto aa = a;
        auto bb = b;
        sort(begin(aa),end(aa));
        sort(begin(bb),end(bb));
        if(aa!=bb) {
            cout << "NO" << endl;
            continue;
        }
        bool done = false;
        FOR(i, 1, n) {
            if(aa[i]==aa[i-1]) {
                done=true;
            }
        }
        if(done) {
            cout << "YES" << endl;
            continue;
        } 
        SegTree st(n);
        map<int,int> mp;
        F0R(i, n) {
            mp[b[i]]=i;
        }
        int moves = 0;
        F0R(i, n) {
            st.rangeAdd(i,i,i);
        }
        F0R(i, n-2) {
            int pos = mp[a[i]];
            // mp[a[i]].erase(pos);
            int actualPos = st.rangeQuery(pos,pos);
            moves+=actualPos-i;
            st.rangeAdd(0,pos-1,1);
        }
        int pos0 = mp[a[n-2]];
        int pos1 = mp[a[n-1]];
        if(moves%2) {
            if(pos0<pos1) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        } else {
            if(pos0<pos1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}