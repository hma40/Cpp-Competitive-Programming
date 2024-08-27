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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<pair<int,int>> setLazy;
    //CHANGE THESE!
    // int none;
    SegTree(int nn): n(nn) {
        // none=(inf);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,{-69420,-69420});
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
        if(setLazy[i].f!=-69420) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            //sum of mx+b from LEFT to RIGHT
            //=b(end-beg+1)+m(beg+end)*(end-beg+1)/2
            tree[2*i]=setLazy[i].s*(end[2*i]-beg[2*i]+1)+setLazy[i].f*(beg[2*i]+end[2*i])*(end[2*i]-beg[2*i]+1)/2;
            // tree[2*i+1]=setLazy[i]*(end[2*i+1]-beg[2*i+1]+1);
            tree[2*i+1]=setLazy[i].s*(end[2*i]-beg[2*i]+1)+setLazy[i].f*(beg[2*i+1]+end[2*i+1])*(end[2*i]-beg[2*i]+1)/2;
            setLazy[i]={-69420,-69420};
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
        int ans = 0;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans+=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            ans+=rangeQuery(2*index+1, max(left, beg[2*index+1]), right);

        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int m, int b) {
        //set LEFT to RIGHT to y=mx+b
        rangeSet(1,left,right,m, b);
    }
    void rangeSet(int i, int left, int right, int m, int b) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]={m,b};
            tree[i]=setLazy[i].s*(end[i]-beg[i]+1)+setLazy[i].f*(beg[i]+end[i])*(end[i]-beg[i]+1)/2;
            // tree[i]=val*end[i]-beg[i]+1;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), m, b);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, m, b);
        }
        tree[i]=tree[2*i]+tree[2*i+1];
    }
};
set<pair<int,int>> harbors;
void addHarbor(SegTree &st, int pos, int val) {
    pair<int,int> bruh = {pos,val};
    auto after = *(harbors.upper_bound(bruh));
    auto bef = harbors.upper_bound(bruh);
    bef--;
    // auto aafter = *after;
    auto bbef = *bef;
    // cout << bruh << *after << *bef << endl;
    //bef.f+1 thru bruh: set to bef.s*(bruh.f-i)
    st.rangeSet(bbef.f+1, pos, -bbef.s, bbef.s*bruh.f);
    //pos+1 thru after.f: set to bruh.s*(after.f-i)
    st.rangeSet(pos+1, after.f, -bruh.s, bruh.s*after.f);
    harbors.insert(bruh);
}   
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,m,q;
    cin >> n >> m >> q;
    SegTree st(n);
    vt<int> pos(m),val(m);
    F0R(i, m) {
        cin >> pos[i];
        pos[i]--;
    }
    F0R(i, m) cin >> val[i];
    int val0 = 0;
    F0R(i, m) {
        if(pos[i]==0) {
            val0=val[i];
            harbors.insert({pos[i], val[i]});
        } 
        if(pos[i]==n-1) {
            harbors.insert({pos[i], val[i]});
        }
    }
    //set 1 through n-1 with val0*(n-1-i)
    st.rangeSet(1, n-1, -val0, val0*n-val0);
    // addHarbor(st, 2,23);
    // F0R(i, st.n) {
    //     st.prop(i);
    // }
    // cout << st.tree;
    F0R(i, m) {
        if(pos[i]!=0&&pos[i]!=n-1) {
            addHarbor(st, pos[i], val[i]);
        }
    }
    while(q--) {
        int t,x,y;
        cin >> t >> x >> y;
        if(t==1) {
            addHarbor(st, x-1, y);
        } else {
            cout << st.rangeQuery(x-1,y-1) << endl;
        }
    }
    return 0;
}
/*
300000 2 3
300000 1
10000000 1
2 1 300000
2 1 299999
2 2 300000
*/