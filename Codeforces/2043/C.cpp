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
int maxSuffix(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    int ans = 0, cur = 0;
    ROF(i, lo, hi+1) {
        cur+=v[i];
        ans=max(ans,cur);
    }
    return ans;
}
int maxPrefix(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    int ans=0, cur=0;
    FOR(i, lo, hi+1) {
        cur+=v[i];
        ans=max(ans, cur);
    }
    return ans;
}
int minSuffix(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    int ans = 0, cur = 0;
    ROF(i, lo, hi+1) {
        cur+=v[i];
        ans=min(ans,cur);
    }
    // cout << "LINE 163 " << ans << " " << lo << " " << hi << endl;
    return ans;
}
int minPrefix(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    int ans=0, cur=0;
    FOR(i, lo, hi+1) {
        cur+=v[i];
        ans=min(ans, cur);
    }
    return ans;
}
int minSubarraySum(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    set<int> pref;
    pref.insert(0);
    int ans = 0, sum = 0;
    FOR(i, lo, hi+1) {
        sum+=v[i];
        int biggest = *pref.rbegin();
        ans=min(ans, sum-biggest);
        pref.insert(sum);
    }
    return ans;
}
int maxSubarraySum(vector<int> &v, int lo, int hi) {
    if(lo>hi) return 0;
    set<int> pref;
    pref.insert(0);
    int ans = 0, sum = 0;
    FOR(i, lo, hi+1) {
        sum+=v[i];
        int biggest = *pref.begin();
        ans=max(ans, sum-biggest);
        pref.insert(sum);
    }
    return ans;
}
void ins(set<int> &s, int lo, int hi ){
    FOR(i, lo, hi+1) s.insert(i);
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
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        int bad = 0;
        F0R(i, n) if(a[i]!=-1&&a[i]!=1) bad=i;
        set<int> ans;
        ins(ans,minSubarraySum(a,0,bad-1),maxSubarraySum(a,0,bad-1));
        ins(ans,minSubarraySum(a,bad+1,n-1),maxSubarraySum(a,bad+1,n-1));
        ins(ans,a[bad]+minSuffix(a,0,bad-1)+minPrefix(a,bad+1,n-1),a[bad]+maxSuffix(a,0,bad-1)+maxPrefix(a,bad+1,n-1));
        // FOR(i, minSubarraySum(a,0,bad-1),maxSubarraySum(a,0,bad-1)+1) ans.insert(i);
        // FOR(i, minSubarraySum(a,bad+1,n-1),maxSubarraySum(a,bad+1,n-1)+1) ans.insert(i);
        // FOR(i, a[bad]+minSuffix(a,0,bad-1)+minPrefix(a,bad+1,n-1),a[bad]+maxSuffix(a,0,bad-1)+maxPrefix(a,bad+1,n-1)+1) ans.insert(i);
        cout << ans.size() << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}