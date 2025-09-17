#pragma GCC optimize("O3,unroll-loops")
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
// #define endl "\n"
// #define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int ququ(vt<int> &v) {
    cout << "? " << v.size() << " ";
    trav(x, v) cout << x << " ";
    cout << "\n";
    cout.flush();
    int ans;
    cin >> ans;
    return ans;
}
int quid(int x) {
    cout << "? " << x << " ";
    F0R(i, x) cout << i+1 << " ";
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}
int quidd(int x) {
    cout << "? " << x << " ";
    R0F(i, x) cout << i+1 << " ";
    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}
// vt<vt<int>> id(1005), rid(1005);
vt<int> pos;
        string ans;
void DO(int i, int j, int hi) {
    vt<int> qu;
    int left = 0, right = 0;
    int expect = 0;
    FOR(k, i, j+1) {
        expect+=left*(left+1)/2+right*(right+1)/2;
        F0R(x, left) {
            qu.add(hi-1);
            qu.add(hi);
        }
        qu.add(k+1);
        qu.add(hi);
        F0R(x, right) {
            qu.add(hi-1);
            qu.add(hi);
        }
        if(left==right) {
            right*=2;
            right++;
        } else {
            left*=2;
            left++;
        }
        qu.add(hi);
    }
    // cout << expect << endl;
    int an = ququ(qu)-expect;
    FOR(ii, i, j+1) {
        if(an&(1<<(ii-i))) {
            ans[ii]='(';
        } else {
            ans[ii]=')';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        // int qleft = 200;
        int n;
        cin >> n;
        // assert(n<500);
        // int lo = 0, hi = n-1;
        bool fir; //first is (
        if(n==2) {
            vt<int> v = {1,2};
            if(ququ(v)) {
                cout << "! ()" << endl;
            } else {
                cout << "! )(" << endl;
            }
            continue;
        }
        vt<int> all;
        F0R(i, n) all.add(i+1);
        if(!ququ(all)) {
            int lo = 0, hi = n;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                vt<int> v;
                R0F(i, mid) v.add(i+1);
                if(ququ(v)) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            string ans;
            // cout << hi << endl;
            F0R(i, hi-1) ans+=')';
            FOR(i, hi-1, n) ans+='(';
            cout << "! " << ans << endl;
        } else {
            ans="";
            F0R(i, n) ans+='?';
            int lo=0, hi = n;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                vt<int> v;
                F0R(i, mid) v.add(i+1);
                if(ququ(v)) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            // cout << hi << endl;
            if(n<12) {
                DO(0, n-1, hi);
            } else {
                for(int i = 11; i < n; i+=12) {
                    DO(i-11, i, hi);
                } 
                DO(n-12, n-1, hi);
            }
            cout << "! " << ans << endl;
        }
    }
    return 0;
}
/*

()()()()()()()()

0 0
0 1
1 1

100 queries
so we need to do them in groups of 14

?)()?)()
could get
2
4
6
10

d: 2, 4, 8

?)()()()?)()()()
12
16

abbaab))))))

())(()))))))
3
(((((())))))
6

))))))))))))
0

()()()x()()()()
original: a(a+1)/2+b(b+1)/2
new: (a+b+1)*(a+b+2)/2

))((
1: (0,0)
2: (0,1)
4: (1,1)
8: (1,3)
16: (3,3)
32: (3,7)
64: (7,7)
128: (7,15)
256: (15,15) or (7,7,11)
512: (15,31) or (7,15,15) 
1024: (31,31) or (15,15,23) or (8,9,15,17)
2048: (31,63) or (15,31,31) or (15,17,19,19)
4096: (63,63) or (31,31,47) or (19,24,27,31)
8192: (63,127) or (48,49,57) or (31,35,39,39) or (15,31,31,31,31)

*/