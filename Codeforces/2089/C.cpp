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
// #define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e=mod-2) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}       
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,l,k;
        cin >> n >> l >> k;
        vt<vt<int>> dp(n,vt<int>(k+1));
        dp[0][0]=1;
        // vt<int> tries(n);
        auto sum = [&n](vt<int> &pref, int lx, int r)->int{
            // cout << pref << lx << " " << r << endl;
            lx%=n;
            r%=n;
            if(lx<0) lx+=n;
            if(r<0) r+=n;
            if(lx<=r) return (pref[r+1]-pref[lx])%mod;
            return (pref.back()-pref[lx]+pref[r+1])%mod;
        };
        ROF(key, 1, l+k) {
            int left = k+l-key+1;
            vt<vt<int>> ndp(n,vt<int>(k+1));
            F0R(fake, min(k, left)+1) {
                // cout << fake << " " << left << endl;
                int lesser = (left-fake)/n*bexpo(left-fake)%mod;
                int greater = ((left-fake)/n+1)*bexpo(left-fake)%mod;
                int numGreater = (left-fake)%n;
                vt<int> pref1(n+1), pref2(n+1);
                F0R(i, n) pref1[i+1]=pref1[i]+dp[i][fake];
                if(fake!=0) {
                    F0R(i, n) pref2[i+1]=pref2[i]+dp[i][fake-1];
                }
                // cout << left << endl;
                int chanceFake = fake*bexpo(left)%mod;
                int chanceReal = (mod+1-chanceFake)%mod;
                // cout << "LINE 198 " << chanceReal << " " << chanceFake << endl;
                // cout << greater << " " << lesser << " " << numGreater << endl;
                F0R(i, n) {
                    if(i<numGreater) {
                        ndp[i][fake]+=greater*chanceReal%mod;
                    } else {
                        ndp[i][fake]+=lesser*chanceReal%mod;
                    }
                    // cout << i << " LINE 206 " << ndp << endl;
                    //more starts at 1, 2, 3, ..., numGreater
                    //corresponds to positions (i-1)-numGreater...(i-1)-1
                    if(numGreater==0) {
                        // cout << "LINE 210 " << endl;
                        ndp[i][fake]+=lesser*sum(pref1, 0, n-1)%mod*chanceReal%mod;
                        ndp[i][fake]%=mod;
                    } else {
                        // cout << "LINE 213 " << ndp << enld;
                        int tot = sum(pref1,0,n-1)%mod;
                        int more = sum(pref1, i-numGreater, i-1)%mod;
                        int less = tot-more;
                        // cout << i << " " << more << " " << less << endl;
                        less%=mod;
                        less+=mod;
                        less%=mod;
                        // cout << "LINE 222 (new) " << ndp << enld;
                        ndp[i][fake]+=more*greater%mod*chanceReal%mod;
                        ndp[i][fake]+=less*lesser%mod*chanceReal%mod;
                    }
                    // cout << i << " LINE 222 " << ndp << endl;
                    //if its fake, everything gets shifted by l
                    int shift = l%n;
                    if(fake!=0) {
                        int unshifted = (i+n-shift)%n;
                        // cout << unshifted << " " << dp[unshifted][fake-1] << endl;
                        ndp[i][fake]+=dp[unshifted][fake-1]*chanceFake%mod;
                    }
                    ndp[i][fake]%=mod;
                    ndp[i][fake]+=mod;
                    ndp[i][fake]%=mod;
                }
            }
            swap(dp,ndp);
            cout << key << " " << dp << endl;
        }
        F0R(i, n) cout << dp[i][k] << " ";
        cout << endl;
        // cout << dp << endl;
    }
    return 0;
}