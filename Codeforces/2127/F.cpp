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
const ll mod = 1000000007;
ll inf = 1e18;
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return ans;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> f(4e5+5), ivf(4e5+5);
    f[0]=ivf[0]=1;
    FOR(i, 1, 4e5+5) {
        f[i]=f[i-1]*i%mod;
        ivf[i]=bexpo(f[i], mod-2);
    }
    auto nck = [&](int n, int k)->int{
        if(n==k) return 1LL;
        if(k<0 || k>n) return 0;
        // cout << n << " " << k << " " << f[n] << " " << f[n]*ivf[k]%mod*ivf[n-k]%mod << endl;
        return f[n]*ivf[k]%mod*ivf[n-k]%mod;
    };
    auto count = [&](int n, int sum, int mx)->int{
        if(mx==0) {
            if(sum==0) return 1;
            else return 0;
        }
        if(sum<0) return 0;
        int ans = 0;
        int neg = 1;
        for(int numMax = 0; numMax<=n; numMax++) {
            if(numMax*mx>sum) break;
            /*
            sum-=numMax*mx
            C(n, numMax)
            now n-numMax spaces for sum-numMax*mx
            */
            ans+=neg*nck(n, numMax)%mod*nck(sum-numMax*(mx+1)+n-1, n-1);
            // cout << neg << " " << nck(n, numMax) << " " << nck(sum-numMax*(mx+1)+n-1, n-1) << endl;
            ans%=mod;
            neg*=-1;
            // cout << numMax << " " << ans << endl;
        }
        return ans;
    };
    // cout << count(3, 4, 2) << endl;
    int t;
    cin >> t;
    while(t--) {
        int n,sum;
        cin >> n >> sum;
        int ans = 0;
        F0R(mx, sum+1) {
            //add contribution from a[n-1]
            int fir = count(n-1, sum-mx, mx), sec = count(n-2, sum-2*mx, mx);
            ans+=mx*fir;
            ans%=mod;
            // if(mx==2) cout << ans << endl;
            // cout << mx << " " << ans << endl;
            //add contribution from other occurrences of max
            ans+=(n-1)*sec%mod*mx%mod;
            ans%=mod;
            // if(mx==2) cout << ans << endl;
            // cout << mx << " " << ans << endl;
            //subtract contribution from a[1]
            ans-=fir*(sum-mx)%mod*bexpo(n-1, mod-2)%mod;
            ans%=mod;
            // if(mx==2) cout << ans << endl;
            //subtract contribution from right after max
            //so it goes from 1...n-1 (so n-2 numbers)
            ans-=sec*(sum-2*mx)%mod*bexpo(n-2, mod-2)%mod*(n-2)%mod;
            ans%=mod;
            // cout << ans << endl;
            //subtract contribution from a[n-2]=a[n-1]=mx
            ans-=sec*mx%mod;
            ans%=mod;
            // cout << mx << " " << ans << endl;
        }
        ans%=mod;
        if(ans<0) ans+=mod;
        cout << ans << endl;
    }
    return 0;
}
/*
+: sum of maximums
-: numbers right after maximums
-: a[0] 

n=3, sum=4, max=2

2 2 0
0 2 2
2 0 2
1 1 2
1 2 1
2 1 1

C(6,2)
sum=1
C(3,1) * C(3,2) = 3
*/