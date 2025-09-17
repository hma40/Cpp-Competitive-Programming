#include <bits/stdc++.h>
using namespace std;
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
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
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
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> setLazy;
    vt<int> addLazy; 
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
            tree[2*i]=setLazy[i]*(end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setLazy[i]*(end[2*i+1]-beg[2*i+1]+1);
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
            tree[2*i+1]+=addLazy[i]*(end[2*i]-beg[2*i]+1);
            tree[2*i]+=addLazy[i]*(end[2*i]-beg[2*i]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, int val) {
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
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, int val) {
        if(i>=n) {
            tree[i]+=val;
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointAdd(2*i, index, val);
        } else {
            pointAdd(2*i+1, index, val);
        }
        tree[i]=(tree[2*i]+tree[2*i+1]);
    }
    void pointAdd(int index, int val) {
        pointAdd(1, index, val);
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
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    void rangeAdd(int left, int right, int val) {
        if(left>right) return;
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val*(end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=(tree[2*i]+ tree[2*i+1]);
    }
};
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    vt<int> p2(4e5), ip2(4e5);
    p2[0]=ip2[0]=1;
    FOR(i, 1, 4e5) p2[i]=p2[i-1]*2%mod;
    FOR(i, 1, 4e5) ip2[i]=bexpo(p2[i], mod-2);
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> pref, suff;
        pref.add(a[0]);
        FOR(i, 1, n) if(a[i]>pref.back()) pref.add(a[i]);
        suff.add(a.back());
        R0F(i, n-1) {
            if(a[i]>suff.back()) suff.add(a[i]);
        }
        //dp[i][j] = we got up to i with the first j prefix sums
        /*
        let dp2[i] = number of ways to get up to some index with up to the ith suffix max
        what is the transition for dp2?
        dp2[i]*=2 for some of them
        dp2[i]+=dp2[i-1] for at most one of them
        */
        // cout << dp << dp2 << endl;
        vt<int> pdp(pref.size()+1);
        vt<int> sdp(suff.size()+1);
        pdp[0]=1;
        SegTree st(n+5);
        auto recover = [&](int ind)->void{
            // cout << ind << sdp << endl;
            int bruh = st.rangeQuery(ind,ind);
            if(bruh<0) {
                sdp[ind]*=ip2[-bruh];
                sdp[ind]%=mod;
            } else {
                sdp[ind]*=p2[bruh];
                sdp[ind]%=mod;
            }
            st.pointSet(ind, 0);
        };
        auto recover2 = [&](int ind)->void{
            // cout << ind << sdp << endl;
            int bruh = st.rangeQuery(ind,ind);
            if(bruh<0) {
                pdp[ind]*=ip2[-bruh];
                pdp[ind]%=mod;
            } else {
                pdp[ind]*=p2[bruh];
                pdp[ind]%=mod;
            }
            st.pointSet(ind, 0);
        };
        // return 0;
        int ans = 0;
        int contrib = 0;
        sdp[0]=1;
        vt<int> lol(n);
        R0F(i, n) {
            contrib*=2;
            contrib%=mod;
            if(a[i]==suff.back()) {
                recover(suff.size()-1);
                contrib+=sdp[suff.size()-1];
                lol[i]=sdp[suff.size()-1];
            }
            // cout << i << endl;
            auto lo = lower_bound(begin(suff),end(suff),a[i])-begin(suff);
            // cout << i << " " << lo << endl;
            if(suff[lo]==a[i]) {
                st.rangeAdd(lo+1, sdp.size()-1, 1);

                recover(lo);
                recover(lo+1);
                sdp[lo+1]+=sdp[lo];   
            } else {
                st.rangeAdd(lo+1, sdp.size()-1, 1);
            }
            // return 0;
            // F0R(j, sdp.size()) recover(j);
            // cout << i << " " << sdp << endl;
        }
        // cout << lol << contrib << endl;
        st.rangeSet(0, n, 0);
        F0R(i, n) {
            contrib-=lol[i];
            contrib*=ip2[1];
            contrib%=mod;
            contrib+=mod;
            contrib%=mod;
            // contrib*=2;
            // contrib%=mod;
            if(a[i]==suff.back()) {
                recover2(pref.size()-1);
                ans+=pdp[pref.size()-1]*contrib;
                ans%=mod;
                ans+=pdp[pref.size()-1]*lol[i];
                ans%=mod;
            }
            // cout << i << endl;
            auto lo = lower_bound(begin(pref),end(pref),a[i])-begin(pref);
            // cout << i << " " << lo << endl;
            if(pref[lo]==a[i]) {
                st.rangeAdd(lo+1, pdp.size()-1, 1);

                recover2(lo);
                recover2(lo+1);
                pdp[lo+1]+=pdp[lo];   
            } else {
                st.rangeAdd(lo+1, pdp.size()-1, 1);
            }
            // return 0;
            // F0R(j, sdp.size()) recover(j);
            // cout << i << " " << sdp << endl;
        }
        cout << ans << endl;
    }
    return 0;
}