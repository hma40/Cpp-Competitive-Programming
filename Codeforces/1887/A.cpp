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
bool works(vt<int> &a, vt<int> &b, int remv) {
    // cout << a << b << remv << endl;
    for(int i = 0; i < b.size()-remv; i++) {
        // cout << i << endl;
        if(a[i]>=b[b.size()-remv-i-1]) {
            return false;
        }   
    }
    return true;
}
bool fine(vt<int> a, vt<int> &b, int remv) {
    sort(begin(a),end(a));
    for(int i = 0; i < b.size()-remv; i++) {
        // cout << i << endl;
        if(a[i]>=b[b.size()-remv-i-1]) {
            return false;
        }   
    }
    return true;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<int> a(n-1);
        F0R(i, n-1) cin >> a[i];
        vt<int> b(n);
        F0R(i, n) {
            cin >> b[i];
            b[i]*=-1;
        }
        sort(begin(a),end(a));
        sort(begin(b),end(b));
        F0R(i, n) {
            b[i]*=-1;
        }
        //first bsearch on what the answer is if we remove the extra element
        int lo = 0, hi = n;
        while(lo+1<hi) {
            int mid = (lo+1+hi)/2;
            if(works(a,b,mid)) {
                hi=mid;
            } else {
                lo=mid;
            }
        }
        // cout << hi << endl;
        //hi now contains elements to remove if extra element is removed
        //now bsearch 2: what max of other element is if we don't remove
        
        a.add(1);
        int lo2 = 0, hi2 = 1000000001;
        while(lo2+1<hi2) {
            int mid = (lo2+hi2)/2;
            a.back()=mid;
            if(fine(a,b,hi-1)) {
                lo2=mid;
            } else {
                hi2=mid;
            }
        }
        if(lo2>=m) {
            cout << (hi-1)*m << endl;
        } else {
            cout << (hi-1)*lo2+hi*(m-lo2) << endl;
        }
    }
    return 0;
}
/*
1 1 5 5
3 3 3 8
*/