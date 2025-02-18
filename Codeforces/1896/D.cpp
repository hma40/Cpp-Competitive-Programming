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
};
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        set<int> ones;
        SegTree a(n);
        F0R(i, n) {
            int x;
            cin >> x;
            if(x==1) ones.insert(i);    
            a.set(i, x);
        }
        while(q--) {
            int op;
            cin >> op;
            if(op==1) {
                int sum;
                cin >> sum;
                if(a.rangeQuery(0, n-1)<sum) {
                    cout << "NO" << endl;
                    continue;
                }
                if(sum==1) {
                    if(ones.size()) {
                        cout << "YES" << endl;
                    } else {
                        cout << "NO" << endl;
                    }
                    continue;
                } else if(sum==2) {
                    if(n==1&&ones.size()) {
                        cout << "NO" << endl;
                    } else {
                        cout << "YES" << endl;
                    }
                    continue;
                } else if(sum==3) {
                    if(!ones.size()) {
                        cout << "NO" << endl;
                    } else if(a.rangeQuery(0,n-1)<3) {
                        cout << "NO" << endl;
                    } else {
                        cout << "YES" << endl;
                    }
                    continue;
                }
                bool good = false;
                int lo = 0, hi = n;
                while(lo+1<hi) {
                    int mid = (lo+hi)/2;
                    int rq = a.rangeQuery(0,mid);
                    if(rq==sum) {
                        good=true;
                        break;
                    } else if(rq<sum) {
                        lo=mid;
                    } else {
                        hi=mid;
                    }
                }
                lo=-1;
                hi=n-1;
                while(lo+1<hi) {
                    int mid = (1+lo+hi)/2;
                    int rq = a.rangeQuery(mid, n-1);
                    if(rq==sum) {
                        good=true;
                        break;
                    } else if(rq<sum) {
                        hi=mid;
                    } else {
                        lo=mid;
                    }
                }
                if(ones.size()) {
                    int start = (*ones.begin())+1;
                    lo=(*ones.begin())+1;
                    hi=n;
                    while(lo+1<hi) {
                        int mid = (lo+hi)/2;
                        int rq = a.rangeQuery(start, mid);
                        if(rq==sum||rq==sum-1) {
                            good=true;
                            break;
                        } else if(rq<sum) {
                            lo=mid;
                        } else {
                            hi=mid;
                        }
                    }
                    start = (*ones.rbegin())-1;
                    lo = -1;
                    hi=start;
                    while(lo+1<hi) {
                        int mid = (lo+hi+1)/2;
                        int rq = a.rangeQuery(mid, start);
                        if(rq==sum||rq==sum-1) {
                            good=true;
                            break;
                        } else if(rq<sum) {
                            hi=mid;
                        } else {
                            lo=mid;
                        }
                    }
                }
                if(good) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            } else {
                int i,v;
                cin >> i >> v;
                i--;
                a.set(i,v);
                ones.erase(i);
                if(v==1) ones.insert(i);
            }
        }
    }
    return 0;
}
/*
1
6 1
2 2 1 2 2 2
1 3
*/