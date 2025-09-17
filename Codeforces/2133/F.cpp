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
    vt<int> where;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np, inf);
        n=np;
        where.resize(2*np, inf);
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        where[pos]=pos-n;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=min(tree[2*pos],tree[2*pos+1]);
            if(tree[2*pos]>tree[2*pos+1]) {
                where[pos]=where[2*pos+1];
            } else {
                where[pos]=where[2*pos];
            }
        }
    }
    pair<int,int> rangeQuery(int a, int b) {
        a+=n;
        pair<int,int> ans = {inf,0};
        b+=n;
        while(a<=b) {
            if(a%2==1) {
                if(tree[a]<ans.f) {
                    ans.f=tree[a];
                    ans.s=where[a];
                }
                // ans=min(ans, tree[a++]);
                a++;
            }
            if(b%2==0) {
                if(tree[b]<ans.f) {
                    ans.f=tree[b];
                    ans.s=where[b];
                }
                // ans=min(ans, tree[b--]);
                b--;
            }
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
        // cout << n << endl;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        // F0R(i, n) cout << a[i] << " ";
        cout << endl;
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
        vt<int> last(n+1,-1);
        vt<vt<array<int,4>>> where(n+1);
        // vt<pair<int,int>> where(n, {-1,-1});
        SegTree st(n+1);
        st.set(0,0);
        min_pq<array<int,5>> upd;
        trav(x, ord) {
            while(upd.size() && upd.top()[0]<x[0]) {
                auto tp = upd.top();
                upd.pop();
                if(st.tree[st.n+tp[1]]>tp[2]) {
                    st.set(tp[1], tp[2]);
                    // where[tp[1]]=tp[3];
                    where[tp[1]].add({tp[0], tp[2], tp[3], tp[4]});
                }
            }
            if(x[2]==0) {
                auto bruh = st.rangeQuery(iv[x[1]].f, x[1]);
                int mn = bruh.f;
                upd.push({x[1], iv[x[1]].s, mn+1, bruh.s, 0});
            } else {
                auto bruh = st.rangeQuery(iv[x[1]].f, iv[x[1]].s);
                int mn = bruh.f;
                upd.push({x[1], iv[x[1]].s, mn+1, bruh.s, 1});
            }
        }
        while(upd.size()) {
            auto tp = upd.top();
            upd.pop();
            if(st.tree[st.n+tp[1]]>tp[2]) {
                st.set(tp[1], tp[2]);
                where[tp[1]].add({tp[0], tp[2], tp[3], tp[4]});
            }
        }
        // cerr << where << endl;
        
        if(st.rangeQuery(n,n).f>=inf) {
            cout << -1 << endl;
        } else {
            cout << st.rangeQuery(n,n).f << endl;
            vt<int> ans;
            int cur = n;
            int look = st.rangeQuery(n,n).f;
            int lim = inf;
            auto DO = [&](auto self) -> void{
                if(look==0) return;
                // cout << cur << " " << look << endl;
                while(cur) {
                    trav(x, where[cur]) {
                        if(x[1]==look && x[0]<lim) {
                            if(x[3]==0) {
                                look--;
                                lim=inf;
                                cur=x[0];
                                self(self);
                                ans.add(x[0]+1);
                            } else {
                                ans.add(x[0]+1);
                                look--;
                                lim=iv[x[0]].f;
                                cur=iv[x[0]].s;
                                self(self);
                            }
                            return;
                        }
                    }
                    cur--;
                }
            };
            DO(DO);
            assert(ans.size()==st.rangeQuery(n,n).f);
            // cout << ans << endl;
            trav(x, ans) cout << x << " ";
            cout << endl;
        }
    }
    return 0;
}
/*
dp[i][pos]
*/