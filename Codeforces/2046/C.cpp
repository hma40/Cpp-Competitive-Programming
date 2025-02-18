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
    int lower(int amt) {
        //return the least index k such that a[0]+a[2]+...+a[k-1]>=amt
        int tot = 0, ind = 1;
        while(ind<n) {
            // cout << "LINE 187 " << ind << endl << tree << endl;
            if(tot+tree[2*ind]<amt) {

                tot+=tree[2*ind];
                ind=ind*2+1;
            } else {
                ind=ind*2;
            }
        }
        return ind-n+1;
    }
    int upper(int amt) {
        //return the largest k such that a[k]+...+a[inf]>=amt
        int tot = 0, ind = 1;
        while(ind<n) {
            // cout << ind << endl;
            if(tot+tree[2*ind+1]<amt) {

                tot+=tree[2*ind+1];
                ind=ind*2;
            } else {
                ind=ind*2+1;
            }
        }
        return ind-n;
    }
};
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
        vt<pair<int,int>> coords(n);
        F0R(i, n) cin >> coords[i].f >> coords[i].s;
        map<int,int> comp;
        vt<int> invComp;
        int nxt = 0;
        vt<int> all;
        F0R(i, n) {
            all.add(coords[i].f);
            all.add(coords[i].f+1);
            all.add(coords[i].s);
            all.add(coords[i].s+1);
        }
        sort(begin(all),end(all));
        trav(x, all) {
            if(comp.count(x)) continue;
            comp[x]=nxt++;
            invComp.add(x);
        }
        F0R(i, n) {
            coords[i].f=comp[coords[i].f];
            coords[i].s=comp[coords[i].s];
        }
        SegTree left(nxt+5), right(nxt+5);
        min_pq<pair<int,int>> rem;
        F0R(i, n) rem.push({coords[i].f, coords[i].s});
        F0R(i, n) {
            right.add(coords[i].s, 1);
        }
        int bestAns = 0;
        pair<int,int> bestCoord = {0,0};
        FOR(xcoord, -1, nxt+3) {
            while(rem.size()&&rem.top().f<xcoord) {
                auto tp = rem.top();
                rem.pop();
                right.add(tp.s, -1);
                left.add(tp.s, 1);
            }
            // cout << xcoord << " " << left.tree << endl << right.tree << endl << endl;
            int lo = 0, hi = n/4+1;//min score
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                pair<int,int> leftInt = {left.lower(mid), left.upper(mid)};
                pair<int,int> rightInt = {right.lower(mid), right.upper(mid)};
                if(min(leftInt.s, rightInt.s)>=max(leftInt.f, rightInt.f)) {
                    //this is possible
                    lo=mid;
                    if(mid>bestAns) {
                        bestAns=mid;
                        bestCoord={xcoord, min(leftInt.s, rightInt.s)};
                    }
                } else {
                    hi=mid;
                }
            }

        }
        cout << bestAns << endl << invComp[bestCoord.f] << " " << invComp[bestCoord.s] << endl;
    }
    return 0;
}
/*
try each x
for each x, find best y
*/