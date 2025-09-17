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
        q.pop_front();
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
const ll mod = 998244353;
ll inf = 1e18;
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree, minTree;
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
        minTree.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        rangeSet(nn, n-1, inf);
        // cout << beg << end << endl;
    }
    void prop(int i) {
        if(setLazy[i]!=none) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setLazy[i];
            minTree[2*i]=setLazy[i];
            minTree[2*i+1]=setLazy[i];
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
            minTree[2*i]+=addLazy[i];
            minTree[2*i+1]+=addLazy[i];
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
                ans=max(ans,r);
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        if(left>right) return -1;
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int val) {
        if(left>right) return;
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=val;
            minTree[i]=val;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=max(tree[2*i],tree[2*i+1]);
        minTree[i]=min(minTree[2*i], minTree[2*i+1]);
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val;
            minTree[i]+=val;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=max(tree[2*i], tree[2*i+1]);
        minTree[i]=min(minTree[2*i], minTree[2*i+1]);
    }
    int walk(int ind, int threshold) {
        if(rangeQuery(ind,ind)>=threshold) return -1;
        int i = 1;
        while(i<n) {
            // cout << threshold << " " << ind << " " << i << " " << beg[i] << " " << end[i] << " " << minTree[i] << " " << tree[i] <<endl;
            prop(i);
            if(beg[i]>ind) {
                //now we only want first good ind
                if(minTree[2*i+1]<threshold) {
                    i=i*2+1;
                } else {
                    i=i*2;
                }
                continue;
            }
            //if ind is in right subtree, go there no matter what
            if(beg[2*i+1]<=ind && end[2*i+1]>=ind) {
                i=i*2+1;
                continue;
            }
            //if ind is in left subtree
            if(minTree[2*i+1]<threshold) {
                i=i*2+1;
            } else {
                i=i*2;
            }
        }
        return i-n;
    }
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> all;
        vt<pair<int,int>> a(n);
        F0R(i, n) cin >> a[i].f >> a[i].s;
        F0R(i, n) {
            all.add(a[i].f);
            all.add(a[i].s);
        }
        sort(begin(all),end(all));
        int nxt = 0;
        map<int,int> mp;
        trav(x, all) {
            if(mp.count(x)) continue;
            mp[x]=nxt++;
        }
        F0R(i, n) {
            a[i].f=mp[a[i].f];
            a[i].s=mp[a[i].s];
        }
        SegTree st(nxt+1);
        F0R(i, n) {
            st.rangeAdd(a[i].f,a[i].s,1);
            // FOR(ii, 1, st.n) st.prop(ii);
            // cout << st.tree << st.minTree << endl;
            // cout << endl << "ANS: " << st.rangeQuery(0,nxt) << endl;
            cout << st.rangeQuery(0,nxt) << " ";
            int bruh = st.rangeQuery(a[i].s,a[i].s);
            int lo = st.walk(a[i].s+1, bruh);
            // cout << endl << "LINE 338: " << bruh << " " << lo << endl;
            st.rangeSet(a[i].s+1,lo,bruh);
                        // FOR(ii, 1, st.n) st.prop(ii);
            // cout << st.tree << st.minTree << endl;
        }
        cout << endl;
    }
    return 0;
}