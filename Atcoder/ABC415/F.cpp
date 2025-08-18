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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
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
        // addLazy.resize(2*n,none);
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
            tree[2*i+1]=setLazy[i];//(end[2*i+1]-beg[2*i+1]+1);
            setLazy[i]=none;
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
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=val;
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=max(tree[2*i],tree[2*i+1]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,q;
    cin >> n >> q;
    SegTree sz(n), left(n), right(n);
    string s;
    cin >> s;
    F0R(i, n) {
        left.rangeSet(i,i,i);
        right.rangeSet(i,i,i);
    }
    sz.rangeSet(0,n-1,1);
    // F0R(i, n) {
    //     // cout << left.rangeQuery(i,i) << " " << right.rangeQuery(i,i) << endl;
    // }
    auto work = [&](int ind)->void{
        int l = left.rangeQuery(ind,ind);
        int r = right.rangeQuery(ind,ind);
        // cout << ind << " " << l << " " << r << endl;
        if(l!=ind) {
            left.rangeSet(l, ind-1, l);
            right.rangeSet(l, ind-1, ind-1);
            sz.rangeSet(l, ind-1, ind-l);
        }
        if(r!=ind) {
            left.rangeSet(ind+1, r, ind+1);
            right.rangeSet(ind+1, r, r);
            sz.rangeSet(ind+1, r, r-ind);
        }
        left.rangeSet(ind,ind,ind);
        right.rangeSet(ind,ind,ind);
        sz.rangeSet(ind,ind,1);
        bool lgood = (ind!=0 && s[ind-1]==s[ind]);
        bool rgood = (ind!=n-1 && s[ind]==s[ind+1]);
        if(lgood && rgood) {
            // cout << "LINE 264 " << ind << endl;
            l=left.rangeQuery(ind-1,ind-1);
            r=right.rangeQuery(ind+1,ind+1);
            left.rangeSet(l,r,l);
            right.rangeSet(l,r,r);
            sz.rangeSet(l,r,r-l+1);
        } else if (lgood) {
            // cout << "LINE 270 " << ind << endl;
            l = left.rangeQuery(ind-1, ind-1);
            left.rangeSet(l, ind, l);
            right.rangeSet(l, ind, ind);
            sz.rangeSet(l, ind, ind-l+1);
        } else if(rgood) {
            // cout << "LINE 275 " << ind << " " << l << " " << r <<  endl;
            r = right.rangeQuery(ind+1, ind+1);
            // cout << r << endl;
            left.rangeSet(ind, r, ind);
            right.rangeSet(ind, r, r);
            sz.rangeSet(ind, r, r-ind+1);
            // cout << "LINE 283 " << ind << " " << r << endl;
        } else {
            // cout << "LINE 276 " << ind << endl;
        }
        // cout << left.rangeQuery(ind,ind) << " " << right.rangeQuery(ind,ind) << endl;
    };

    auto get = [&](int l, int r)->int{
        int le = max(l,left.rangeQuery(r,r)), rg = min(r,right.rangeQuery(l,l));
        // cout << le << " " << rg << " " << right.rangeQuery(l,l) << endl;
        FOR(i, l, r+1) {
            // cout << i << " " << left.rangeQuery(i,i) << " " << right.rangeQuery(i,i) << endl;
        }
        int ans = max(r-le+1, rg-l+1);
        if(rg+1<=le-1) {
            ans=max(ans, sz.rangeQuery(rg+1,le-1));
        }
        return ans;
    };
    F0R(i, n) work(i);
        // F0R(i, n) {
        // cout << i << " " << left.rangeQuery(i,i) << " " << right.rangeQuery(i,i) << endl;
    // }
    while(q--) {
        int a;
        cin >> a;
        if(a==1) {
            int b;
            char c;
            cin >> b >> c;
            s[b-1]=c;
            work(b-1);
            // F0R(i, n) cout << i << " " << left.rangeQuery(i,i) << " " << right.rangeQuery(i,i) << " " << sz.rangeQuery(i,i) << endl;
        } else {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            cout << get(l,r) << endl;
        }
    }
    return 0;
}
/*
10 1
baaaacczcc
2 1 4
*/