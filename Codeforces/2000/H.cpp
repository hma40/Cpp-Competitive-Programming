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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());\
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> setLazy;
    //CHANGE THESE!
    int none;
    SegTree(int nn): n(nn) {
        none=(6969420420LL);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,none);
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
            // cout << "PROP CALLED FOR " << i << " " << tree[i] << " " << setLazy[i] << endl;
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setLazy[i];
            tree[2*i+1]=setLazy[i];
            setLazy[i]=none;
        }   
        // cout << tree[2*i] << " " << setLazy[2*i] << " " << tree[i] << endl;
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
                ans=max(ans, r);
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int val) {
        // cout << "SETTING " << left << " THROUGH " << right << " TO " << val << endl;
        if(left>right) return;
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        // cout << "RANGESET CALLED FOR " << i << " " << left << " " << right << " " << val << endl;
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=val;
            // cout << "DONE: " << left << " " << right << " " << tree[i] << endl;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }

        tree[i]=max(tree[2*i], tree[2*i+1]);     
        // cout << "DONE2: " << left << " " << right << " " << tree[i] << endl;
    }
    int firstAtLeast(int x) {
        // cout << "FIRSTATLEAST CALLED FOR " << x << " " << n << endl;
        int cur = 1;
        while(cur<n) {
            prop(cur);
            // cout << "LINE 215 " << cur << " " << beg[cur] << " " << end[cur] << " " << tree[2*cur] << " " << tree[2*cur+1] << endl;
            // cout << tree << endl << setLazy << endl;
            if(tree[2*cur]>=x) {
                cur*=2;
            } else {
                cur=2*cur+1;
            }
        }
        return 1+cur-n;
    }
};
set<int> cur;
int MAXA = 2000000;
SegTree st(MAXA+1);
void insert(int ele) {
    auto b = cur.lower_bound(ele);
    b--;
    int aft = *(cur.upper_bound(ele));
    int bef = *b;
    st.rangeSet(ele, ele, 0);
    if(aft!=inf) {
        st.rangeSet(ele+1, aft-1, aft-ele-1);
    } else {
        st.rangeSet(ele+1, MAXA, inf);
    }
    if(bef!=-inf) {
        st.rangeSet(bef+1, ele-1, ele-bef-1);
    } else {
        st.rangeSet(0, ele-1, ele);
    }
    cur.insert(ele);
}
void erase(int ele) {
    auto b = cur.lower_bound(ele);
    b--;
    int aft = *(cur.upper_bound(ele));
    int bef = *b;
    if(bef!=-inf&&aft!=inf) {
        st.rangeSet(bef+1, aft-1, aft-bef-1);
    } else if(bef!=-inf) {
        st.rangeSet(bef+1, MAXA, inf);
    } else if(aft!=inf) {
        st.rangeSet(0, aft-1, aft);
    } else {
        st.rangeSet(0, MAXA, inf);
    }
    cur.erase(ele);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        cur.clear();
        cur.insert(-inf);
        cur.insert(inf);
        st.rangeSet(0, MAXA, inf);
        F0R(i, n) {
            int x;
            cin >> x;
            x--;
            insert(x);
        }
        int q;
        cin >> q;
        while(q--) {
            string s;
            int x;
            cin >> s >> x;
            if(s=="+") insert(x-1);
            if(s=="-") erase(x-1);
            if(s=="?") cout << st.firstAtLeast(x) << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
1
5
3 4 5 6 8
1
? 5

2 2 0 0 0 0 1 0 inf
*/