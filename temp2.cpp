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
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np, inf);
        n=np;
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=min(tree[2*pos],tree[2*pos+1]);
        }
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=min(ans, tree[a++]);
            if(b%2==0) ans=min(ans, tree[b--]);
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
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<pair<int,int>> iv(n);
        F0R(i, n) {
            iv[i].f=max(0LL,i-a[i]+1);
            iv[i].s=min(n, i+a[i]);
        }
        vt<array<int,3>> ord;
        F0R(i, n) {
            if(a[i]==0) continue;
            ord.add({iv[i].f, i, 1});
            ord.add({i-1, i, 0});
        }
        sort(begin(ord),end(ord));
        
        SegTree st(n+1);
        st.set(0,0);
        min_pq<array<int,3>> upd;
        trav(x, ord) {
            while(upd.size() && upd.top()[0]<x[0]) {
                auto tp = upd.top();
                upd.pop();
                if(st.tree[st.n+tp[1]]>tp[2]) {
                    st.set(tp[1], tp[2]);
                }
            }
            if(x[2]==0) {
                int mn = st.rangeQuery(iv[x[1]].f, x[1]);
                upd.push({x[1], iv[x[1]].s, mn+1});
            } else {
                int mn = st.rangeQuery(iv[x[1]].f, iv[x[1]].s);
                upd.push({x[1], iv[x[1]].s, mn+1});
            }
        }
        while(upd.size()) {
            auto tp = upd.top();
            upd.pop();
            if(st.tree[st.n+tp[1]]>tp[2]) {
                st.set(tp[1], tp[2]);
            }
        }
        if(st.rangeQuery(n,n)>=inf) {
            cout << -1 << endl;
        } else {
            cout << st.rangeQuery(n,n) << endl;
        }
        // vt<vt<int>> dp(n+1, vt<int>(n, inf));
        // dp[0][0]=0;
        // F0R(i, n) {
        //     int smallest = max(0LL, i-a[i]+1);
        //     int largest = min(n, i+a[i]);
        //     FOR(j, smallest, i+1) {
        //         F0R(k, n) {
        //             dp[largest][i]=min(dp[largest][i], dp[j][k]+1);
        //         }
        //     } 
        //     FOR(j, i+1, largest+1) {
        //         F0R(k, smallest) {
        //             dp[largest][i]=min(dp[largest][i], dp[j][k]+1);
        //         }
        //     }
        // }
        // /*
        // enumerate 
        // */
        // int ans = inf;
        // F0R(i, n) ans=min(ans, dp[n][i]);
        // if(ans>=inf) {
        //     cout << -1 << endl;
        // } else {
        //     cout << ans << endl;
        // }
    }
    return 0;
}
/*
dp[i][pos]
*/