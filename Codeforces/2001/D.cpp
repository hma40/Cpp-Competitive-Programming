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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> tree;
    vt<int> tree2;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
        tree2.resize(2*np);
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
            tree2[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=min(tree[2*i],tree[2*i+1]);
            tree2[i]=max(tree2[2*i], tree2[2*i+1]);
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=inf;
        tree2[pos]=0;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=min(tree[2*pos],tree[2*pos+1]);
            tree2[pos]=max(tree2[2*pos],tree2[2*pos+1]);
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=min(ans,tree[a++]);
            if(b%2==0) ans=min(ans,tree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
    int getMax(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=max(ans,tree2[a++]);
            if(b%2==0) ans=max(ans,tree2[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
};
struct SegTre {
    int n;
    vt<int> tree;
    SegTre(int nn) {
        nn++;
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void rangeSub(int lo, int hi, int amt) {
        // tree[lo]-=amt;
        // tree[hi+1]+=amt;
        add(lo, -amt);
        add(hi+1, amt);
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
        vt<int> a(n);
        set<int> activePos;
        activePos.insert(inf);
        F0R(i, n) activePos.insert(i);
        F0R(i, n) cin >> a[i];   
        SegTree s(n);
        s.build(a);
        // assert(false);
        // assert(false);
        // vt<int,set<int>> mp
        map<int, set<int>> mp;
        F0R(i, n) {
            mp[a[i]].insert(i);
        }
        F0R(i, n) {
            mp[a[i]].insert(inf);
        }
        // assert(false);
        vt<int> ans;
        SegTre backward(n);
        set<int> back;
        int globalSub = 0;
        R0F(i, n) {
            back.insert(a[i]);
            backward.rangeSub(i, i, -back.size());
        }
        // cout << backward.tree << endl;
        F0R(i, n) {
            if(mp.size()==0) break;
            // cout << i << mp << ans << endl;
            int lo = i, hi = n;
            while(lo+1<hi) {
                int mi = (lo+hi)/2;
                // int mid = (lo+hi)/2;
                int mid=*(activePos.lower_bound(mi));
                if(mid==inf) {
                    hi=mi;
                    continue;
                }
                int count = backward.rangeQuery(0,mid);
                // cout << mid << " " << count << endl;
                if(count==mp.size()) {
                    lo=mi;
                } else {
                    hi=mi;
                }
                // cout << lo << " " << hi << " " << activePos << endl;
            }
            // cout << "LINE 212 " << lo << endl;
            if(ans.size()%2) {
                auto fuck = s.rangeQuery(i,lo);
                ans.add(fuck);
                mp[fuck].erase(inf);
                backward.rangeSub(0, *(mp[fuck].rbegin()), 1);
                trav(x, mp[fuck]) {
                    if(x==inf) continue;
                    activePos.erase(x);
                    s.set(x, 0);
                }
                mp.erase(fuck);
                while(a[i]!=fuck) i++;
            } else {
                //take max
                auto fuck = s.getMax(i, lo);
                ans.add(fuck);
                mp[fuck].erase(inf);
                backward.rangeSub(0, *(mp[fuck].rbegin()), 1);
                trav(x, mp[fuck]) {
                    if(x==inf) continue;
                    activePos.erase(x);
                    s.set(x, 0);
                }
                mp.erase(fuck);
                while(a[i]!=fuck) i++;
            }
        }
        // cout << ans << endl;
        cout << ans.size() << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}