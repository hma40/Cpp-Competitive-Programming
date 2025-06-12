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
int get(vt<int> &a, int x, int k) {
    // cout << x << " " << k << endl;
    if(k<a.size()) return a[k];
    if(k%2) return get(a, x, k-1);
    if(!(k/2%2)) return x^get(a, x, k/2);
    return x;
}
vt<int> allSum, evenSum;
int getEvenSum(int l, int r, int x, vt<int> &a) {
    // cerr << "LINE 160: " << l << " " << r << " " << x << " " << a << endl;
    if(l>r) return 0;
    if(l<a.size()) {
        int mx = min((int)a.size()-2, r);

        int ans = evenSum[mx]-evenSum[l-1]+getEvenSum(mx+2, r, x, a);
        // cerr << "LINE 164 RETURNING " << l << " " << r << " " << x << " " << ans << endl;
        return ans;
    }
    int ans = 0;
    int zeroModStart = (l+3)/4*4, zeroModEnd = r/4*4;
    int twoModStart, twoModEnd;
    if(zeroModStart==l) twoModStart=l+2;
    else twoModStart=l;
    if(r==zeroModEnd) twoModEnd = r-2;
    else twoModEnd = r;
    int twoModAmt = (twoModEnd-twoModStart)/4+1;
    ans+=x*twoModAmt;
    // cout << l << " " << r << " TWOAMT: " << twoModAmt << endl; 
    if(x==0){
        ans+=getEvenSum(zeroModStart/2, zeroModEnd/2, x, a); 
        // cerr << "RETURNING " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    } else {
        int zeroModAmt = (zeroModEnd-zeroModStart)/4+1;
        ans+=zeroModAmt-getEvenSum(zeroModStart/2, zeroModEnd/2, x, a);
        // cerr << "RETURNING " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }
}
int getSum(int l, int r, int x, vt<int> &a) {
    // cerr << "LINE 190 " << l << " " << r << " " << x << " " << a << endl;

    if(l>r) return 0;
    if(l<a.size()) {
        int mx = min((int)a.size()-1, r);
        int ans = allSum[mx]-allSum[l-1]+getSum(mx+1, r, x, a);
        // cerr << "RETURNING LINE 193 " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }
    if(l%2==1) {
        int ans = get(a,x,l)+getSum(l+1,r,x,a);
        // cerr << "RETURNING LINE 198 " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }
    if(r%2==0) {
        int ans = get(a,x,r)+getSum(l, r-1,x, a);

        // cerr << "RETURNING LINE 202 " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }
    int ans = 0;
    int zeroModStart = (l+3)/4*4, zeroModEnd = r/4*4;
    int twoModStart, twoModEnd;
    if(zeroModStart==l) twoModStart=l+2;
    else twoModStart=l;
    if(r-1==zeroModEnd) twoModEnd = r-3;
    else twoModEnd = r-1;
    int twoModAmt = (twoModEnd-twoModStart)/4+1;
    ans+=x*2*twoModAmt;
    // cerr << twoModStart << " " << twoModEnd << " " << zeroModStart << " " << zeroModEnd << endl;
    if(x==0) {
        ans+=2*getEvenSum(zeroModStart/2, zeroModEnd/2, x, a); 
        // cerr << "RETURNING LINE 208 " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }else {
        int zeroModAmt = (zeroModEnd-zeroModStart)/4+1;
        ans+=2*zeroModAmt-2*getEvenSum(zeroModStart/2, zeroModEnd/2, x, a);
        // cerr << "RETURNING " << l << " " << r << " " << x << " " << a << " " << ans << endl;
        return ans;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,l,r;
        cin >> n >> l >> r;
        vt<int> a(n+1);
        // int ans = 0;
        F0R(i, n) cin >> a[i+1];
        if(n%2==0) {
            int temp = 0;
            FOR(i, 1, n/2+1) temp^=a[i];
            n++;
            a.add(temp);
        }
        vt<int> pref(n+1);
        F0R(i, n) pref[i+1]=pref[i]^a[i+1];
        while(a.size()<=2*n+1) {
            a.add(pref[a.size()/2]);
        }
        int x = 0;
        F0R(i, n+1) x^=a[i];
        // cerr << a << endl;
        // return 0;
        allSum.assign(a.size(), 0);
        evenSum.assign(a.size(), 0);
        FOR(i, 1, a.size()) {
            allSum[i]=allSum[i-1]+a[i];
            evenSum[i]=evenSum[i-1];
            if(i%2==0) evenSum[i]+=a[i];
            // cerr << i << allSum << evenSum << endl;
        }
        cout << getSum(l,r,x, a) << endl;
    }
    return 0;
}
/*

1
4 31 35
1 1 1 0 

Extendo: 1 1 1 0 0
x = 1

sum(31,35)=1+sum(32,35)=1+2f(32)+2f(34)=1+2+2f(32)
*/