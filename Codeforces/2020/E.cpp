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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
FastMod fs(mod);
    ll bexpo(ll b, ll e, ll m = 1000000007) {
        ll a = 1;
        while(e) {
            if(e%2) {
                a*=b;
                a%=m;
            }
            e/=2;
            b*=b;
            b%=m;
        }
        return a;
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
        vt<int> a(n),p(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> p[i];
        vt<int> chances(11);
        int inv1e4 = bexpo(10000, mod-2);
        F0R(i, n) {
            F0R(j, 11) {
                if((a[i]&(1<<j))==0) continue;
                chances[j]=(chances[j]*(10000-p[i])%mod*inv1e4%mod)+((mod+1-chances[j])*p[i]%mod*inv1e4%mod);
                chances[j]%=mod;
                chances[j]+=mod;
                chances[j]%=mod;
            }
        }
        int ans = 0;
        F0R(i, 11) {
            ans+=chances[i]%mod*(1<<i)%mod*(1<<i)%mod;
            ans%=mod;
        }
        F0R(i, 11) {
            FOR(j, i+1, 11) {
                array<int,4> probabilities = {0,0,0,0};//0: both on, 1:first on, 2: second on, 3: none on
                probabilities[3]=1;
                array<int,4> temp;
                F0R(k, n) {
                    if((a[k]&(1<<i))&&(a[k]&(1<<j))) {
                        temp[0]=probabilities[0]*(10000-p[k])%mod*inv1e4%mod+probabilities[3]*p[k]%mod*inv1e4%mod;
                        temp[1]=probabilities[1]*(10000-p[k])%mod*inv1e4%mod+probabilities[2]*p[k]%mod*inv1e4%mod;
                        temp[2]=probabilities[2]*(10000-p[k])%mod*inv1e4%mod+probabilities[1]*p[k]%mod*inv1e4%mod;
                        temp[3]=probabilities[3]*(10000-p[k])%mod*inv1e4%mod+probabilities[0]*p[k]%mod*inv1e4%mod;
                    } else if((a[k]&(1<<i))) {
                        temp[0]=probabilities[0]*(10000-p[k])%mod*inv1e4%mod+probabilities[2]*p[k]%mod*inv1e4%mod;
                        temp[1]=probabilities[1]*(10000-p[k])%mod*inv1e4%mod+probabilities[3]*p[k]%mod*inv1e4%mod;
                        temp[2]=probabilities[2]*(10000-p[k])%mod*inv1e4%mod+probabilities[0]*p[k]%mod*inv1e4%mod;
                        temp[3]=probabilities[3]*(10000-p[k])%mod*inv1e4%mod+probabilities[1]*p[k]%mod*inv1e4%mod;                    
                    } else if((a[k]&(1<<j))) {
                        temp[0]=probabilities[0]*(10000-p[k])%mod*inv1e4%mod+probabilities[1]*p[k]%mod*inv1e4%mod;
                        temp[1]=probabilities[1]*(10000-p[k])%mod*inv1e4%mod+probabilities[0]*p[k]%mod*inv1e4%mod;
                        temp[2]=probabilities[2]*(10000-p[k])%mod*inv1e4%mod+probabilities[3]*p[k]%mod*inv1e4%mod;
                        temp[3]=probabilities[3]*(10000-p[k])%mod*inv1e4%mod+probabilities[2]*p[k]%mod*inv1e4%mod;                          
                    } else {
                        temp.swap(probabilities);
                    }
                    temp[0]%=mod;
                    temp[1]%=mod;
                    temp[2]%=mod;
                    temp[3]%=mod;
                    temp.swap(probabilities);
                }
                ans+=probabilities[0]*2*(1<<i)%mod*(1<<j)%mod;
                ans%=mod;
            }
        }
        cout << ans << endl;
        // cout << bexpo(4,mod-2) << endl;
        // cout << bexpo(2,mod-2)*5%mod << endl;
    }
    return 0;
}