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
map<int,int> mp;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n;
vt<int> a;
vt<int> pref, dc, ddc;
int query(int x) {
    auto lb = mp.upper_bound(x);
    // cout << x << (*lb) << endl;
    // if((*lb).f!=x) --lb; 
    --lb;
    int group = (*lb).s;
    int ans = ddc[(*lb).s];
    // cout << "LINE 148 " << ans << endl;
    /*
    now we have everything before. Lets deal with this group now
    lets calculate displacement first
    original: 4a0+3a1+2a2+a3
    this group: 2a1+a2
    */
    if(x==0) return 0;
    x-=(*lb).f;
    // cout << x << endl;
    ans+=dc[x+group];
    // cout << "LINE 159 " << ans << endl;
    ans-=dc[group];
    // cout << "LINE 161 " << ans << endl;
    /*
    +4a1 +3a2
    -4a1

    */
    int amt = n-(x+group);
    // cout << "AMT: " << amt << endl;
    ans-=(amt)*pref[x+group];
    // cout << "LINE 169 " << ans << endl;
    ans+=(amt)*pref[group];
    // cout << "LINE 171 " << ans << endl;
    // return -1;
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    cin >> n;
    a.resize(n);
    F0R(i, n) cin >> a[i];
    int end = 0;
    mp[0]=0;
    mp[inf]=n+1;
    R0F(i, n) {
        mp[end+i+1]=mp[end]+1;
        end+=i+1;
    }
    // cout << mp << endl;
    /*
    1 2 5 10
    1 3 8 18
    1 4 12 30

    1+(1+2)+(1+2+5)+(1+2+5+10) = 4a1+3a2+2a3+a4
    2+(2+5)+(2+5+10) = 3a2+
    5+(5+10)+10
    */
    pref.resize(n+1);
    F0R(i, n) pref[i+1]=pref[i]+a[i];
    dc.resize(n+1);
    F0R(i, n) {
        dc[i+1]=dc[i]+(n-i)*a[i];
    }
    // cout << dc << endl;
    ddc.resize(n+1);
    F0R(i, n) ddc[i+1]=ddc[i]+dc[n]-dc[i];
    // cout << ddc << endl;
    int q;
    cin >> q;
    while(q--) {
        int x,y;
        cin >> x >> y;
        x--;
        // y--;
        // query(x);
        // cout << query(x) << endl;
        cout << query(y)-query(x) << endl;
        // cout << query(x) << " " << query(y) << endl;
    }
    return 0;
}