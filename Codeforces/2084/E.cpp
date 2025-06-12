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
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
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
#define enld "\n"
#define double long double
const ll mod = 1000000007;
ll inf = 1e18;
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> addLazy; 
    vt<int> setLazy;
    //CHANGE THESE!
    int none;
    SegTree(int nn) {
        none=(-6969420);
        n=1;
        while(n<nn) {
            n*=2;
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
        if(setLazy[i]!=none) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setLazy[i];
            tree[2*i+1]=setLazy[i];
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i]!=none) {
            if(setLazy[2*i]!=none) {
                setLazy[2*i]+=addLazy[i];
            } else if(addLazy[2*i]!=none) {
                addLazy[2*i]+=(addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1]!=none) {
                setLazy[2*i+1]+=( addLazy[i]);
            } else if(addLazy[2*i+1]!=none) {
                addLazy[2*i+1]+=(addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]+=addLazy[i];
            tree[2*i]+=addLazy[i];
            addLazy[i]=none;
        }
    }
    void rangeSet(int left, int right, int val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=val*(end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=min(tree[2*i],tree[2*i+1]);
    }
    void rangeAdd(int left, int right, int val) {
        // cout << "RANGE ADDING " << left << " " << right << " " << val << endl;
        if(left>right) return;
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        // cout << i << tree.size() << endl;
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
    int walk(int frees) {
        int cur = 1;
        while(cur<n) {
            prop(cur);
            if(cur*2<n) {
                prop(cur*2);
                prop(cur*2+1);
            }
            if(tree[2*cur+1]<=frees) {
                cur=cur*2+1;
            } else {
                cur=cur*2;
            }
        }
        // cout << frees << " " << cur << " "  << tree << endl;
        return cur-n;
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e) {
    int a = 1;
    while(e) {
        if(e&1) a=a*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return a;
}
vt<int> fact(10005), invfact(10005);
int nck(int n, int k) {
    if(n<k) return 0;
    return fact[n]*invfact[n-k]%mod*invfact[k]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    fact[0]=1;
    FOR(i, 1, 10005) fact[i]=fact[i-1]*i%mod;
    F0R(i, 10005) invfact[i]=bexpo(fact[i], mod-2);
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        // set<int> fixed;
        // F0R(i, n) if(a[i]!=-1) fixed.insert(a[i]);
        int tot_free = n;
        F0R(i, n) if(a[i]!=-1) tot_free--;
        vt<vt<int>> pref(n+2, vt<int>(n+2)); //mex, frees
        vt<vt<int>> times(n+2,vt<int>(n+2));
        // SegTree st(n+1);
        vt<bool> seen(n+1);
        F0R(i, n) if(a[i]!=-1) seen[a[i]]=true;
        F0R(beg, n) {
            // cout << "LINE 246 " << beg << endl;
            int free = 0;
            // st.rangeSet(0, st.n-1, 0);
            vt<bool> contains(n+1);
            // cout << "LINE 249 " << endl;
            // st.rangeAdd(n+1, st.n-1, inf);
            // F0R(i, n+1) st.rangeAdd(i, i, i);
            // set<int> dealWith;
            // cout << "LINE 255 " << st.tree << endl;
            // cout << "LINE 253 " << endl
            int mex = 0;
            int nextAdd = 0;
            int nextFixed = 0;
            FOR(end, beg, n) {
                if(a[end]==-1) {
                    free++;
                    while(seen[nextAdd]||contains[nextAdd]) nextAdd++;
                    contains[nextAdd]=true;
                } else {
                    // st.rangeAdd(a[end]+1, n, -1);
                    // dealWith.insert(a[end]);
                    contains[a[end]]=true;
                }
                while(contains[mex]) mex++;
                int maxPossibleMex = mex;
                while(nextFixed<n&&(!seen[nextFixed]||contains[nextFixed])) nextFixed++;
                // if(fixed.size()) {
                maxPossibleMex = min(maxPossibleMex, nextFixed);
                // }                
                // cout << beg << " " << end << " " << maxPossibleMex << endl;
                pref[0][free]+=tot_free-free;
                pref[maxPossibleMex+1][free]-=tot_free-free;
                times[maxPossibleMex][free]++;
            }
            // cout << beg << pref << endl;
        }
        F0R(free, n+1) {
            FOR(mex, 1, n+1) pref[mex][free]+=pref[mex-1][free];
        }
        // F0R(mex, n+1) {
        //     FOR(free, 1, n+1) pref[mex][free]+=pref[mex][free-1];
        // }
        // cerr << times << endl;
        // cerr << pref << endl;
        int ans = 0;
        ans+=fact[tot_free]*(n)%mod;
        int tot_bef = 0;
        // cout << ans << endl;
        if(seen[0]) tot_bef++;
        FOR(mex, 1, n) {
            // cout << mex << " " << tot_bef << endl;
            if(seen[mex]) {
                F0R(free, n+1) {
                    if(times[mex][free]!=0) {
                        int fill = mex-tot_bef-1;
                        ans+=nck(free, fill+1)*times[mex][free]%mod*mex%mod*fact[tot_free-fill-1]%mod*fact[fill+1]%mod%mod;
                        ans%=mod;
                    }
                }
                tot_bef++;
            } else {
                F0R(free, n+1) {
                    if(pref[mex][free]!=0) {
                        int fill = mex-tot_bef;
                        // cout << fill << " " << tot_free-fill-1 << "LINE 327" << endl;
                        ans+=nck(free, mex-tot_bef)*pref[mex][free]%mod*mex%mod*fact[tot_free-fill-1]%mod*fact[mex-tot_bef]%mod%mod;
                        ans%=mod;
                    }
                }
            }
            // cout << mex << " " << ans << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
/*
2 0 1
0 2 1

*/