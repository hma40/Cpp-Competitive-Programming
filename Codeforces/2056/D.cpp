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
    vt<vt<int>> tr;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tr.resize(2*np);
        for(int i = 0; i < np; i++) {
            tr[i+np].add(0);
        }
        for(int i = np-1; i > 0; i--) {
            int sz = tr[2*i].size()+tr[2*i+1].size();
            for(int j = 0; j < sz; j++) tr[i].add(0);
        }
        n=np;
    }
    void build(vector<int> b) {
        for(int i = 0; i < b.size(); i++) {
            tr[i+n][0]=b[i];
        }
        for(int i = n-1; i > 0; i--) {
            // cout << i << endl;
            merge(i);
        }
    }
    void merge(int ind) {
        int l = 0, r = 0;
        int nxt = 0;
        while(l<tr[2*ind].size()&&r<tr[2*ind+1].size()) {
            if(tr[2*ind][l]<tr[2*ind+1][r]) {
                tr[ind][nxt++]=tr[2*ind][l];
                l++;
            } else {
                tr[ind][nxt++]=tr[2*ind+1][r];
                r++;
            }
        }
        while(l<tr[2*ind].size()) {
            tr[ind][nxt++]=tr[2*ind][l];
            l++;
        }
        while(r<tr[2*ind+1].size()) {
            tr[ind][nxt++]=tr[2*ind+1][r];
            r++;
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tr[pos][0]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            merge(pos);
            // tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    int numbersExactly(int a, int b, int x) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) {
                ans+=(upper_bound(begin(tr[a]), end(tr[a]), x)-lower_bound(begin(tr[a]), end(tr[a]), x));
                a++;
            }
            if(b%2==0) {
                ans+=(upper_bound(begin(tr[b]), end(tr[b]), x)-lower_bound(begin(tr[b]), end(tr[b]), x));
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
    // cout << st.numbersAtMost(2,4,3) << endl;
    // cout << st.tr << endl;
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        SegTree st(n+1);
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        int ans = n*(n+1)/2;
        vt<int> b(n+1);
        // cout << ans << endl;
        FOR(med, 1, 11) {
            set<int> eq;
            eq.insert(inf);
            F0R(i, n) {
                if(a[i]==med) eq.insert(i);
                if(a[i]<=med) {
                    b[i+1]=b[i]-1;
                } else {
                    b[i+1]=b[i]+1;
                }
            }
            // assert(false);
            // cout << b << endl;
            st.build(b);
            // cout << st.tr << endl;
            // assert(false);
            F0R(i, n) {
                int nxt = *eq.lower_bound(i);
                if(nxt==inf) break;
                // cout << "LINE 237 " << i << " " << nxt << endl;
                ans-=st.numbersExactly(nxt+1, n, b[i]);
            }
            // cout << med << " " << ans << endl;
        }
        cout << ans << endl;

    }
    return 0;
}
/*
10
6 3 2 3 5 3 4 2 3 5

[l,r]
one(l,r)<=(r-l+1)/2-1

bad:
pref(r+1)-pref(l)>=(r-l+1)/2
2pref(r+1)-2pref(l)>=r-l+1
2pref(r+1)-r>=2pref(l)-l+1

[1,10,2,3,3]
n=3
[0,0,1,1,1,1]
[0,1,1,2,2,2]

[0,1,0,-1,-2,-3]
[0,1,0,1,0,-1]

*/